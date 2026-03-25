#ifndef LLVM_LIB_TARGET_TAGA_TAGAMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_TAGA_TAGAMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

class TAgaFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();

  bool ReturnStackOffsetSet = false;
  unsigned ReturnStackOffset = -1U;

  int VarArgsFrameIndex = 0;
  int VarArgsSaveSize = 0;
  unsigned CalleeSavedStackSize = 0;

public:
  TAgaFunctionInfo() {}
  explicit TAgaFunctionInfo(MachineFunction &MF) {}
  ~TAgaFunctionInfo() {}

  void setVarArgsFrameIndex(int Off) { VarArgsFrameIndex = Off; }
  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

  void setVarArgsSaveSize(int Size) { VarArgsSaveSize = Size; }
  int getVarArgsSaveSize() const { return VarArgsSaveSize; }

  unsigned getCalleeSavedStackSize() const { return CalleeSavedStackSize; }
  void setCalleeSavedStackSize(unsigned Size) { CalleeSavedStackSize = Size; }

  void setReturnStackOffset(unsigned Off) {
    assert(!ReturnStackOffsetSet && "Return stack offset set twice");
    ReturnStackOffset = Off;
    ReturnStackOffsetSet = true;
  }

  unsigned getReturnStackOffset() const {
    assert(ReturnStackOffsetSet && "Return stack offset not set");
    return ReturnStackOffset;
  }
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_TAGA_TAGAMACHINEFUNCTIONINFO_H