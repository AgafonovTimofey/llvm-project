def RetCC_TAga : CallingConv<[
    CCIfType<[i32, i64], CCAssignToReg<[R9, R10, R11, R12]>>,
    CCIfType<[i64], CCAssignToStack<8, 4>>,
    CCIfType<[i32], CCAssignToStack<4, 4>>
]>;
def CC_TAga : CallingConv<[
    CCIfType<[i8, i16], CCPromoteToType<i32>>,
    CCIfType<[i32, i64], CCAssignToReg<[R9, R10, R11, R12]>>,
    CCIfType<[i64], CCAssignToStack<8, 4>>,
    CCIfType<[i32], CCAssignToStack<4, 4>>
]>;
 
def CSR_TAga : CalleeSavedRegs<(add R0, R1, R3, R5, R6, R7, R8)>;
 