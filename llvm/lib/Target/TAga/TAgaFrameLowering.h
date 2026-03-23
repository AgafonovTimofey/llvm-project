#ifndef LLVM_LIB_TARGET_TAGA_TAGAFRAMELOWERING_H
#define LLVM_LIB_TARGET_TAGA_TAGAFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class TAgaSubtarget;

class TAgaFrameLowering : public TargetFrameLowering {
  const TAgaSubtarget &STI;

public:
  explicit TAgaFrameLowering(const TAgaSubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0),
        STI(STI) {}

  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  bool hasFPImpl(const MachineFunction &MF) const override { return false; }
};

} // namespace llvm

#endif