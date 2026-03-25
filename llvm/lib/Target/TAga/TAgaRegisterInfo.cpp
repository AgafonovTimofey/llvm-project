#include "TAgaRegisterInfo.h"
#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "TAgaFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "TAgaGenRegisterInfo.inc"

TAgaRegisterInfo::TAgaRegisterInfo() : TAgaGenRegisterInfo(TAga::R0) {}

const MCPhysReg *
TAgaRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_TAga_SaveList;
}

BitVector TAgaRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  TAgaFrameLowering const *TFI = getFrameLowering(MF);
  BitVector Reserved(getNumRegs());
  Reserved.set(TAga::R1);

  if (TFI->hasFP(MF))
    Reserved.set(TAga::R2);
  return Reserved;
}

bool TAgaRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool TAgaRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");
  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();
  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset))
    llvm_unreachable("Offset isn't int 16");

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register TAgaRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? TAga::R2 : TAga::R1;
}

const uint32_t *
TAgaRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const {
  return CSR_TAga_RegMask;
}
