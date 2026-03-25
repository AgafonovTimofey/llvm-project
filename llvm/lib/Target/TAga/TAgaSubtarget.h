#ifndef LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H
#define LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H

#include "TAgaFrameLowering.h"
#include "TAgaISelLowering.h"
#include "TAgaInstrInfo.h"
#include "TAgaRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "TAgaGenSubtargetInfo.inc"

namespace llvm {

class TAgaSubtarget : public TAgaGenSubtargetInfo {
  TAgaTargetLowering TLInfo;
  TAgaFrameLowering FrameLowering;
  TAgaRegisterInfo RegInfo;
  TAgaInstrInfo InstrInfo;
  SelectionDAGTargetInfo TSInfo;

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

  const TAgaRegisterInfo *getRegisterInfo() const override { return &RegInfo; }

  const TAgaInstrInfo *getInstrInfo() const override { return &InstrInfo; }

  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGASUBTARGET_H