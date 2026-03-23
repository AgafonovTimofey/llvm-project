#include "TAgaSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "tAgaSubtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TAgaGenSubtargetInfo.inc"

TAgaSubtarget::TAgaSubtarget(const Triple &TT, const std::string &CPU,
                             const std::string &FS, const TargetMachine &TM)
    : TAgaGenSubtargetInfo(TT, CPU, CPU, FS), TLInfo(TM, *this),
      FrameLowering(*this) {}
