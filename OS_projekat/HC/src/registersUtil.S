.global _ZN5Riscv13pushRegistersEv
_ZN5Riscv13pushRegistersEv:
    addi sp, sp, -256 //stek raste ka nizim adresama tako da za alokaciju prostora za stek moramo da od SP oduzmemo 256
    //x0 je 0 pa ne mora da se cuva
    //x1 je ra a x2 je sp to cuvamo u okviru Context strukture unutar CCB-a


    // .irp param, 1,2,3
    // move d\param,sp
    // .endr

    //se preslikava u

    // move d1,sp
    // move d2,sp
    // move d3,sp

    .irp param, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
     sd x\param, \param * 8(sp) //pushovanje svih registara
    .endr

    ret


.global _ZN5Riscv12popRegistersEv
_ZN5Riscv12popRegistersEv:


    .irp param, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
     ld x\param, \param * 8(sp) //popovanje svih registara
    .endr


    addi sp, sp, 256 //oslobadjanje prostora za stek
    ret



