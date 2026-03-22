#ifndef LLVM_LIB_TARGET_TAGA_TAGAFRAMELOWERING_H
#define LLVM_LIB_TARGET_TAGA_TAGAFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class TAgaFrameLowering : public TargetFrameLowering {
public:
  explicit TAgaFrameLowering()
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0) {}

  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  bool hasFPImpl(const MachineFunction &MF) const override { return false; }
};

} // namespace llvm

#endif