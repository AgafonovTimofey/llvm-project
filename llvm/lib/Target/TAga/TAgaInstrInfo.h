#ifndef LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H
#define LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H

#include "MCTargetDesc/TAgaInfo.h"
#include "TAgaRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "TAgaGenInstrInfo.inc"

namespace llvm {

class TAgaSubtarget;

class TAgaInstrInfo : public TAgaGenInstrInfo {
public:
  TAgaInstrInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGAINSTRINFO_H