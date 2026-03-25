#include "TAgaMCTargetDesc.h"
#include "MCTargetDesc/TAgaInfo.h"
#include "TAgaInstPrinter.h"
#include "TAgaMCAsmInfo.h"
#include "TargetInfo/TAgaTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "TAgaGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "TAgaGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TAgaGenSubtargetInfo.inc"

static MCRegisterInfo *createTAgaMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTAgaMCRegisterInfo(X, TAga::R7);
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

static MCAsmInfo *createTAgaMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new TAgaELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(TAga::R9, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createTAgaMCInstPrinter(const Triple &T,
                                              unsigned SyntaxVariant,
                                              const MCAsmInfo &MAI,
                                              const MCInstrInfo &MII,
                                              const MCRegisterInfo &MRI) {
  return new TAgaInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaTargetMC() {
  Target &TheTAgaTarget = getTheTAgaTarget();
  TargetRegistry::RegisterMCRegInfo(TheTAgaTarget, createTAgaMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheTAgaTarget, createTAgaMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheTAgaTarget,
                                          createTAgaMCSubtargetInfo);
  RegisterMCAsmInfoFn X(TheTAgaTarget, createTAgaMCAsmInfo);
  TargetRegistry::RegisterMCInstPrinter(TheTAgaTarget, createTAgaMCInstPrinter);
}
