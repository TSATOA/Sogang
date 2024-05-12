open Program
open Error

(* Our symbol table will be a mapping from 'string' to 'ctype_entry'. *)
type ctype_entry =
  | VarType of ctype
  | FuncType of ctype * ctype list (* return type * argument type list *)

(* Define a module for symbol table *)
module SymbolMap = Map.Make(String)

(* During the semantic analysis, this type can be helpful. Why do we need this
 * even though 'ctype' is already defined? If you encounter a wrong expression
 * during the semantic analysis (for example "1 + true"), you cannot decide its
 * type but still may have to return something. *)
type typ = Void | Int | Bool | Unknown

let ctyp_to_typ ctyp =
  match ctyp with
  | CVoid -> Void
  | CInt -> Int
  | CBool -> Bool

let typ_to_ctyp ctyp =
  match ctyp with
  | Void -> CVoid
  | Int -> CInt
  | Bool -> CBool
  | Unknown -> (* Raise exception *)
      failwith "Not allowed (You should not call this in such situation)"

(* Record the type of variables into the symbol table *)
let rec collect_vars decls sym_tab =
  match decls with
  | [] -> sym_tab
  | head_decl :: tail_decls ->
      let (ctyp, vname) = head_decl in
      let sym_tab = SymbolMap.add vname (VarType ctyp) sym_tab in
      collect_vars tail_decls sym_tab

(* Record the type of functions into the symbol table *)
let rec collect_functions funcs sym_tab =
  match funcs with
  | [] -> sym_tab
  | (fname, ret_type, args, _) :: tail_funcs ->
      let arg_types = List.map (fun (atyp, _) -> atyp) args in
      let func_type = FuncType (ret_type, arg_types) in
      let sym_tab = SymbolMap.add fname func_type sym_tab in
      collect_functions tail_funcs sym_tab

(*
let string_of_ctype ctype =
  match ctype with
  | CInt -> "int"
  | CBool -> "bool"
  | CVoid -> "void"
let strings_of_ctype ctype =
  match ctype with
  | Int -> "int"
  | Bool -> "bool"
  | Void -> "void"
let print_sym_tab sym_tab =
  SymbolMap.bindings sym_tab
  |> List.iter (fun (key, value) ->
        match value with
        | VarType ctype -> Printf.printf "Var: %s, Type: %s\n" key (string_of_ctype ctype)
        | FuncType (ret_type, arg_types) ->
            let arg_types_str = String.concat ", " (List.map string_of_ctype arg_types) in
            Printf.printf "Func: %s, Return type: %s, Arg types: (%s)\n" key (string_of_ctype ret_type) arg_types_str
      )
      
*)




(* Check expression 'e' and return detected semantic errors, along with the
 * decided type of 'e'. If the type of expression cannot be decided due to
 * semantic error, return 'Unknown' as its type. *)
let rec check_exp sym_tab e =
  match e with
  | ConstBool b -> ([], Bool)
  | ConstInt i -> ([], Int)
  | Var vname ->
    if SymbolMap.mem vname sym_tab then
      let ctype_entry = SymbolMap.find vname sym_tab in
      match ctype_entry with
      | VarType ctype -> ([], ctyp_to_typ ctype)
      | FuncType _ -> ([UsingFunctionAsVar vname], Unknown)
    else
      ([UndefinedName vname], Unknown)
  | Add (e1, e2) | Sub (e1, e2) | Mul (e1, e2) | Div (e1, e2) ->
    let (errors1, type1) = check_exp sym_tab e1 in
    let (errors2, type2) = check_exp sym_tab e2 in
    if type1 = Int && type2 = Int then
      (errors1 @ errors2, Int)
    else
      (errors1 @ errors2 @ [OperandMismatch], Unknown)
  | Neg e ->
    let (errors, type_) = check_exp sym_tab e in
    if type_ = Int then
      (errors, Int)
    else
      (errors @ [OperandMismatch], Unknown)
  | Equal (e1, e2) | NotEq (e1, e2) | LessEq (e1, e2) | LessThan (e1, e2) | GreaterEq (e1, e2) | GreaterThan (e1, e2) ->
    let (errors1, type1) = check_exp sym_tab e1 in
    let (errors2, type2) = check_exp sym_tab e2 in
    if (type1 = Int || type1 = Bool) && type1 = type2 then
      (errors1 @ errors2, Bool)
    else
      (errors1 @ errors2 @ [OperandMismatch], Unknown)
  | And (e1, e2) | Or (e1, e2) ->
    let (errors1, type1) = check_exp sym_tab e1 in
    let (errors2, type2) = check_exp sym_tab e2 in
    if type1 = Bool && type2 = Bool then(
      (errors1 @ errors2, Bool))
    else(
      (*Printf.printf "Type1: %s, Type2: %s\n" (strings_of_ctype type1) (strings_of_ctype type2);*)
      (errors1 @ errors2 @ [OperandMismatch], Unknown))
  | Not e ->
    let (errors, type_) = check_exp sym_tab e in
    if type_ = Bool then
      (errors, Bool)
    else
      (errors @ [OperandMismatch], Unknown)
  | CallExp (fname, args) ->
    if SymbolMap.mem fname sym_tab then
      let ctype_entry = SymbolMap.find fname sym_tab in
      match ctype_entry with
      | FuncType (ret_type, arg_types) -> 
        if List.length args != List.length arg_types then(
          ([ArgNumMismatch], Unknown))
        else
          let rec check_args sym_tab arg_types args =  
            match arg_types, args with
            | [], [] -> ([], ctyp_to_typ ret_type)  
            | expected_type :: expected_rest, arg :: arg_rest ->
              let (exp_errors, exp_type) = check_exp sym_tab arg in
              if exp_type = ctyp_to_typ expected_type then
                let (rest_errors, ret) = check_args sym_tab expected_rest arg_rest in
                (exp_errors @ rest_errors, Unknown)
              else
                (exp_errors @ [ArgTypeMismatch (expected_type,typ_to_ctyp exp_type)],  Unknown)
            | _ -> ([],Unknown)
          in  
          check_args sym_tab arg_types args  
      | VarType _ -> ([CallingVariable fname], Unknown)
    else
      ([UndefinedName fname], Unknown)




let rec check_stmt sym_tab func_ret_type stmt =
  match stmt with
  | LocalDecl (ctype, vname) ->
    let sym_tab = SymbolMap.add vname (VarType ctype) sym_tab in
    (sym_tab, [])
  | Assign (vname, exp) ->
    if SymbolMap.mem vname sym_tab then
      let entry = SymbolMap.find vname sym_tab in
      match entry with
      | VarType var_type ->
        let (exp_errors, exp_type) = check_exp sym_tab exp in
        if exp_type = Unknown then
          (sym_tab, exp_errors) 
        else if ctyp_to_typ var_type = exp_type then
          (sym_tab, exp_errors)
        else
          (sym_tab, [AssignMismatch (var_type, typ_to_ctyp exp_type)])
      | FuncType _ ->
        (sym_tab, [UsingFunctionAsVar vname])
    else
      (sym_tab, [UndefinedName vname])
    
  | Call (fname, arg_exps) ->
    if SymbolMap.mem fname sym_tab then
      let ctype_entry = SymbolMap.find fname sym_tab in
      match ctype_entry with
      | FuncType (ret_type, arg_types) ->
        if List.length arg_exps != List.length arg_types then
          (sym_tab, [ArgNumMismatch]) 
        else
          let rec check_args_match args_types args_exps acc_errors =
            match args_types, args_exps with
            | [], [] -> (acc_errors)  
            | expected_type :: t_rest, arg_exp :: e_rest ->
              let (arg_errors, arg_type) = check_exp sym_tab arg_exp in
              if arg_type = ctyp_to_typ expected_type then
                check_args_match t_rest e_rest (acc_errors @ arg_errors)
              else
                check_args_match t_rest e_rest (acc_errors @ arg_errors @ [ArgTypeMismatch (expected_type, typ_to_ctyp arg_type)])
            | _ -> (acc_errors)
          in
          let errors = check_args_match arg_types arg_exps [] in
          (sym_tab, errors)
      | VarType _ -> (sym_tab, [CallingVariable fname])  
    else
      (sym_tab, [UndefinedName fname])  
  
  | Return ->
    if ctyp_to_typ func_ret_type = Void then
      (sym_tab, [])
    else
      (sym_tab, [ReturnMismatch (func_ret_type, CVoid)])
  | ReturnValue exp ->
    let (exp_errors, exp_type) = check_exp sym_tab exp in
    if exp_type != Unknown then(
      if ctyp_to_typ func_ret_type = exp_type then
        (sym_tab, exp_errors)
      else
        (sym_tab, [ReturnMismatch (func_ret_type, typ_to_ctyp exp_type)] @ exp_errors))
    else
      (sym_tab,exp_errors)

  | If (cond, then_stmts, else_stmts) ->
    let (cond_errors, cond_type) = check_exp sym_tab cond in
    let (sym_tab_then, then_errors) = check_stmts sym_tab func_ret_type then_stmts in
    let (sym_tab_else, else_errors) = check_stmts sym_tab func_ret_type else_stmts in
    if cond_type = Bool then
      (sym_tab, cond_errors @ then_errors @ else_errors)
    else
      (sym_tab, [OperandMismatch] @ cond_errors @ then_errors @ else_errors)
  | While (cond, do_stmts) ->
    let (cond_errors, cond_type) = check_exp sym_tab cond in
    let (sym_tab_do, do_errors) = check_stmts sym_tab func_ret_type do_stmts in
    if cond_type = Bool then
      (sym_tab, cond_errors @ do_errors)
    else
      (sym_tab, [OperandMismatch] @ cond_errors @ do_errors)

and check_stmts sym_tab func_ret_type stmts =
  let rec collect_errors sym_tab acc stmts =
    match stmts with
    | [] -> (sym_tab, acc)
    | stmt :: rest ->
      let (updated_sym_tab, errors) = check_stmt sym_tab func_ret_type stmt in
      collect_errors updated_sym_tab (acc @ errors) rest
  in
  let (final_sym_tab, errors) = collect_errors sym_tab [] stmts in
  (*print_sym_tab final_sym_tab;*)  (* print sym_tab *)
  (final_sym_tab, errors)

let check_single_function sym_tab (fname, ret_type, args, body) =
  let rec add_params_to_symtab sym_tab args =
    match args with
    | [] -> sym_tab
    | (arg_type, arg_name) :: rest ->
        let sym_tab = SymbolMap.add arg_name (VarType arg_type) sym_tab in
        add_params_to_symtab sym_tab rest
  in
  let local_sym_tab = add_params_to_symtab sym_tab args in
  let (final_sym_tab, errors) = check_stmts local_sym_tab ret_type body in
  errors


(* Check functions and return detected semantic errors. *)
let rec check_functions sym_tab funcs =
  match funcs with
  | [] -> []
  | head_func :: tail_funcs ->
      let current_errors = check_single_function sym_tab head_func in
      let rest_errors = check_functions sym_tab tail_funcs in
      current_errors @ rest_errors
      



(* Check a program and return detected semantic errors. *)
let run (p: program) : error list =
  let (gdecls, funcs) = p in
  let sym_tab = collect_vars gdecls SymbolMap.empty in
  let sym_tab = collect_functions funcs sym_tab in
  (* At this point, 'sym_tab' must contain global variables & functions *)
  check_functions sym_tab funcs



