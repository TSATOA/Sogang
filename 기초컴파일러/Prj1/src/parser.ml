type token =
  | PLUS
  | MINUS
  | TIMES
  | DIVIDE
  | EQUAL
  | NOTEQ
  | LEQ
  | LESS
  | GEQ
  | GREATER
  | AND
  | OR
  | NOT
  | LPAR
  | RPAR
  | ASSIGN
  | LBRA
  | RBRA
  | SEMICOLON
  | COMMA
  | TRUE
  | FALSE
  | INT
  | BOOL
  | VOID
  | IF
  | ELSE
  | WHILE
  | RETURN
  | EOF
  | NUM of (int)
  | IDENTIFIER of (string)

open Parsing;;
let _ = parse_error;;
# 2 "parser.mly"
# 39 "parser.ml"
let yytransl_const = [|
  257 (* PLUS *);
  258 (* MINUS *);
  259 (* TIMES *);
  260 (* DIVIDE *);
  261 (* EQUAL *);
  262 (* NOTEQ *);
  263 (* LEQ *);
  264 (* LESS *);
  265 (* GEQ *);
  266 (* GREATER *);
  267 (* AND *);
  268 (* OR *);
  269 (* NOT *);
  270 (* LPAR *);
  271 (* RPAR *);
  272 (* ASSIGN *);
  273 (* LBRA *);
  274 (* RBRA *);
  275 (* SEMICOLON *);
  276 (* COMMA *);
  277 (* TRUE *);
  278 (* FALSE *);
  279 (* INT *);
  280 (* BOOL *);
  281 (* VOID *);
  282 (* IF *);
  283 (* ELSE *);
  284 (* WHILE *);
  285 (* RETURN *);
    0 (* EOF *);
    0|]

let yytransl_block = [|
  286 (* NUM *);
  287 (* IDENTIFIER *);
    0|]

let yylhs = "\255\255\
\001\000\004\000\004\000\004\000\005\000\005\000\002\000\003\000\
\006\000\006\000\006\000\007\000\007\000\007\000\007\000\009\000\
\008\000\008\000\008\000\010\000\010\000\010\000\010\000\010\000\
\010\000\010\000\013\000\013\000\012\000\012\000\012\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\000\000"

let yylen = "\002\000\
\002\000\000\000\002\000\002\000\000\000\002\000\003\000\008\000\
\001\000\001\000\001\000\000\000\001\000\001\000\003\000\002\000\
\000\000\002\000\002\000\004\000\003\000\005\000\002\000\003\000\
\008\000\007\000\000\000\004\000\000\000\001\000\003\000\001\000\
\001\000\001\000\001\000\004\000\003\000\003\000\003\000\003\000\
\002\000\002\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\002\000\003\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\011\000\010\000\009\000\053\000\000\000\000\000\
\000\000\000\000\003\000\000\000\004\000\000\000\001\000\000\000\
\006\000\000\000\000\000\007\000\000\000\000\000\000\000\000\000\
\016\000\000\000\000\000\000\000\015\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\019\000\000\000\000\000\
\000\000\000\000\000\000\000\000\023\000\033\000\034\000\032\000\
\000\000\000\000\000\000\000\000\000\000\008\000\018\000\000\000\
\000\000\000\000\000\000\051\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\024\000\000\000\000\000\000\000\021\000\000\000\
\000\000\052\000\000\000\000\000\000\000\000\000\000\000\043\000\
\044\000\045\000\046\000\047\000\048\000\000\000\000\000\000\000\
\000\000\020\000\000\000\000\000\036\000\031\000\022\000\000\000\
\000\000\000\000\026\000\000\000\025\000\000\000\000\000\028\000"

let yydgoto = "\002\000\
\006\000\007\000\008\000\009\000\013\000\035\000\023\000\036\000\
\024\000\037\000\076\000\077\000\109\000"

let yysindex = "\002\000\
\027\255\000\000\000\000\000\000\000\000\000\000\027\255\027\255\
\006\000\244\254\000\000\027\255\000\000\255\254\000\000\035\255\
\000\000\017\255\071\255\000\000\000\000\029\255\046\255\048\255\
\000\000\055\255\071\255\062\255\000\000\062\255\049\255\065\255\
\043\255\039\255\052\255\066\255\062\255\000\000\045\255\045\255\
\045\255\045\255\045\255\045\255\000\000\000\000\000\000\000\000\
\078\255\202\255\045\255\045\255\091\255\000\000\000\000\240\255\
\255\255\038\000\038\000\000\000\014\000\045\255\045\255\045\255\
\045\255\045\255\045\255\045\255\045\255\045\255\045\255\045\255\
\045\255\045\255\000\000\117\255\096\255\221\255\000\000\098\255\
\118\255\000\000\099\255\038\000\038\000\019\255\019\255\000\000\
\000\000\000\000\000\000\000\000\000\000\019\255\038\000\045\255\
\094\255\000\000\062\255\062\255\000\000\000\000\000\000\116\255\
\120\255\109\255\000\000\122\255\000\000\062\255\124\255\000\000"

let yyrindex = "\000\000\
\143\000\000\000\000\000\000\000\000\000\000\000\143\000\145\000\
\000\000\000\000\000\000\145\000\000\000\000\000\000\000\000\000\
\000\000\000\000\131\255\000\000\242\254\000\000\000\000\132\255\
\000\000\000\000\131\255\136\255\000\000\136\255\000\000\000\000\
\000\000\000\000\000\000\000\000\136\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\097\255\000\000\140\255\000\000\000\000\000\000\000\000\000\000\
\000\000\003\255\161\255\000\000\000\000\140\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\150\255\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\170\255\176\255\129\255\149\255\000\000\
\000\000\000\000\000\000\000\000\000\000\155\255\182\255\140\255\
\000\000\000\000\136\255\136\255\000\000\000\000\000\000\000\000\
\000\000\009\000\000\000\000\000\000\000\136\255\000\000\000\000"

let yygindex = "\000\000\
\000\000\000\000\008\000\172\000\174\000\070\000\160\000\226\255\
\000\000\000\000\225\255\208\255\000\000"

let yytablesize = 305
let yytable = "\038\000\
\013\000\050\000\001\000\041\000\041\000\015\000\055\000\056\000\
\057\000\058\000\059\000\060\000\061\000\083\000\041\000\012\000\
\009\000\041\000\016\000\012\000\078\000\041\000\041\000\067\000\
\068\000\069\000\070\000\071\000\072\000\018\000\019\000\084\000\
\085\000\086\000\087\000\088\000\089\000\090\000\091\000\092\000\
\093\000\094\000\095\000\041\000\042\000\041\000\042\000\102\000\
\019\000\003\000\004\000\005\000\051\000\020\000\052\000\043\000\
\044\000\043\000\044\000\025\000\026\000\045\000\039\000\046\000\
\047\000\046\000\047\000\027\000\104\000\105\000\010\000\028\000\
\048\000\049\000\048\000\049\000\010\000\014\000\040\000\111\000\
\030\000\014\000\053\000\054\000\003\000\004\000\005\000\031\000\
\022\000\032\000\033\000\062\000\034\000\003\000\004\000\021\000\
\022\000\035\000\035\000\035\000\035\000\035\000\035\000\035\000\
\035\000\035\000\035\000\035\000\035\000\079\000\097\000\035\000\
\103\000\101\000\099\000\035\000\035\000\063\000\064\000\065\000\
\066\000\067\000\068\000\069\000\070\000\071\000\072\000\073\000\
\074\000\039\000\039\000\039\000\039\000\106\000\100\000\108\000\
\096\000\107\000\110\000\039\000\039\000\112\000\002\000\039\000\
\005\000\012\000\014\000\039\000\039\000\040\000\040\000\040\000\
\040\000\017\000\029\000\049\000\049\000\049\000\049\000\040\000\
\040\000\042\000\042\000\040\000\030\000\049\000\049\000\040\000\
\040\000\049\000\037\000\037\000\042\000\049\000\049\000\042\000\
\038\000\038\000\011\000\042\000\042\000\037\000\050\000\050\000\
\037\000\017\000\029\000\038\000\037\000\037\000\038\000\000\000\
\000\000\050\000\038\000\038\000\050\000\000\000\000\000\000\000\
\050\000\050\000\063\000\064\000\065\000\066\000\067\000\068\000\
\069\000\070\000\071\000\072\000\073\000\074\000\000\000\000\000\
\000\000\000\000\000\000\000\000\075\000\063\000\064\000\065\000\
\066\000\067\000\068\000\069\000\070\000\071\000\072\000\073\000\
\074\000\000\000\000\000\000\000\000\000\000\000\000\000\098\000\
\063\000\064\000\065\000\066\000\067\000\068\000\069\000\070\000\
\071\000\072\000\073\000\074\000\000\000\000\000\080\000\063\000\
\064\000\065\000\066\000\067\000\068\000\069\000\070\000\071\000\
\072\000\073\000\074\000\000\000\000\000\081\000\063\000\064\000\
\065\000\066\000\067\000\068\000\069\000\070\000\071\000\072\000\
\073\000\074\000\027\000\027\000\082\000\000\000\000\000\027\000\
\027\000\027\000\027\000\000\000\027\000\027\000\000\000\027\000\
\065\000\066\000\067\000\068\000\069\000\070\000\071\000\072\000\
\073\000"

let yycheck = "\030\000\
\015\001\033\000\001\000\001\001\002\001\000\000\037\000\039\000\
\040\000\041\000\042\000\043\000\044\000\062\000\012\001\008\000\
\031\001\015\001\031\001\012\000\052\000\019\001\020\001\005\001\
\006\001\007\001\008\001\009\001\010\001\031\001\014\001\063\000\
\064\000\065\000\066\000\067\000\068\000\069\000\070\000\071\000\
\072\000\073\000\074\000\001\001\002\001\001\001\002\001\096\000\
\014\001\023\001\024\001\025\001\014\001\019\001\016\001\013\001\
\014\001\013\001\014\001\031\001\015\001\019\001\014\001\021\001\
\022\001\021\001\022\001\020\001\099\000\100\000\001\000\017\001\
\030\001\031\001\030\001\031\001\007\000\008\000\014\001\110\000\
\019\001\012\000\031\001\018\001\023\001\024\001\025\001\026\001\
\019\000\028\001\029\001\014\001\031\001\023\001\024\001\025\001\
\027\000\001\001\002\001\003\001\004\001\005\001\006\001\007\001\
\008\001\009\001\010\001\011\001\012\001\019\001\015\001\015\001\
\019\001\015\001\017\001\019\001\020\001\001\001\002\001\003\001\
\004\001\005\001\006\001\007\001\008\001\009\001\010\001\011\001\
\012\001\001\001\002\001\003\001\004\001\018\001\017\001\027\001\
\020\001\018\001\017\001\011\001\012\001\018\001\000\000\015\001\
\000\000\015\001\015\001\019\001\020\001\001\001\002\001\003\001\
\004\001\018\001\015\001\001\001\002\001\003\001\004\001\011\001\
\012\001\001\001\002\001\015\001\015\001\011\001\012\001\019\001\
\020\001\015\001\001\001\002\001\012\001\019\001\020\001\015\001\
\001\001\002\001\007\000\019\001\020\001\012\001\001\001\002\001\
\015\001\012\000\027\000\012\001\019\001\020\001\015\001\255\255\
\255\255\012\001\019\001\020\001\015\001\255\255\255\255\255\255\
\019\001\020\001\001\001\002\001\003\001\004\001\005\001\006\001\
\007\001\008\001\009\001\010\001\011\001\012\001\255\255\255\255\
\255\255\255\255\255\255\255\255\019\001\001\001\002\001\003\001\
\004\001\005\001\006\001\007\001\008\001\009\001\010\001\011\001\
\012\001\255\255\255\255\255\255\255\255\255\255\255\255\019\001\
\001\001\002\001\003\001\004\001\005\001\006\001\007\001\008\001\
\009\001\010\001\011\001\012\001\255\255\255\255\015\001\001\001\
\002\001\003\001\004\001\005\001\006\001\007\001\008\001\009\001\
\010\001\011\001\012\001\255\255\255\255\015\001\001\001\002\001\
\003\001\004\001\005\001\006\001\007\001\008\001\009\001\010\001\
\011\001\012\001\018\001\019\001\015\001\255\255\255\255\023\001\
\024\001\025\001\026\001\255\255\028\001\029\001\255\255\031\001\
\003\001\004\001\005\001\006\001\007\001\008\001\009\001\010\001\
\011\001"

let yynames_const = "\
  PLUS\000\
  MINUS\000\
  TIMES\000\
  DIVIDE\000\
  EQUAL\000\
  NOTEQ\000\
  LEQ\000\
  LESS\000\
  GEQ\000\
  GREATER\000\
  AND\000\
  OR\000\
  NOT\000\
  LPAR\000\
  RPAR\000\
  ASSIGN\000\
  LBRA\000\
  RBRA\000\
  SEMICOLON\000\
  COMMA\000\
  TRUE\000\
  FALSE\000\
  INT\000\
  BOOL\000\
  VOID\000\
  IF\000\
  ELSE\000\
  WHILE\000\
  RETURN\000\
  EOF\000\
  "

let yynames_block = "\
  NUM\000\
  IDENTIFIER\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'top_decls) in
    Obj.repr(
# 23 "parser.mly"
                       ( _1 )
# 280 "parser.ml"
               : Program.program))
; (fun __caml_parser_env ->
    Obj.repr(
# 26 "parser.mly"
                          ( ([], []) )
# 286 "parser.ml"
               : 'top_decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Program.decl) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'top_decls) in
    Obj.repr(
# 27 "parser.mly"
                        ( let (gdecls, funcs) = _2 in (_1 :: gdecls, funcs) )
# 294 "parser.ml"
               : 'top_decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Program.func) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'funcs) in
    Obj.repr(
# 28 "parser.mly"
                   ( ([], _1 :: _2) )
# 302 "parser.ml"
               : 'top_decls))
; (fun __caml_parser_env ->
    Obj.repr(
# 30 "parser.mly"
                      ( [] )
# 308 "parser.ml"
               : 'funcs))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Program.func) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'funcs) in
    Obj.repr(
# 31 "parser.mly"
                   ( _1 :: _2 )
# 316 "parser.ml"
               : 'funcs))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'ctype) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 33 "parser.mly"
                                  ( (_1, _2) )
# 324 "parser.ml"
               : Program.decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 7 : 'ctype) in
    let _2 = (Parsing.peek_val __caml_parser_env 6 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 4 : 'args) in
    let _7 = (Parsing.peek_val __caml_parser_env 1 : 'stmts) in
    Obj.repr(
# 35 "parser.mly"
                                                      ( (_2, _1, _4, _7) )
# 334 "parser.ml"
               : Program.func))
; (fun __caml_parser_env ->
    Obj.repr(
# 37 "parser.mly"
             ( Program.CVoid )
# 340 "parser.ml"
               : 'ctype))
; (fun __caml_parser_env ->
    Obj.repr(
# 38 "parser.mly"
             ( Program.CBool )
# 346 "parser.ml"
               : 'ctype))
; (fun __caml_parser_env ->
    Obj.repr(
# 39 "parser.mly"
            ( Program.CInt )
# 352 "parser.ml"
               : 'ctype))
; (fun __caml_parser_env ->
    Obj.repr(
# 41 "parser.mly"
                    ( [] )
# 358 "parser.ml"
               : 'args))
; (fun __caml_parser_env ->
    Obj.repr(
# 42 "parser.mly"
           ( [] )
# 364 "parser.ml"
               : 'args))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'arg) in
    Obj.repr(
# 43 "parser.mly"
          ( [_1] )
# 371 "parser.ml"
               : 'args))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arg) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'args) in
    Obj.repr(
# 44 "parser.mly"
                     ( _1 :: _3 )
# 379 "parser.ml"
               : 'args))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'ctype) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 46 "parser.mly"
                      ( (_1, _2) )
# 387 "parser.ml"
               : 'arg))
; (fun __caml_parser_env ->
    Obj.repr(
# 48 "parser.mly"
                      ( [] )
# 393 "parser.ml"
               : 'stmts))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'stmt) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stmts) in
    Obj.repr(
# 49 "parser.mly"
                   ( _1 :: _2 )
# 401 "parser.ml"
               : 'stmts))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stmts) in
    Obj.repr(
# 50 "parser.mly"
                        ( _2 )
# 408 "parser.ml"
               : 'stmts))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'exp) in
    Obj.repr(
# 52 "parser.mly"
                                      ( Program.Assign (_1, _3) )
# 416 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'ctype) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 53 "parser.mly"
                                 ( Program.LocalDecl (_1, _2) )
# 424 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'exps) in
    Obj.repr(
# 54 "parser.mly"
                                          ( Program.Call (_1, _3) )
# 432 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    Obj.repr(
# 55 "parser.mly"
                       ( Program.Return )
# 438 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'exp) in
    Obj.repr(
# 56 "parser.mly"
                           ( Program.ReturnValue _2 )
# 445 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 5 : 'exp) in
    let _6 = (Parsing.peek_val __caml_parser_env 2 : 'stmts) in
    let _8 = (Parsing.peek_val __caml_parser_env 0 : 'elseopt) in
    Obj.repr(
# 57 "parser.mly"
                                               ( Program.If (_3, _6, _8) )
# 454 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'exp) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'stmts) in
    Obj.repr(
# 58 "parser.mly"
                                          ( Program.While (_3, _6) )
# 462 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    Obj.repr(
# 60 "parser.mly"
                        ( [] )
# 468 "parser.ml"
               : 'elseopt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'stmts) in
    Obj.repr(
# 61 "parser.mly"
                               ( _3 )
# 475 "parser.ml"
               : 'elseopt))
; (fun __caml_parser_env ->
    Obj.repr(
# 63 "parser.mly"
                    ( [] )
# 481 "parser.ml"
               : 'exps))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 64 "parser.mly"
          ( [_1] )
# 488 "parser.ml"
               : 'exps))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exps) in
    Obj.repr(
# 65 "parser.mly"
                     ( _1 :: _3 )
# 496 "parser.ml"
               : 'exps))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 67 "parser.mly"
          ( Program.ConstInt _1 )
# 503 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    Obj.repr(
# 68 "parser.mly"
           ( Program.ConstBool true )
# 509 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    Obj.repr(
# 69 "parser.mly"
            ( Program.ConstBool false )
# 515 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 70 "parser.mly"
                 ( Program.Var _1 )
# 522 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'exps) in
    Obj.repr(
# 71 "parser.mly"
                                ( Program.CallExp (_1, _3) )
# 530 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 72 "parser.mly"
                   ( Program.Add (_1, _3) )
# 538 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 73 "parser.mly"
                    ( Program.Sub (_1, _3) )
# 546 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 74 "parser.mly"
                    ( Program.Mul (_1, _3) )
# 554 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 75 "parser.mly"
                     ( Program.Div (_1, _3) )
# 562 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 76 "parser.mly"
               ( _2 )
# 569 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 77 "parser.mly"
                ( Program.Neg _2 )
# 576 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 78 "parser.mly"
                    ( Program.Equal (_1, _3) )
# 584 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 79 "parser.mly"
                    ( Program.NotEq (_1, _3) )
# 592 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 80 "parser.mly"
                  ( Program.LessEq (_1, _3) )
# 600 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 81 "parser.mly"
                   ( Program.LessThan (_1, _3) )
# 608 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 82 "parser.mly"
                  ( Program.GreaterEq (_1, _3) )
# 616 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 83 "parser.mly"
                      ( Program.GreaterThan (_1, _3) )
# 624 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 84 "parser.mly"
                  ( Program.And (_1, _3) )
# 632 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'exp) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 85 "parser.mly"
                 ( Program.Or (_1, _3) )
# 640 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'exp) in
    Obj.repr(
# 86 "parser.mly"
              ( Program.Not _2 )
# 647 "parser.ml"
               : 'exp))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'exp) in
    Obj.repr(
# 87 "parser.mly"
                    ( _2 )
# 654 "parser.ml"
               : 'exp))
(* Entry program *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let program (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Program.program)
