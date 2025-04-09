/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 定义链接脚本的辅助宏头文件，用于支持编写架构特定的链接脚本。
 * [这是一个示例，具体架构可能有特殊要求]
 * OUTPUT_FORMAT(...)                   // 指定输出文件格式
 * OUTPUT_ARCH(...)                     // 指定目标架构
 * ENTRY(stext)                         // 指定程序入口点
 * SECTIONS                                // 定义段布局
 * {
 *     . = START;                          // 设置起始地址
 * 
 *     __init_begin = .;                   // 初始化段的开始
 *     . = ALIGN(__SYS_PAGE_SIZE__);
 *     .init.text : { *(.init.text) }      // 初始化代码段
 *     .init.data : { *(.init.data) }      // 初始化数据段
 *     . = ALIGN(__SYS_PAGE_SIZE__);
 *     __init_end = .;                     // 初始化段的结束
 * 
 *     _stext = .;                         // 代码段的开始
 *     .text : { *(.text) }                // 代码段
 *     . = ALIGN(__SYS_PAGE_SIZE__);
 *     _etext = .;                         // 代码段的结束
 * 
 *     _sdata = .;                         // 数据段的开始
 *     .data : { *(.data) }                // 数据段
 *     .rodata : { *(.rodata) }            // 只读数据段
 *     . = ALIGN(__SYS_PAGE_SIZE__);
 *     _edata = .;                         // 数据段的结束
 * 
 *     _sbss = .;                          // BSS段的开始
 *     .bss : { *(.bss) }                  // BSS段
 *     . = ALIGN(__SYS_PAGE_SIZE__);
 *     _ebss = .;                          // BSS段的结束
 * 
 *     _end = .;                           // 段的结束
 * }
 *
 * [__init_begin, __init_end] 是初始化段，初始化完成后可以释放
 *  // __init_begin 和 __init_end 应该按页对齐，以便释放整个 .init 内存
 * [_stext, _etext] 是代码段
 * [_sdata, _edata] 是数据段
 * [_sbss, _ebss] 是BSS段
 */
// bootloader应当将内核加载到正确的内存地址，kernel不会保证
#ifndef __LINKER_LDS_H__
#define __LINKER_LDS_H__

// 调试信息段定义，包含 DWARF 调试信息，包括调试符号表、行号信息等
#define DWARF_DEBUG                            \
        /* DWARF 1 */                        \
        .debug          0 : { *(.debug) }            \
        .line           0 : { *(.line) }            \
        /* GNU DWARF 1 extensions */                \
        .debug_srcinfo  0 : { *(.debug_srcinfo) }        \
        .debug_sfnames  0 : { *(.debug_sfnames) }        \
        /* DWARF 1.1 and DWARF 2 */                \
        .debug_aranges  0 : { *(.debug_aranges) }        \
        .debug_pubnames 0 : { *(.debug_pubnames) }        \
        /* DWARF 2 */                        \
        .debug_info     0 : { *(.debug_info            \
                .gnu.linkonce.wi.*) }            \
        .debug_abbrev   0 : { *(.debug_abbrev) }        \
        .debug_line     0 : { *(.debug_line) }            \
        .debug_frame    0 : { *(.debug_frame) }            \
        .debug_str      0 : { *(.debug_str) }            \
        .debug_loc      0 : { *(.debug_loc) }            \
        .debug_macinfo  0 : { *(.debug_macinfo) }        \
        .debug_pubtypes 0 : { *(.debug_pubtypes) }        \
        /* DWARF 3 */                        \
        .debug_ranges    0 : { *(.debug_ranges) }        \
        /* SGI/MIPS DWARF 2 extensions */            \
        .debug_weaknames 0 : { *(.debug_weaknames) }        \
        .debug_funcnames 0 : { *(.debug_funcnames) }        \
        .debug_typenames 0 : { *(.debug_typenames) }        \
        .debug_varnames  0 : { *(.debug_varnames) }        \
        /* GNU DWARF 2 extensions */                \
        .debug_gnu_pubnames 0 : { *(.debug_gnu_pubnames) }    \
        .debug_gnu_pubtypes 0 : { *(.debug_gnu_pubtypes) }    \
        /* DWARF 4 */                        \
        .debug_types    0 : { *(.debug_types) }            \
        /* DWARF 5 */                        \
        .debug_addr    0 : { *(.debug_addr) }            \
        .debug_line_str    0 : { *(.debug_line_str) }        \
        .debug_loclists    0 : { *(.debug_loclists) }        \
        .debug_macro    0 : { *(.debug_macro) }            \
        .debug_names    0 : { *(.debug_names) }            \
        .debug_rnglists    0 : { *(.debug_rnglists) }        \
        .debug_str_offsets    0 : { *(.debug_str_offsets) }

#endif /* __LINKER_LDS_H__ */

