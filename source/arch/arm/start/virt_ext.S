/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/* 虚拟化扩展 */
// 该功能未实现，实现后删除此行注释
#error "Virtualization extension is not implemented yet."
.weak __hyp_stub_install
__hyp_stub_install:
    bx lr