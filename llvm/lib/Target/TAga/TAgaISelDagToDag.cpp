#include "MCTargetDesc/TAgaMCTargetDesc.h"
#include "TAga.h"
#include "TAgaISelLowering.h"
#include "TAgaTargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "tAgaDAGToDAGISel"

namespace {

class TAgaDAGToDAGISel : public SelectionDAGISel {
public:
  static char ID;
  TAgaDAGToDAGISel() = delete;
  explicit TAgaDAGToDAGISel(TAgaTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISel(TM, OptLevel) {}

  bool runOnMachineFunction(MachineFunction &MF) override {
    return SelectionDAGISel::runOnMachineFunction(MF);
  }

  void Select(SDNode *N) override;

#include "TAgaGenDAGISel.inc"
};
class TAgaDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;

  TAgaDAGToDAGISelLegacy(TAgaTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISelLegacy(
            ID, std::make_unique<TAgaDAGToDAGISel>(TM, OptLevel)) {}
  StringRef getPassName() const override {
    return "TAga DAG to DAG Pattern Instruction Selection";
  }
};
} // namespace

char TAgaDAGToDAGISelLegacy::ID = 0;

FunctionPass *llvm::createTAgaISelDag(TAgaTargetMachine &TM,
                                      CodeGenOptLevel OptLevel) {
  return new TAgaDAGToDAGISelLegacy(TM, OptLevel);
}

void TAgaDAGToDAGISel::Select(SDNode *Node) {
  if (Node->isMachineOpcode()) {
    Node->setNodeId(-1);
    return;
  }
  SDLoc DL(Node);
  SelectCode(Node);
}