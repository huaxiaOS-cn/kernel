/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 该文件定义了 架构下通用的 弱汇编函数，用于对未选择的功能进行处理
 */

SYM_FUNC_START_WEAK(__g_func_lookup_processor_type)
    bx lr
SYM_FUNC_END(__g_func_lookup_processor_type)