#include "TAgaMCTargetDesc.h"
#include "MCTargetDesc/TAgaInfo.h"
#include "TargetInfo/TAgaTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "TAgaGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "TAgaGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TAgaGenSubtargetInfo.inc"

static MCRegisterInfo *createTAgaMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTAgaMCRegisterInfo(X, TAga::R0);
  return X;
}

static MCInstrInfo *createTAgaMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTAgaMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createTAgaMCSubtargetInfo(const Triple &TT,
                                                  StringRef CPU, StringRef FS) {
  return createTAgaMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaTargetMC() {
  Target &TheTAgaTarget = getTheTAgaTarget();
  TargetRegistry::RegisterMCRegInfo(TheTAgaTarget, createTAgaMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheTAgaTarget, createTAgaMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheTAgaTarget,
                                          createTAgaMCSubtargetInfo);
}
