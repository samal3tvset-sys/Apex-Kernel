.global _start

.section .text

_start:
    cli
    xor %eax, %eax
    mov %eax, %cr0

.hang:
    hlt
    jmp .hang