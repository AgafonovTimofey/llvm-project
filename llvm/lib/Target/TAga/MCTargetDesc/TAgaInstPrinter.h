#ifndef LLVM_LIB_TARGET_TAGA_INSTPRINTER_TAGAINSTPRINTER_H
#define LLVM_LIB_TARGET_TAGA_INSTPRINTER_TAGAINSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCRegister.h"

namespace llvm {

class TAgaInstPrinter : public MCInstPrinter {
public:
  TAgaInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                  const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  std::pair<const char *, uint64_t>
  getMnemonic(const MCInst &MI) const override;
  void printInstruction(const MCInst *MI, uint64_t Address, raw_ostream &O);

  static const char *getRegisterName(MCRegister Reg);
  static void printOperand(const MCOperand &MO, raw_ostream &O);

  void printRegName(raw_ostream &O, MCRegister Reg) override;
  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &O) override;
  void printOperand(const MCInst *MI, int OpNo, raw_ostream &OS);
  void printBranchOperand(const MCInst *MI, uint64_t Address, unsigned OpNo,
                          raw_ostream &O);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_INSTPRINTER_TAGAINSTPRINTER_H