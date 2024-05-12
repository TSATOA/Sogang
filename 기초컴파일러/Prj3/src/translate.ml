open Program
open Ir
open Helper

(* The module for symbol table. Carefully think about what should be stored in
 * the symbol table for this IR translation phase. *)
module SymbolMap = Map.Make(String)


(* Let's assume that boolean is 1-byte and integer is 4-byte. *)
let sizeof ctyp =
  match ctyp with
  | CInt -> 4
  | CBool -> 1
  | CIntArr n -> 4 * n
  | CBoolArr n -> n

let rec extract_names args =
  match args with
  | [] -> []
  | (arg_typ, arg_name) :: tail_args -> arg_name :: extract_names tail_args

  let rec process_args args symbol_table instrs =
    match args with
    | [] -> (instrs, symbol_table)
    | (typ, arg_name) :: tail_args ->
      let new_symbol_table = SymbolMap.add arg_name (typ, arg_name) symbol_table in
      process_args tail_args new_symbol_table instrs
  


(* Function to convert expressions to IR instructions. *)
let rec translate_expr_to_ir expr reg symbol_table=
  match expr with
  | ConstBool b -> ([Set (reg, ImmBool b)] ,reg)
  | ConstInt i -> ([Set (reg, ImmInt i)],reg)
  | Var v ->
    let (_, reg_name) = SymbolMap.find v symbol_table in
    if reg_name = reg then
      ([], reg)  (* Reuse the register if it's the same *)
    else
      ([Copy (reg_name, reg)], reg)  (* Only copy if different *)
  | Arr (arr_name, idx_expr) ->
    let idx_reg = create_register_name () in
    let addr_reg = create_register_name () in
    let (idx_instrs, _) = translate_expr_to_ir idx_expr idx_reg symbol_table in
    if SymbolMap.mem arr_name symbol_table then
        match SymbolMap.find arr_name symbol_table with
        | (CIntArr _, base_addr_reg) ->
            let offset_instrs = [
                BinOp (addr_reg, MulOp, Reg idx_reg, Imm (ImmInt 4));
                BinOp (addr_reg, AddOp, Reg base_addr_reg, Reg addr_reg)
            ] in
            let load_instr = Load (reg, addr_reg) in
            idx_instrs @ offset_instrs @ [load_instr], reg
        | (CBoolArr _, base_addr_reg) ->
            let offset_instrs = [
                BinOp (addr_reg, MulOp, Reg idx_reg, Imm (ImmInt 1));
                BinOp (addr_reg, AddOp, Reg base_addr_reg, Reg addr_reg)
            ] in
            let load_instr = Load (reg, addr_reg) in
            idx_instrs @ offset_instrs @ [load_instr], reg
        | _ -> failwith ("Invalid array type for: " ^ arr_name)
    else
        failwith ("Array not found: " ^ arr_name)

  | Add (e1, e2) -> 
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1 @ i2 @ [BinOp (reg, AddOp, Reg r1, Reg r2)],reg)
  | Sub (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, SubOp, Reg r1, Reg r2)],reg)
  | Mul (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, MulOp, Reg r1, Reg r2)],reg)
  | Div (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, DivOp, Reg r1, Reg r2)],reg)
  | Neg e ->
    let r1 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e r1 symbol_table in
    (i1@ [UnOp (reg, NegOp, Reg r1)],reg)
  | Equal (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, EqOp, Reg r1, Reg r2)],reg)
  | NotEq (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, NeqOp, Reg r1, Reg r2)],reg)
  | LessEq (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, LeqOp, Reg r1, Reg r2)],reg)
  | LessThan (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, LtOp, Reg r1, Reg r2)],reg)
  | GreaterEq (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, GeqOp, Reg r1, Reg r2)],reg)
  | GreaterThan (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1@ i2@ [BinOp (reg, GtOp, Reg r1, Reg r2)],reg)
  | And (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let false_label = create_label () in
    let end_label = create_label () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1 
    @ [GotoIfNot (r1, false_label)] 
    @ i2 
    @ [GotoIfNot (r2, false_label)]
    @ [Set (reg, ImmBool true); Goto end_label]
    @ [Label false_label; Set (reg, ImmBool false)]
    @ [Label end_label]
    ,reg)
  | Or (e1, e2) ->
    let r1 = create_register_name () in
    let r2 = create_register_name () in
    let true_label = create_label () in
    let end_label = create_label () in
    let (i1,_) = translate_expr_to_ir e1 r1 symbol_table in
    let (i2,_) = translate_expr_to_ir e2 r2 symbol_table in
    (i1 
    @ [GotoIf (r1, true_label)] 
    @ i2 
    @ [GotoIf (r2, true_label)]
    @ [Set (reg, ImmBool false); Goto end_label]
    @ [Label true_label; Set (reg, ImmBool true)]
    @ [Label end_label]
    ,reg)
  | Not e ->
    let r1 = create_register_name () in
    let (i1,_) = translate_expr_to_ir e r1 symbol_table in
    (i1@ [UnOp (reg, NotOp, Reg r1)],reg)



let rec translate_stmt_to_ir stmts symbol_table =
  match stmts with
  | [] -> ([], symbol_table)
  | stmt :: rest ->
    let (instrs, updated_symbol_table) = match stmt with
      | LocalDecl (typ, name) ->
        if typ then
          let reg = create_register_name () in
          let new_symbol_table = SymbolMap.add name (typ, reg) symbol_table in
          ([], new_symbol_table) (* No LocalAlloc instruction needed *)
        else
          let size = sizeof typ in
          let alloc_reg = create_register_name () in
          let new_symbol_table = SymbolMap.add name (typ,alloc_reg) symbol_table in
          ([LocalAlloc (alloc_reg, size)], new_symbol_table)
      
      | Assign (lv, expr) ->
        let expr_reg = create_register_name () in
        let (expr_instrs, _) = translate_expr_to_ir expr expr_reg symbol_table in
        let store_instrs = match lv with
          | LVar v -> 
            let (_, var_reg) = SymbolMap.find v symbol_table in
            [Copy (expr_reg, var_reg)]  (* Directly copy to the variable's register *)

          | LArr (arr_name, idx_expr) ->
            let idx_reg = create_register_name () in
            let addr_reg = create_register_name () in
            let (idx_instrs, _) = translate_expr_to_ir idx_expr idx_reg symbol_table in
            if SymbolMap.mem arr_name symbol_table then
                match SymbolMap.find arr_name symbol_table with
                | (CIntArr _, base_addr_reg) ->
                    let offset_instrs = [
                        BinOp (addr_reg, MulOp, Reg idx_reg, Imm (ImmInt 4));
                        BinOp (addr_reg, AddOp, Reg base_addr_reg, Reg addr_reg)
                    ] in
                    let store_instr = Store (Reg expr_reg, addr_reg) in
                    idx_instrs @ offset_instrs @ [store_instr]
                | (CBoolArr _, base_addr_reg) ->
                    let offset_instrs = [
                        BinOp (addr_reg, MulOp, Reg idx_reg, Imm (ImmInt 1));
                        BinOp (addr_reg, AddOp, Reg base_addr_reg, Reg addr_reg)
                    ] in
                    let store_instr = Store (Reg expr_reg, addr_reg) in
                    idx_instrs @ offset_instrs @ [store_instr]
                | _ -> failwith ("Invalid array type for: " ^ arr_name)
            else
                failwith ("Array not found: " ^ arr_name)
        in
        (expr_instrs @ store_instrs, symbol_table)
        

      | ReturnValue e ->
        let reg = create_register_name () in
        let (expr_instrs, _) = translate_expr_to_ir e reg symbol_table in
        (expr_instrs @ [Ret (Reg reg)], symbol_table)
        

      | If (cond, then_stmts, else_stmts) ->
        let (cond_instrs, cond_reg) = match cond with
          | Var v ->
            let (_, reg_name) = SymbolMap.find v symbol_table in
            ([], reg_name)  (* Directly use the register assigned to the variable *)
          | _ ->
            let cond_reg = create_register_name () in
            let (instrs, _) = translate_expr_to_ir cond cond_reg symbol_table in
            (instrs, cond_reg)
        in
        let label_then = create_label () in
        let label_else = create_label () in
        let label_end = create_label () in
        let (then_instrs, _) = translate_stmt_to_ir then_stmts symbol_table in
        let (else_instrs, _) = translate_stmt_to_ir else_stmts symbol_table in
        (cond_instrs @ [GotoIf (cond_reg, label_then); Goto (label_else); Label label_then]
          @ then_instrs @ [Goto label_end; Label label_else]
          @ else_instrs @ [Label label_end], symbol_table)

      | While (cond, loop_stmts) ->
        let label_start = create_label () in
        let label_end = create_label () in
        let cond_reg = create_register_name () in
        let (cond_instrs,_) = translate_expr_to_ir cond cond_reg symbol_table in
        let (loop_instrs, _) = translate_stmt_to_ir loop_stmts symbol_table in

        ([Label label_start] @ cond_instrs @ [GotoIfNot (cond_reg, label_end)]
          @ loop_instrs @ [Goto label_start; Label label_end], symbol_table)

    in
    let (rest_instrs, final_symbol_table) = translate_stmt_to_ir rest updated_symbol_table in
    (instrs @ rest_instrs, final_symbol_table)




let run (p: program): ir_code =
  
  let (fname, ret_type, args, stmts) = p in
  let initial_symbol_table = SymbolMap.empty in  
  let (arg_instrs, updated_symbol_table) = process_args args initial_symbol_table [] in
  let (stmt_instrs, final_symbol_table) = translate_stmt_to_ir stmts updated_symbol_table in
  (fname, extract_names args, arg_instrs @ stmt_instrs)





