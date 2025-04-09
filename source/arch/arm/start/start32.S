/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (C) 2025 huaxiaOS
 * This file is encoded in UTF-8. 
 * If there is garbled text, please open it in this format.
 */
 /*
 * 该文件是32位系统的启动代码
 * 这个文件应当由解压缩代码调用，它的主要功能是初始化MMU，设置页表，然后跳转到内核代码
 */

// 对齐要求是为了确保页表的地址符合处理器的内存管理单元（MMU）的要求，避免因地址不对齐而导致的性能问题或错误。
#define KERNEL_RAM_VADDR    (__SYS_PAGE_OFFSET__ + __SYS_KERNEL_OFFSET__)
#if (KERNEL_RAM_VADDR & 0xffff) != 0x8000
    #error KERNEL_RAM_VADDR 最低16BIT必须为 0x8000
#endif

// 当前不支持 大虚拟地址与大物理地址 即LPA 与 LVA
#define PG_RAM_SIZE                __SYS_PAGE_SIZE__
#define PMD_ENTRY_ORDER            2

// 计算页表的起始虚拟地址
    .globl      g_data_page_start_vaddr                                    // 页表的初始虚拟地址
    .equ        g_data_page_start_vaddr, KERNEL_RAM_VADDR - PG_RAM_SIZE

/*
 * mmu 中会使用到的一些符号
 * 这里的目的是为了告诉链接器这些符号的值是在运行时链接器符号解析时赋值的。
 * 这些符号的值是在链接时由链接器计算得到的，具体的值取决于链接器的配置和链接脚本。
 * 虽然这些实际上是64位无符号整数，但在本汇编代码中我们将其存储为32位。
 */

// 计算页表物理基地址的宏 相当于 #define pgtbl(rd, phys) rd = phys + __SYS_KERNEL_OFFSET__ - PG_RAM_SIZE
    .macro      pgtbl, rd, phys     // \rd: 目标寄存器，用于存储计算结果\phys: 物理地址寄存器
    add         \rd, \phys, #__SYS_KERNEL_OFFSET__ // 将物理地址加上内核偏移量
    sub         \rd, \rd, #PG_RAM_SIZE  // 减去页表的大小，得到页表的起始地址
    .endm

/*
 * 内核启动入口点,由解压缩代码调用。要求：
 * MMU = 关闭, D-cache = 关闭, I-cache = 不关心, r0 = 0,
 * r1 = 机器编号, r2 = dtb指针
 * 你需要在内核链接地址__pa(0xc0008000)处调用
 */
    .arm     // 指定接下来的代码是 ARM模式 的指令，而不是Thumb模式
    __START  // 指定代码段
SYM_FUNC_START(stext)

// 安装虚拟化支持
    bl    __g_func_hyp_stub_install
// 获取处理器ID
    mrc    p15, 0, r9, c0, c0
// 根据处理器ID查找处理器类型
    bl    __g_func_lookup_processor_type
// 判断是否需要就地执行
    bl    __g_func_xip_config
// MMU早期准备阶段
    bl    __g_func_mmu_setup
// 设置 MMU 启用后的跳转地址，初始化页表
// 跳转到__g_func_mmap_switched -> start_common.S
    ldr    r0, =__g_func_mmap_switched

    // 函数体内容保持不变
SYM_FUNC_END(stext)
