/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
/* 
 * 定义 Linux 内核中与链接相关的宏和类型
 */
#ifndef __LINKAGE_H__
#define __LINKAGE_H__

/* 一些工具链使用其他字符(例如: '`')在宏中标记新行 */
#ifndef ASM_NL
#define ASM_NL ;
#endif

/* 确保在 C++ 代码中调用 C 函数时，函数名能够正确链接，避免因 C++ 的名称修饰机制导致的链接错误。在 C 代码中，这个宏不会产生任何效果 */
#ifdef __cplusplus
#define CPP_ASMLINKAGE extern "C"
#else
#define CPP_ASMLINKAGE
#endif

/* 
 * 定义 asmlinkage 宏，用于标记函数为内联函数。在内联函数中，函数的代码会被直接插入到调用它的地方，
 * 而不是通过函数调用的方式执行。这样可以减少函数调用的开销，提高程序的执行效率。
 */
#ifndef asmlinkage
#define asmlinkage CPP_ASMLINKAGE
#endif

/* 定义 cond_syscall 宏，定义一个条件系统调用。如果某个系统调用函数 x 未实现，则将其设置为 sys_ni_syscall，这样可以避免链接错误 */
#ifndef cond_syscall
#define cond_syscall(x) asm( \
    ".weak " __stringify(x) "\n\t" \
    ".set  " __stringify(x) "," \
    __stringify(sys_ni_syscall))
#endif

/* 该宏由编译器设置，确保在汇编语言和 C 语言混合编程时，栈上的参数不会被编译器错误地修改或优化掉 */
#ifndef __ASSEMBLY__
    #ifndef asmlinkage_protect
    #define asmlinkage_protect(n, ret, args...) do { } while (0)
    #endif
#endif

#ifdef __ASSEMBLY__
/* SYM_T_FUNC -- 汇编 用来标记函数类型的符号 */
#ifndef SYM_T_FUNC
#define SYM_T_FUNC STT_FUNC
#endif

/* SYM_T_OBJECT -- 汇编 用于标记数据的符号 */
#ifndef SYM_T_OBJECT
#define SYM_T_OBJECT STT_OBJECT
#endif

/* SYM_T_NONE -- 汇编 用于标记未知类型的项 */
#ifndef SYM_T_NONE
#define SYM_T_NONE STT_NOTYPE
#endif

/* SYM_A_* -- 是否对齐 */
#define SYM_A_ALIGN ALIGN
#define SYM_A_NONE /* nothing */

/* SYM_L_* -- 符号链接 */
#define SYM_L_GLOBAL(name) .globl name
#define SYM_L_WEAK(name) .weak name
#define SYM_L_LOCAL(name) /* nothing */

/*------------------------以下为通用的----------------------------------------*/
/* SYM_ENTRY -- 只有在必须使用非成对符号时才使用，可替代 GLOBAL 宏 */
#ifndef SYM_ENTRY
#define SYM_ENTRY(name, linkage, align...) \
    linkage(name) ASM_NL \
    align ASM_NL \
    name:
#endif

/* SYM_START -- 必要时才使用 */
#ifndef SYM_START
#define SYM_START(name, linkage, align...) \
    SYM_ENTRY(name, linkage, align)
#endif

/* SYM_END -- 必要时才使用 */
#ifndef SYM_END
#define SYM_END(name, sym_type) \
    .type name sym_type ASM_NL \
    .set .L__sym_size_##name, .-name ASM_NL \
    .size name, .L__sym_size_##name
#endif

/* SYM_ALIAS -- 必要时才使用 */
#ifndef SYM_ALIAS
#define SYM_ALIAS(alias, name, linkage) \
    linkage(alias) ASM_NL \
    .set alias, name ASM_NL
#endif

/*------------------------以下为代码相关的----------------------------------------*/
/*
 * 功能分类
 * FUNC：用于标记类似 C 的函数（具有标准的栈帧等）。
 * CODE：用于非 C 代码（例如中断处理程序，具有不同的特殊栈等）。
 * 工具支持
 * Objtool：
 * 对 FUNC 进行栈验证，但对 CODE 不进行验证。
 * 为 FUNC 和 CODE 生成调试信息，但需要为每个 CODE 的开始添加特殊注释（以描述实际的栈帧）。
 * 符号要求
 * ELF 符号：objtool 要求所有代码必须包含在 ELF 符号中。
 * 以 .L 为前缀的符号不会生成符号表条目。
 * .L 前缀的符号可以在代码区域内使用，但应避免用于通过 SYM_*_START/END 注释表示代码范围。
 * 别名
 * ALIAS：不会生成调试信息 —— 被别名的函数会生成调试信息。
 */

/* SYM_INNER_LABEL_ALIGN -- 专门用于在代码中间定义标签，而不是用于标记函数或代码段的开始或结束 */
#ifndef SYM_INNER_LABEL_ALIGN
#define SYM_INNER_LABEL_ALIGN(name, linkage) \
    .type name SYM_T_NONE ASM_NL \
    SYM_ENTRY(name, linkage, SYM_A_ALIGN)
#endif

/* SYM_INNER_LABEL -- 专门用于在代码中间定义标签，而不是用于标记函数或代码段的开始或结束 */
#ifndef SYM_INNER_LABEL
#define SYM_INNER_LABEL(name, linkage) \
    .type name SYM_T_NONE ASM_NL \
    SYM_ENTRY(name, linkage, SYM_A_NONE)
#endif

/* SYM_FUNC_START -- 用于全局函数，也可替代 ENTRY 宏 */
#ifndef SYM_FUNC_START
#define SYM_FUNC_START(name) \
    SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#endif

/* SYM_FUNC_START_NOALIGN -- 用于定义全局函数，但不会自动对齐函数的起始地址 */
#ifndef SYM_FUNC_START_NOALIGN
#define SYM_FUNC_START_NOALIGN(name) \
    SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#endif

/* SYM_FUNC_START_LOCAL -- 用于局部函数 */
#ifndef SYM_FUNC_START_LOCAL
#define SYM_FUNC_START_LOCAL(name) \
    SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#endif

/* SYM_FUNC_START_LOCAL_NOALIGN -- 用于定义局部函数，但不会自动对齐函数的起始地址 */
#ifndef SYM_FUNC_START_LOCAL_NOALIGN
#define SYM_FUNC_START_LOCAL_NOALIGN(name) \
    SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#endif

/* SYM_FUNC_START_WEAK -- 用于弱函数，可替代 WEAK 宏 */
#ifndef SYM_FUNC_START_WEAK
#define SYM_FUNC_START_WEAK(name) \
    SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)
#endif

/* SYM_FUNC_START_WEAK_NOALIGN -- 用于弱函数，但不会自动对齐函数的起始地址 */
#ifndef SYM_FUNC_START_WEAK_NOALIGN
#define SYM_FUNC_START_WEAK_NOALIGN(name) \
    SYM_START(name, SYM_L_WEAK, SYM_A_NONE)
#endif

/*
 * SYM_FUNC_END -- 用于标记函数的结束，通常与 SYM_FUNC_START_LOCAL SYM_FUNC_START 
 *     SYM_FUNC_START_WEAK 等宏配对使用，表示函数的结束
 */
#ifndef SYM_FUNC_END
#define SYM_FUNC_END(name) \
    SYM_END(name, SYM_T_FUNC)
#endif

/*
 * SYM_FUNC_ALIAS -- 为现有函数定义全局别名
 */
#ifndef SYM_FUNC_ALIAS
#define SYM_FUNC_ALIAS(alias, name) \
    SYM_ALIAS(alias, name, SYM_L_GLOBAL)
#endif

/*
 * SYM_FUNC_ALIAS_LOCAL -- 为现有函数定义一个局部别名
 */
#ifndef SYM_FUNC_ALIAS_LOCAL
#define SYM_FUNC_ALIAS_LOCAL(alias, name) \
    SYM_ALIAS(alias, name, SYM_L_LOCAL)
#endif

/*
 * SYM_FUNC_ALIAS_WEAK -- 为现有函数定义弱全局别名
 */
#ifndef SYM_FUNC_ALIAS_WEAK
#define SYM_FUNC_ALIAS_WEAK(alias, name) \
    SYM_ALIAS(alias, name, SYM_L_WEAK)
#endif

/* SYM_CODE_START -- 用于非 C 语言（特殊）函数 */
#ifndef SYM_CODE_START
#define SYM_CODE_START(name) \
    SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#endif

/* SYM_CODE_START_NOALIGN -- 用于非 C 语言（特殊）函数，但不会自动对齐函数的起始地址 */
#ifndef SYM_CODE_START_NOALIGN
#define SYM_CODE_START_NOALIGN(name) \
    SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#endif

/* SYM_CODE_START_LOCAL -- 用于非 C 语言（特殊）局部函数 */
#ifndef SYM_CODE_START_LOCAL
#define SYM_CODE_START_LOCAL(name) \
    SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#endif

/*
 * SYM_CODE_START_LOCAL_NOALIGN -- 用于非 C 语言（特殊）局部函数，但不会自动对齐函数的起始地址
 */
#ifndef SYM_CODE_START_LOCAL_NOALIGN
#define SYM_CODE_START_LOCAL_NOALIGN(name) \
    SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#endif

/* SYM_CODE_END -- 用于标记函数的结束，通常与 SYM_CODE_START_LOCAL SYM_CODE_START 等配对使用 */
#ifndef SYM_CODE_END
#define SYM_CODE_END(name) \
    SYM_END(name, SYM_T_NONE)
#endif

/*------------------------以下为数据相关的----------------------------------------*/

/* SYM_DATA_START -- 全局数据符号 */
#ifndef SYM_DATA_START
#define SYM_DATA_START(name) \
    SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#endif

/* SYM_DATA_START -- 局部数据符号 */
#ifndef SYM_DATA_START_LOCAL
#define SYM_DATA_START_LOCAL(name) \
    SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#endif

/* SYM_DATA_END -- 用于结束 SYM_DATA_START 数据符号 */
#ifndef SYM_DATA_END
#define SYM_DATA_END(name) \
    SYM_END(name, SYM_T_OBJECT)
#endif

/* SYM_DATA_END_LABEL -- SYM_DATA_START 数据符号结束后的标签 */
#ifndef SYM_DATA_END_LABEL
#define SYM_DATA_END_LABEL(name, linkage, label) \
    linkage(label) ASM_NL \
    .type label SYM_T_OBJECT ASM_NL \
    label: \
    SYM_END(name, SYM_T_OBJECT)
#endif

/* SYM_DATA -- start+end wrapper around simple global data */
#ifndef SYM_DATA
#define SYM_DATA(name, data...) \
    SYM_DATA_START(name) ASM_NL \
    data ASM_NL \
    SYM_DATA_END(name)
#endif

/* SYM_DATA_LOCAL -- start+end wrapper around simple local data */
#ifndef SYM_DATA_LOCAL
#define SYM_DATA_LOCAL(name, data...) \
    SYM_DATA_START_LOCAL(name) ASM_NL \
    data ASM_NL \
    SYM_DATA_END(name)
#endif

#endif

#endif /* __LINKAGE_H__ */

