#ifndef LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAINFO_H
#define LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace TAgaOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
};
} // namespace TAgaOp

} // end namespace llvm

#endif