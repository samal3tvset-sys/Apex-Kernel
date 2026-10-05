.global _start

.section .text

_start:
    cli

    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    mov $0x9000, %esp

    call kernel_main

.hang:
    hlt
    jmp .hang