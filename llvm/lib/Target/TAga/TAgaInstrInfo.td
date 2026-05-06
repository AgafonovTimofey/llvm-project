def tAga_ret : SDNode<"TAgaISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

include "TAgaInstrFormats.td"

class SImmAsmOperand<int width> : AsmOperandClass {
  let Name = "SImm" # width;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

def simm16 : Operand<i32>, ImmLeaf<i32, [{return isInt<16>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let EncoderMethod = "getSImm16OpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM16";
  let OperandNamespace = "TAgaOp";
}


def SDT_TAgaBrCC  : SDTypeProfile<0, 2, [ SDTCisVT<0, i32>,
                                         SDTCisVT<1, OtherVT>]>;

def taga_brcc     : SDNode<"TAgaISD::BR_CC", SDT_TAgaBrCC,
                            [SDNPHasChain]>;

let isReturn = 1, isTerminator = 1, hasSideEffects = 0, r1 = 0, r2 = 0, r3_imm = 0 in
def RET : TAgaInst<0xFE, (outs), (ins), "ret", [(tAga_ret)]>;

let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVLI : TAgaInst<0xAA, (outs GPR:$r1), (ins simm16:$r3_imm),
                     "mov $r1 $r3_imm",
                     [(set GPR:$r1, simm16:$r3_imm)]>;
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : TAgaInst<0xBB, (outs), (ins GPR:$r1), "br $r1",
                  [(brind GPR:$r1)]>;


def btarget16 : Operand<OtherVT> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getBranchTarget16OpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

def LI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() & 0xffff,
                                  SDLoc(N), MVT::i32);
}]>;

def HI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() >> 16, SDLoc(N),
                                  MVT::i32);
}]>;


let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0  in
def MOVHI : TAgaInst<0xAF, (outs GPR:$r1), (ins simm16:$r3_imm),
                    "MOVhi $r1 $r3_imm", []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ORI : TAgaInst<0x44, (outs GPR:$r1), (ins GPR:$r2, simm16:$r3_imm),
                  "ORi $r1 $r2 $r3_imm", [(set GPR:$r1, (or GPR:$r2, simm16:$r3_imm))]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBarrier = 1, isBranch = 1, isTerminator = 1, r1 = 0, r2 = 0 in
def B : TAgaInst<0xB0, (outs), (ins btarget16:$r3_imm), "B $r3_imm",
                [(br bb:$r3_imm)]>;


let r2 = 0, r3_imm = 0 in
def FLUSH : TAgaInst<0xFF, (outs GPR:$r1), (ins), "FLUSH $r1", [(set GPR:$r1, (int_taga_flush))]>;

def PUTPIXEL : TAgaInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_taga_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

let r2 = 0, r3_imm = 0 in
def SIMRAND : TAgaInst<0xEF, (outs GPR:$r1), (ins), "SIMRAND $r1", [(set GPR:$r1, (int_taga_simrand))]>;

def : Pat<(i32 imm:$imm),
          (ORI (MOVHI (HI16 imm:$imm)), (LI16 imm:$imm))>;

let isBranch = 1, isTerminator = 1, r2 = 0 in
def BR_COND : TAgaInst<0xBC, (outs), (ins GPR:$r1, btarget16:$r3_imm),
                      "BR_COND $r1 $r3_imm", [(taga_brcc GPR:$r1, bb:$r3_imm)]>;

def i32hi16 : Operand<i32>, PatLeaf<(i32 imm), [{
    // i32hi16 predicate - true if the 32-bit immediate has only leftmost 16
    // bits set.
    return ((N->getZExtValue() & 0xFFFF0000UL) == N->getZExtValue());}], HI16> {
}

def : Pat<(i32 i32hi16:$r3_imm), (MOVHI i32hi16:$r3_imm)>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ADD : TAgaInst<0x01, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "add $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (add GPR:$r2, GPR:$r3_imm))]>;
def : Pat<(add GPR:$r2, simm16:$r3_imm),
         (ADD GPR:$r2, (MOVLI simm16:$r3_imm))>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SUB : TAgaInst<0x02, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "sub $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (sub GPR:$r2, GPR:$r3_imm))]>;

def : Pat<(sub GPR:$r2, simm16:$r3_imm),
         (SUB GPR:$r2, (MOVLI simm16:$r3_imm))>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SRL : TAgaInst<0x10, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "srl $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (srl GPR:$r2, GPR:$r3_imm))]>;
def SRA : TAgaInst<0x11, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "sra $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (sra GPR:$r2, GPR:$r3_imm))]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def AND : TAgaInst<0x46, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "and $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (and GPR:$r2, GPR:$r3_imm))]>;
def : Pat<(setcc GPR:$lhs, GPR:$rhs, SETNE),
          (SRL (SUB GPR:$lhs, GPR:$rhs), (MOVLI 31))>;
def : Pat<(setcc GPR:$lhs, GPR:$rhs, SETEQ),
          (SUB (MOVLI 1), (SRL (SUB GPR:$lhs, GPR:$rhs), (MOVLI 31)))>;
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def MUL : TAgaInst<0x03, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                   "mul $r1, $r2, $r3_imm",
                   [(set GPR:$r1, (mul GPR:$r2, GPR:$r3_imm))]>;
def : Pat<(xor GPR:$src, (i32 -1)),
          (SUB (MOVLI -1), GPR:$src)>;
def : Pat<(setcc GPR:$lhs, GPR:$rhs, SETGT),
          (AND (SRA (SUB GPR:$rhs, GPR:$lhs), (MOVLI 31)), (MOVLI 1))>;
def : Pat<(setcc GPR:$lhs, GPR:$rhs, SETLT),
          (AND (SRA (SUB GPR:$lhs, GPR:$rhs), (MOVLI 31)), (MOVLI 1))>;
let mayLoad = 1, mayStore = 0, hasSideEffects = 0 in
def LD : TAgaInst<0x22, (outs GPR:$r1), (ins GPR:$r2, simm16:$r3_imm),
                  "ld $r1, [$r2, $r3_imm]",
                  [(set GPR:$r1, (load (add GPR:$r2, simm16:$r3_imm)))]>;

let mayLoad = 0, mayStore = 1, hasSideEffects = 0 in
def ST : TAgaInst<0x23, (outs), (ins GPR:$r1, GPR:$r2, simm16:$r3_imm),
                  "st $r1, [$r2, $r3_imm]",
                  [(store GPR:$r1, (add GPR:$r2, simm16:$r3_imm))]>;