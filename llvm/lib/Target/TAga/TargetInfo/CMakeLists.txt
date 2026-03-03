add_llvm_component_library(LLVMTAgaInfo
  TAgaTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  TAga
  )