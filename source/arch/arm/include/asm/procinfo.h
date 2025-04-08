/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/*
 * 该文件定义 启动阶段 处理器相关的汇编函数
 */

#ifndef __ASM_PROCINFO_H
#define __ASM_PROCINFO_H

#ifdef __KERNEL__ // 如果是内核代码

struct cpu_tlb_fns;
struct cpu_user_fns;
struct cpu_cache_fns;
struct processor;
/*
 *请注意!结构体处理器总是被定义
 *使用MULTI_CPU，否则该项是未使用的，但仍然存在。
 *请注意!下列结构由程序集定义语言，不是C代码。有关更多信息，请查看：
 * arch/arm/mm/proc-*.S and arch/arm/kernel/head.S
 */
struct proc_info_list {
    unsigned int        cpu_val;    // 处理器ID寄存器
    unsigned int        cpu_mask;   // 处理器掩码
    unsigned long        __cpu_mm_mmu_flags;    /* used by head.S */
    unsigned long        __cpu_io_mmu_flags;    /* used by head.S */
    unsigned long        __cpu_flush;        /* used by head.S */
    const char        *arch_name;
    const char        *elf_name;
    unsigned int        elf_hwcap;
    const char        *cpu_name;
    struct processor    *proc;
    struct cpu_tlb_fns    *tlb;
    struct cpu_user_fns    *user;
    struct cpu_cache_fns    *cache;
};
#endif    