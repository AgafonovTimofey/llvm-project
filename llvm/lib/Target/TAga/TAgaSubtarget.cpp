#include "TAgaSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "tAgaSubtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TAgaGenSubtargetInfo.inc"

TAgaSubtarget::TAgaSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                             const StringRef &FS, const TargetMachine &TM)
    : TAgaGenSubtargetInfo(TM.getTargetTriple(), CPU, TuneCPU, FS) {}
