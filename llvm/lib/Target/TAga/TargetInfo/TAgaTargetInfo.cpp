#include "TAgaTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheTAgaTarget() {
  static Target TheTAgaTarget;
  return TheTAgaTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaTargetInfo() {
  RegisterTarget<Triple::taga> X(getTheTAgaTarget(), "taga",
                                 "Simulator target for LLVM course", "TAGA");
}
