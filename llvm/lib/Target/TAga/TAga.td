include "llvm/Target/Target.td"
include "TAgaRegisterInfo.td"
include "TAgaInstrInfo.td"

def TAgaInstrInfo : InstrInfo;
def TAga : Target { let InstructionSet = TAgaInstrInfo; }
