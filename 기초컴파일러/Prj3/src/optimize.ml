open Program
open Ir

module RDSet = Set.Make(struct
  type t = instr
  let compare = Pervasives.compare
end)
module ConstMap = Map.Make(String)

(* ���⿡ �� ����ȭ ����� ���� �Լ����� �����մϴ�. *)

let constant_folding_instr (instr: instr) : instr list =
  match instr with
  | BinOp (dest, op, Imm (ImmInt a), Imm (ImmInt b)) ->  (* ������ �κ� *)
    let result = match op with
      | AddOp -> a + b
      | SubOp -> a - b
      | MulOp -> a * b
      | DivOp -> a / b
      | _ -> failwith "Unsupported operation for constant folding"
    in [Set (dest, ImmInt result)]
  | _ -> [instr]  (* �ٸ� ��ɾ�� �״�� ���� *)



let constant_folding (ir: ir_code) : ir_code =
let (fname, args, instrs) = ir in
let folded_instrs = List.flatten (List.map constant_folding_instr instrs) in
(fname, args, folded_instrs)

let constant_propagation (ir: ir_code) : ir_code =
  let (fname, args, instrs) = ir in
  let rec propagate constants instrs =
    match instrs with
    | [] -> []
    | Set (reg, ImmInt value) :: rest ->
      (* ��� ���� �����ϴ� ��ɾ �߰��ϸ�, ��� �ʿ� �߰� *)
      let new_constants = ConstMap.add reg value constants in
      Set (reg, ImmInt value) :: propagate new_constants rest
    | BinOp (dest, op, Reg a, Reg b) :: rest ->
      (* �� �ǿ����ڰ� ��� ����� ����� ���� *)
      let process_binop a_val b_val = match op with
        | AddOp -> a_val + b_val
        | SubOp -> a_val - b_val
        | MulOp -> a_val * b_val
        | DivOp -> a_val / b_val
        | _ -> failwith "Unsupported operation for constant propagation"
      in
      if ConstMap.mem a constants && ConstMap.mem b constants then
        let a_val = ConstMap.find a constants in
        let b_val = ConstMap.find b constants in
        let result = process_binop a_val b_val in
        Set (dest, ImmInt result) :: propagate constants rest
      else
        BinOp (dest, op, Reg a, Reg b) :: propagate constants rest
    | instr :: rest ->
      instr :: propagate constants rest
  in
  let propagated_instrs = propagate ConstMap.empty instrs in
  (fname, args, propagated_instrs)

  

let copy_propagation (ir: ir_code) : ir_code =
  let (fname, args, instrs) = ir in
  let rec propagate copies instrs =
    match instrs with
    | [] -> []
    | Copy (src, dest) :: rest ->
      (* ���� ��ɾ �߰��ϸ�, ���� �ʿ� �߰� *)
      let new_copies = ConstMap.add dest src copies in
      Copy (src, dest) :: propagate new_copies rest
    | BinOp (dest, op, Reg a, Reg b) :: rest ->
      (* �� �ǿ����� �� �ϳ��� ����� ���̶��, �� ���� ��� *)
      let a' = if ConstMap.mem a copies then ConstMap.find a copies else a in
      let b' = if ConstMap.mem b copies then ConstMap.find b copies else b in
      BinOp (dest, op, Reg a', Reg b') :: propagate copies rest
    | Set (reg, value) :: rest ->
      (* ��� ���� ��ɾ�� ���� ���� �������� �ʰ� �״�� ���� *)
      Set (reg, value) :: propagate copies rest
    | instr :: rest ->
      (* �ٸ� ��ɾ���� ���� ���� �״�� ���� *)
      instr :: propagate copies rest
  in
  let propagated_instrs = propagate ConstMap.empty instrs in
  (fname, args, propagated_instrs)



  
  
  
    

let run (ir: ir_code): ir_code =
  let ir = constant_folding ir in
  let ir = constant_propagation ir in
  let ir = copy_propagation ir in
  ir
