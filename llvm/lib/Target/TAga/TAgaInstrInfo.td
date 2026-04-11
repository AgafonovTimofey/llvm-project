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

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : TAgaInst<0xBB, (outs), (ins GPR:$r1), "br $r1",
                  [(brind GPR:$r1)]>;

let isReturn = 1, isTerminator = 1, hasSideEffects = 0 in
def RET : TAgaInst<0xFE, (outs), (ins), "ret", [(tAga_ret)]>;

let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1 in
def MOVLI : TAgaInst<0xAA, (outs GPR:$r1), (ins simm16:$r3_imm),
                     "mov $r1 $r3_imm",
                     [(set GPR:$r1, simm16:$r3_imm)]>;

let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : TAgaInst<0xFF, (outs), (ins), "FLUSH", [(int_taga_flush)]>;

def PUTPIXEL : TAgaInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_taga_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;