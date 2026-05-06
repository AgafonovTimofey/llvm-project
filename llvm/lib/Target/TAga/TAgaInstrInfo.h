#ifndef LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H
#define LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H

#include "MCTargetDesc/TAgaInfo.h"
#include "TAga.h"
#include "TAgaRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "TAgaGenInstrInfo.inc"

namespace llvm {

class TAgaSubtarget;

class TAgaInstrInfo : public TAgaGenInstrInfo {
public:
  TAgaInstrInfo();
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc, bool RenamableDest = false,
                   bool RenamableSrc = false) const override;

  void storeRegToStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, Register SrcReg,
      bool isKill, int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;

  void loadRegFromStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
      Register DestReg, int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H