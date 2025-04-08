/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _HUAXIAOS_INIT_H
#define _HUAXIAOS_INIT_H

/* 优化内核初始化函数的编译，初始化函数在内核启动后不会被再次调用，因此不需要使用 retpoline 技术来缓解 Spectre 漏洞 */
#if defined(__noretpoline) && !defined(MODULE)
#define __noinitretpoline __noretpoline
#else
#define __noinitretpoline
#endif
/* 
 * 这些宏用于将函数或初始化数据标记为"初始化"函数
 * 内核可以将其视为仅在初始化阶段使用的提示，并在初始化完成后释放内存资源
 * 使用示例：
 * 对于函数：
 * static void __init func(int x, int y) { ... } 或
 * extern int func(int, int, int) __init;
 * 对于初始化数据：
 * static int value __initdata = 0;
 * static const char value[] __initconst = { 0x32, 0x36, ... };
 */

/* 这些宏适用于所有代码 */
#define __init		__section(".init.text") __cold  __latent_entropy __noinitretpoline
#define __initdata	__section(".init.data")
#define __initconst	__section(".init.rodata")
#define __exitdata	__section(".exit.data")
#define __exit_call	__used __section(".exitcall.exit")

/* 对于汇编 */
#define __START		.section	".start.text","ax"
#define __INIT		.section	".init.text","ax"
#define __FINIT		.previous

#define __INITDATA	.section	".init.data","aw",%progbits
#define __INITRODATA	.section	".init.rodata","a",%progbits
#define __FINITDATA	.previous

#endif /* _HUAXIAOS_INIT_H */
