#ifndef LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H
#define LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H

#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "TAgaGenSubtargetInfo.inc"

namespace llvm {

class TAgaSubtarget : public TAgaGenSubtargetInfo {
public:
  TAgaSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                const StringRef &FS, const TargetMachine &TM);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H