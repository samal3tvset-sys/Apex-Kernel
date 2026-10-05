.global mmu_init
.global load_page_dir
.global enable_paging

.section .text

mmu_init:
    mov $page_directory, %eax
    mov %eax, %cr3

    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0

    ret

load_page_dir:
    mov 4(%esp), %eax
    mov %eax, %cr3
    ret

enable_paging:
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
    ret

.section .bss
.align 4096
page_directory:
    .space 4096