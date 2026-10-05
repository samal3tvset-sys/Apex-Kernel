.global jump_in_64
.global long_mode_start

.section .text

jump_in_64:
    cli

    mov $stack_top, %esp

    lgdt gdt_descriptor

    mov %cr4, %eax
    or $0x20, %eax
    mov %eax, %cr4

    mov $page_table, %eax
    mov %eax, %cr3

    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0

    ljmp $0x08, $long_mode_start

.section .bss
.align 16
stack:
    .space 4096
stack_top:

.section .data
gdt_descriptor:
    .word gdt_end - gdt - 1
    .long gdt

gdt:
    .quad 0x0000000000000000
    .quad 0x00AF9A000000FFFF
    .quad 0x00AF92000000FFFF

gdt_end:

page_table:
    .space 4096