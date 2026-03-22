#include "MCTargetDesc/TAgaInstPrinter.h"
#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "TAgaSubtarget.h"
#include "TAgaTargetMachine.h"
#include "TargetInfo/TAgaTargetInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "TAgaAsmPriner"

namespace {

class TAgaAsmPrinter : public AsmPrinter {
  const MCSubtargetInfo *STI;

public:
  explicit TAgaAsmPrinter(TargetMachine &TM,
                          std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), STI(TM.getMCSubtargetInfo()) {}

  void emitInstruction(const MachineInstr *MI) override;

  StringRef getPassName() const override { return "TAgaAssemblyPrinter"; }

  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
};

} // namespace

#include "TAgaGenMCPseudoLowering.inc"

void TAgaAsmPrinter::emitInstruction(const MachineInstr *MI) {
  MCInst OutInst;
  if (lowerPseudoInstExpansion(MI, OutInst)) {
    EmitToStreamer(*OutStreamer, OutInst);
    return;
  }
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTAgaAsmPrinter() {
  RegisterAsmPrinter<TAgaAsmPrinter> X(getTheTAgaTarget());
}