open Program
open Ir

module RDSet = Set.Make(struct
  type t = instr
  let compare = Pervasives.compare
end)
module ConstMap = Map.Make(String)

(* 여기에 각 최적화 기법에 대한 함수들을 정의합니다. *)

let constant_folding_instr (instr: instr) : instr list =
  match instr with
  | BinOp (dest, op, Imm (ImmInt a), Imm (ImmInt b)) ->  (* 수정된 부분 *)
    let result = match op with
      | AddOp -> a + b
      | SubOp -> a - b
      | MulOp -> a * b
      | DivOp -> a / b
      | _ -> failwith "Unsupported operation for constant folding"
    in [Set (dest, ImmInt result)]
  | _ -> [instr]  (* 다른 명령어는 그대로 유지 *)



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
      (* 상수 값을 설정하는 명령어를 발견하면, 상수 맵에 추가 *)
      let new_constants = ConstMap.add reg value constants in
      Set (reg, ImmInt value) :: propagate new_constants rest
    | BinOp (dest, op, Reg a, Reg b) :: rest ->
      (* 두 피연산자가 모두 상수일 경우의 로직 *)
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
      (* 복사 명령어를 발견하면, 복사 맵에 추가 *)
      let new_copies = ConstMap.add dest src copies in
      Copy (src, dest) :: propagate new_copies rest
    | BinOp (dest, op, Reg a, Reg b) :: rest ->
      (* 두 피연산자 중 하나라도 복사된 값이라면, 그 값을 사용 *)
      let a' = if ConstMap.mem a copies then ConstMap.find a copies else a in
      let b' = if ConstMap.mem b copies then ConstMap.find b copies else b in
      BinOp (dest, op, Reg a', Reg b') :: propagate copies rest
    | Set (reg, value) :: rest ->
      (* 상수 설정 명령어는 복사 맵을 변경하지 않고 그대로 유지 *)
      Set (reg, value) :: propagate copies rest
    | instr :: rest ->
      (* 다른 명령어들은 변경 없이 그대로 유지 *)
      instr :: propagate copies rest
  in
  let propagated_instrs = propagate ConstMap.empty instrs in
  (fname, args, propagated_instrs)



  
  
  
    

let run (ir: ir_code): ir_code =
  let ir = constant_folding ir in
  let ir = constant_propagation ir in
  let ir = copy_propagation ir in
  ir
