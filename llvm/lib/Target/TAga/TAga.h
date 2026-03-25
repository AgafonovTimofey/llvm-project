#ifndef LLVM_LIB_TARGET_TAGA_TAGA_H
#define LLVM_LIB_TARGET_TAGA_TAGA_H

#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TAgaTargetMachine;
class FunctionPass;
class TAgaSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerTAgaMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                   AsmPrinter &AP);
bool LowerTAgaMachineOperandToMCOperand(const MachineOperand &MO,
                                        MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createTAgaISelDag(TAgaTargetMachine &TM,
                                CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGA_H