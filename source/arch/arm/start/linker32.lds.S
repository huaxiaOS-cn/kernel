/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 链接脚本的预处理
 */
OUTPUT_ARCH(arm)  // 指定输出文件的架构为ARM
ENTRY(stext)      // 指定内核的入口为stext

SECTIONS {
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}