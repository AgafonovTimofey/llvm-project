add_llvm_component_group(TAga)

add_llvm_target(TAgaCodeGen
  TAgaTargetMachine.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  TAgaInfo

  ADD_TO_COMPONENT
  TAga
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)