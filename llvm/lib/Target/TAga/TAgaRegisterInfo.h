#ifndef LLVM_LIB_TARGET_TAGA_TAGAREGISTERINFO_H
#define LLVM_LIB_TARGET_TAGA_TAGAREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "TAgaGenRegisterInfo.inc"

namespace llvm {

struct TAgaRegisterInfo : public TAgaGenRegisterInfo {
public:
  TAgaRegisterInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGAREGISTERINFO_H