#ifndef LLVM_LIB_TARGET_TAGA_TAGATARGETMACHINE_H
#define LLVM_LIB_TARGET_TAGA_TAGATARGETMACHINE_H

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target TheTAgaTarget;

class TAgaTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  TAgaTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM,
                    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                    bool JIT);

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGATARGETMACHINE_H
