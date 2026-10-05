.global init_sub_module

.section .text

init_sub_module:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
    test %eax, %eax
    jz .fail

    call *%eax

    mov $1, %eax
    pop %ebp
    ret

.fail:
    xor %eax, %eax
    pop %ebp
    ret