/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 链接脚本的预处理,可参考 include/asm/linkage.lds.h
 */
#include "source/include/asm/linker.lds.h"
OUTPUT_ARCH(arm)                        // 指定输出文件的架构为ARM
ENTRY(stext)                            // 指定内核的入口为stext

SECTIONS                                // 定义段布局
{
    . = START;                          // 设置起始地址

    __init_begin = .;                   // 初始化段的开始
    . = ALIGN(__SYS_PAGE_SIZE__);
    .init.text : { *(.init.text) }      // 初始化代码段
    .init.data : { *(.init.data) }      // 初始化数据段
    . = ALIGN(__SYS_PAGE_SIZE__);
    __init_end = .;                     // 初始化段的结束

    _stext = .;                         // 代码段的开始
    .text : { *(.text) 
              *(.text.*)
            }                           // 代码段
    . = ALIGN(__SYS_PAGE_SIZE__);
    _etext = .;                         // 代码段的结束

    _sdata = .;                         // 数据段的开始
    .data : { *(.data) 
              *(.data.*)
            }                           // 数据段
    .rodata : { *(.rodata) 
                *(.rodata*)
              }                         // 只读数据段
    . = ALIGN(__SYS_PAGE_SIZE__);
    _edata = .;                         // 数据段的结束

    _sbss = .;                          // BSS段的开始
    .bss : { *(.bss)
             *(.bss.*)
           }                  // BSS段
    . = ALIGN(__SYS_PAGE_SIZE__);
    _ebss = .;                          // BSS段的结束

    DWARF_DEBUG                         // 包含DWARF调试信息

    _end = .;                           // 段的结束
}
