# 1 "src/supervisorTrap.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/riscv64-linux-gnu/include/stdc-predef.h" 1 3
# 32 "<command-line>" 2
# 1 "src/supervisorTrap.S"






.extern _ZN5Riscv10handleTrapEv
.align 4
.global _ZN5Riscv14supervisorTrapEv
_ZN5Riscv14supervisorTrapEv:



    addi sp, sp, -256
    .irp param, 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\param, \param * 8(sp)
    .endr




    call _ZN5Riscv10handleTrapEv



    .irp param, 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
     ld x\param, \param * 8(sp)
    .endr
    addi sp, sp, 256
# 39 "src/supervisorTrap.S"
    sret
