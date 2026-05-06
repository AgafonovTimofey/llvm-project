let TargetPrefix = "taga" in {  // All intrinsics start with "llvm.taga.".
 
 def int_taga_putpixel: ClangBuiltin<"simPutPixel">,
   Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;
 
 def int_taga_flush: ClangBuiltin<"simFlush">,
   Intrinsic<[llvm_i32_ty], [], [IntrNoMem, IntrHasSideEffects]>;
 
 def int_taga_simrand: ClangBuiltin<"simRand">,
   Intrinsic<[llvm_i32_ty], [], [IntrNoMem]>;
 } // TargetPrefix = "taga"