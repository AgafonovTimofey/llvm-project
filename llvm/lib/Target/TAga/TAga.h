#ifndef LLVM_LIB_TARGET_TAGA_TAGA_H
#define LLVM_LIB_TARGET_TAGA_TAGA_H

#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TAgaTargetMachine;
class FunctionPass;

FunctionPass *createTAgaISelDag(TAgaTargetMachine &TM,
                                CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGA_H