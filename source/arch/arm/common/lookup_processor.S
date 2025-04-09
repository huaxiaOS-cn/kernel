/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 该文件定义了 查找处理器类型的功能
 */
#error "lookup_processor is not implemented yet."
.globl __g_func_lookup_processor_type
__g_func_lookup_processor_type:
    bx lr

    ENTRY(lookup_processor_type)
    stmfd    sp!, {r4 - r6, r9, lr}
    mov    r9, r0
    bl    __lookup_processor_type
    mov    r0, r5
    ldmfd    sp!, {r4 - r6, r9, pc}
ENDPROC(lookup_processor_type)

/*
 * 读取处理器ID寄存器（cp# 15, CR0），并在构建的链接中查找
 *    r9 = cpuid
 * 返回值:
 *    r3, r4, r6 在当前函数被使用，已被破坏
 *    r5 = 物理地址空间中 proc_info 结构体或者数据的指针
 *    r9 = cpuid
 */
__lookup_processor_type:
    /*
     * Look in <asm/procinfo.h> for information about the __proc_info
     * structure.
     */
    adr_l    r5, __proc_info_begin
    adr_l    r6, __proc_info_end
1:    ldmia    r5, {r3, r4}            @ value, mask
    and    r4, r4, r9            @ mask wanted bits
    teq    r3, r4
    beq    2f
    add    r5, r5, #PROC_INFO_SZ        @ sizeof(proc_info_list)
    cmp    r5, r6
    blo    1b
    mov    r5, #0                @ unknown processor
2:    ret    lr
ENDPROC(__lookup_processor_type)
