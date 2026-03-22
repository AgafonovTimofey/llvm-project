#include "TAgaMCTargetDesc.h"
#include "TargetInfo/TAgaTargetInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "TAgaGenRegisterInfo.inc"

static MCRegisterInfo *createTAgaMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTAgaMCRegisterInfo(X, TAga::R0);
  return X;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaTargetMC() {
  Target &TheTAgaTarget = getTheTAgaTarget();
  TargetRegistry::RegisterMCRegInfo(TheTAgaTarget, createTAgaMCRegisterInfo);
}
