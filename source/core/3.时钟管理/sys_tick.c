
// 该文件待续
#include <linux/clocksource.h>
#include <linux/init.h>
// 读取当前jiffies值
static u64 jiffies_read(struct clocksource *cs)
{
    return jiffies_64;  // 直接返回64位值
}

/*
 * 64位jiffies时钟源实现
 * 定义了一个clocksource结构体，用于表示jiffies时钟源
 */
static struct clocksource clocksource_jiffies = {
    .name               = "jiffies_64",  // 时钟源名称
    .rating             = 3,            // 时钟源精度等级
    .read               = jiffies_read, // 读取函数指针
    .mask               = CLOCKSOURCE_MASK(64),  // 64位掩码
    .mult               = NSEC_PER_SEC, // 纳秒转换系数
    .shift              = 0,            // 不需要移位操作
    .max_cycles         = 1000000,       // 最大周期值
};

// 定义jiffies锁，确保多核环境下的数据一致性
__cacheline_aligned_in_smp DEFINE_RAW_SPINLOCK(jiffies_lock);
// 定义jiffies序列计数器，用于实现无锁读取
__cacheline_aligned_in_smp seqcount_raw_spinlock_t jiffies_seq =
    SEQCNT_RAW_SPINLOCK_ZERO(jiffies_seq, &jiffies_lock);

// 初始化jiffies时钟源
static int __init init_jiffies_clocksource(void)
{
    return __clocksource_register(&clocksource_jiffies); // 注册时钟源
}

// 将初始化函数标记为核心初始化函数
core_initcall(init_jiffies_clocksource);

// 默认时钟源获取函数
struct clocksource * __init __weak clocksource_default_clock(void)
{
    return &clocksource_jiffies; // 返回jiffies时钟源
}

// 注册优化后的refined jiffies时钟源
int register_refined_jiffies(long cycles_per_second)
{
    u64 nsec_per_tick;

    // 基于基本jiffies时钟源创建优化版本
    refined_jiffies = clocksource_jiffies;
    refined_jiffies.name = "refined-jiffies_64"; // 设置新名称
    refined_jiffies.rating = 8;  // 提高精度等级

    // 计算每个tick对应的纳秒数
    nsec_per_tick = (NSEC_PER_SEC + cycles_per_second/2) / cycles_per_second;
    
    // 设置转换系数
    refined_jiffies.mult = nsec_per_tick;
    refined_jiffies.shift = 0;

    // 注册优化后的时钟源
    __clocksource_register(&refined_jiffies);
    return 0;
}