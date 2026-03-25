include "llvm/Target/Target.td"
include "TAgaRegisterInfo.td"
include "TAgaInstrInfo.td"
include "TAgaCallingConv.td"

def TAgaInstrInfo : InstrInfo;
def TAga : Target { let InstructionSet = TAgaInstrInfo; }

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;
