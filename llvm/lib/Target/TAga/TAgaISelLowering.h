#ifndef LLVM_LIB_TARGET_TAGA_TAGAISELLOWERING_H
#define LLVM_LIB_TARGET_TAGA_TAGAISELLOWERING_H

#include "TAga.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class TAgaSubtarget;
class TAgaTargetMachine;

namespace TAgaISD {

enum NodeType : unsigned {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET,
  CALL,
  BR_CC,
};

}
} // namespace llvm
#endif // LLVM_LIB_TARGET_TAGA_TAGAISELLOWERING_H