#include "TAgaTargetMachine.h"
#include "TargetInfo/TAgaTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaTarget() {
  RegisterTargetMachine<TAgaTargetMachine> A(getTheTAgaTarget());
}

TAgaTargetMachine::TAgaTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM,
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32",
                               TT, CPU, FS, Options, Reloc::Static,
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {

class TAgaPassConfig : public TargetPassConfig {
public:
  TAgaPassConfig(TAgaTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override { return false; }

  TAgaTargetMachine &getTAgaTargetMachine() const {
    return getTM<TAgaTargetMachine>();
  }
};

} // namespace

TargetPassConfig *TAgaTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TAgaPassConfig(*this, PM);
}

TargetLoweringObjectFile *TAgaTargetMachine::getObjFileLowering() const {
  return TLOF.get();
}
