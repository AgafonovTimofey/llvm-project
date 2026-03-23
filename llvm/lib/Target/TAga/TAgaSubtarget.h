#ifndef LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H
#define LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H

#include "TAgaFrameLowering.h"
#include "TAgaISelLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "TAgaGenSubtargetInfo.inc"

namespace llvm {

class TAgaSubtarget : public TAgaGenSubtargetInfo {
  TAgaTargetLowering TLInfo;
  TAgaFrameLowering FrameLowering;

public:
  TAgaSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
                const TargetMachine &TM);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  const TAgaTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }

  const TAgaFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H