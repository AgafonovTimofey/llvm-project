add_llvm_component_library(LLVMTAgaDesc
  TAgaMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  Support
  TAgaInfo

  ADD_TO_COMPONENT
  TAga
 )