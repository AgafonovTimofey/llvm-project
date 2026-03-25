def RetCC_TAga : CallingConv<[
    CCIfType<[i32], CCAssignToReg<[R0]>>,
    CCIfType<[i64], CCAssignToReg<[R0, R1]>>,
    CCIfType<[i64], CCAssignToStack<8, 4>>,
    CCIfType<[i32], CCAssignToStack<4, 4>>
]>;
def CC_TAga : CallingConv<[
    CCIfType<[i8, i16], CCPromoteToType<i32>>,
    CCIfType<[i32, i64], CCAssignToReg<[R0, R1, R2, R3]>>,
    CCIfType<[i64], CCAssignToStack<8, 4>>,
    CCIfType<[i32], CCAssignToStack<4, 4>>
]>;
 
def CSR_TAga : CalleeSavedRegs<(add R10, R11, R12, R13, R14)>;
