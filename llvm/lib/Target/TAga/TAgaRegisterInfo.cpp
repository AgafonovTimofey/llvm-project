#include "TAgaRegisterInfo.h"
#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "TAgaFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "TAgaGenRegisterInfo.inc"

TAgaRegisterInfo::TAgaRegisterInfo() : TAgaGenRegisterInfo(TAga::R0) {}