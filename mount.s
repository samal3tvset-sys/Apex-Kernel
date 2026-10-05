.global mount_init
.global mount_device
.global unmount_device

.section .text

mount_init:
    xor %eax, %eax
    mov %eax, mount_count
    ret

mount_device:
    mov 4(%esp), %eax
    mov %eax, mount_table(,%eax,4)
    ret

unmount_device:
    mov 4(%esp), %eax
    movl $0, mount_table(,%eax,4)
    ret

.section .bss
.align 4
mount_table:
    .space 128
mount_count:
    .space 4