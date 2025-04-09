/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 该文件定义了 启动早期MMU的功能
 */
/* 启动MMU后，跳转到该函数 */
SYM_FUNC_START(__g_func_mmap_switched)
    mov    r7, r1
    mov    r8, r2
    mov    r10, r0

    adr    r4, __g_func_mmap_switched_data
    mov    fp, #0

    b    start_kernel
SYM_FUNC_END(__g_func_mmap_switched)

__g_func_mmap_switched_data: