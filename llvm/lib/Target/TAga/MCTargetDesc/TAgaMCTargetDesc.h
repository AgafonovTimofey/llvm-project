#ifndef LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCTARGETDESC_H
#define LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCTARGETDESC_H

#include <memory>

#define GET_REGINFO_ENUM
#include "TAgaGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "TAgaGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TAgaGenSubtargetInfo.inc"

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCAsmBackend;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createTAgaMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createTAgaAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                   const MCRegisterInfo &MRI,
                                   const MCTargetOptions &Options);
std::unique_ptr<MCObjectTargetWriter> createTAgaELFObjectWriter(bool Is64Bit,
                                                                uint8_t OSABI);
} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_MCTARGETDESC_TAGAMCTARGETDESC_H