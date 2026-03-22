#ifndef LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCASMINFO_H
#define LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class TAgaELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit TAgaELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCASMINFO_H