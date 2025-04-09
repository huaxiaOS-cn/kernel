/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 该文件定义了 启动阶段 弱汇编函数，用于对未选择的功能进行处理
 */

.weak __g_func_hyp_stub_install
__g_func_hyp_stub_install:
    bx lr
