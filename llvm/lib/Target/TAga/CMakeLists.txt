add_llvm_component_group(TAga)

set(LLVM_TARGET_DEFINITIONS TAga.td)

tablegen(LLVM TAgaGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TAgaGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TAgaGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(TAgaCommonTableGen)


add_llvm_target(TAgaCodeGen
  TAgaTargetMachine.cpp
  TAgaRegisterInfo.cpp
  TAgaInstrInfo.cpp
  TAgaSubtarget.cpp

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