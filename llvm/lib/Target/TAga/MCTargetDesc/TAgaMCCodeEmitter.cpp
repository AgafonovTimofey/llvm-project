#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "TAga.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/SubtargetFeature.h"
#include <cassert>
#include <cstdint>

using namespace llvm;

#define DEBUG_TYPE "TAgaMCCodeEmitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

namespace {

class TAgaMCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;

public:
  TAgaMCCodeEmitter(const MCInstrInfo &, MCContext &ctx) : Ctx(ctx) {}
  TAgaMCCodeEmitter(const TAgaMCCodeEmitter &) = delete;
  TAgaMCCodeEmitter &operator=(const TAgaMCCodeEmitter &) = delete;
  ~TAgaMCCodeEmitter() override = default;

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
  unsigned getSImm16OpValue(const MCInst &MI, unsigned OpNo,
                            SmallVectorImpl<MCFixup> &Fixups,
                            const MCSubtargetInfo &STI) const;
};

} // namespace

void TAgaMCCodeEmitter::encodeInstruction(const MCInst &MI,
                                          SmallVectorImpl<char> &CB,
                                          SmallVectorImpl<MCFixup> &Fixups,
                                          const MCSubtargetInfo &STI) const {
  unsigned Bits = getBinaryCodeForInstr(MI, Fixups, STI);
  support::endian::write(CB, Bits, llvm::endianness::little);

  ++MCNumEmitted;
}

unsigned
TAgaMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                     SmallVectorImpl<MCFixup> &Fixups,
                                     const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());
  if (MO.isImm())
    return MO.getImm();
  assert(MO.isExpr());
  const MCExpr *Expr = MO.getExpr();
  int64_t Res;
  if (Expr->evaluateAsAbsolute(Res))
    return Res;
  llvm_unreachable("Unhandled expression!");
  return 0;
}

unsigned TAgaMCCodeEmitter::getSImm16OpValue(const MCInst &MI, unsigned OpNo,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);
  if (MO.isImm())
    return MO.getImm();
  assert(MO.isExpr() &&
         "getSImm16OpValue expects only expressions or an immediate");
  const MCExpr *Expr = MO.getExpr();
  if (const MCConstantExpr *CE = dyn_cast<MCConstantExpr>(Expr))
    return CE->getValue();
  return 0;
}

#include "TAgaGenMCCodeEmitter.inc"

MCCodeEmitter *llvm::createTAgaMCCodeEmitter(const MCInstrInfo &MCII,
                                             MCContext &Ctx) {
  return new TAgaMCCodeEmitter(MCII, Ctx);
}