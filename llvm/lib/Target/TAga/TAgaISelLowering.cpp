#include "TAgaISelLowering.h"
#include "TAga.h"
#include "TAgaRegisterInfo.h"
#include "TAgaSubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFunction.h"

#define DEBUG_TYPE "TAgaISelLowering"

using namespace llvm;

TAgaTargetLowering::TAgaTargetLowering(const TargetMachine &TM,
                                       const TAgaSubtarget &STI)
    : TargetLowering(TM), STI(STI) {
  addRegisterClass(MVT::i32, &TAga::GPRRegClass);
}

const char *TAgaTargetLowering::getTargetNodeName(unsigned OpCode) const {
  switch (OpCode) {
  case TAgaISD::CALL:
    return "TAgaISD::CALL";
  case TAgaISD::RET:
    return "TAgaISD::RET";
  case TAgaISD::BR_CC:
    return "TAgaISD::BR_CC";
  }
  return nullptr;
}
