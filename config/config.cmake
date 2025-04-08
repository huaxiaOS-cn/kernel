# 此文件用于生成 CMake 配置文件，用于配置 CMake 项目的选项
## 总体配置
set(CONFIG_COMMON_LOG_LEVEL "DEBUG" CACHE STRING "选择日志级别")
set_property(CACHE CONFIG_COMMON_LOG_LEVEL PROPERTY STRINGS "FATAL" "ERROR" "WARNING" "INFO" "DEBUG")
set(CONFIG_64BIT_EN OFF CACHE BOOL "是否启用64位模式")
if (CONFIG_64BIT_EN STREQUAL "ON")
    add_definitions(-D__SYS_PAGE_OFFSET__=0xFFFF800000000000) # 64位下给内核分配最后256T虚拟地址空间
else()
    add_definitions(-D__SYS_PAGE_OFFSET__=0xC0000000) # 32位下给内核分配最后1G虚拟地址空间
endif()
add_definitions(-D__SYS_KERNEL_OFFSET__ = 0x00008000) # 内核地址相对内核起始地址的偏移
##  架构配置
set(CONFIG_ARCH_TYPE "arm" CACHE STRING "选择目标架构")
set_property(CACHE CONFIG_ARCH_TYPE PROPERTY STRINGS "arm" "riscv" "x86")   # 可选的架构类型

set(CONFIG_VENDOR_TYPE "nxp" CACHE STRING "选择目标厂商")

set(CONFIG_CHIP_TYPE "imx6ull" CACHE STRING "选择目标芯片")

set(CONFIG_BIG_ENDIAN_EN OFF CACHE BOOL "是否启用大端模式" ) # 默认小端模式
if (CONFIG_BIG_ENDIAN_EN STREQUAL "ON")
    add_definitions(-D__SYS_BIG_ENDIAN__)
endif()
set(CONFIG_MMU_EN ON CACHE BOOL "是否启用MMU内存管理单元")
set(CONFIG_VIRT_EXT_EN OFF CACHE BOOL "是否启用虚拟扩展")
set(CONFIG_SMP_EN OFF CACHE BOOL "是否启用对称多处理器支持")

set(CONFIG_CPU_MITIGATIONS_EN OFF CACHE BOOL "是否启用CPU安全漏洞缓解")

##  核心配置
set(CONFIG_CORE_TYPE "slave" CACHE STRING "选择内核类型")
set_property(CACHE CONFIG_CORE_TYPE PROPERTY STRINGS "master" "slave")   # 可选的内核类型

##  跨设备配置
set(CONFIG_CROSS_DEVICE_EN ON CACHE BOOL "是否启用跨设备支持")

##  驱动设备配置

##  文件系统配置
set(CONFIG_EXT4_FS_EN ON CACHE BOOL "是否启用Ext4文件系统")

set(CONFIG_FAT32_FS_EN ON CACHE BOOL "是否启用FAT32文件系统")

set(CONFIG_NFS_FS_EN ON CACHE BOOL "是否启用NFS文件系统")

set(CONFIG_SMB_FS_EN ON CACHE BOOL "是否启用SMB文件系统")

##  模块与组建配置

##  网络配置

##  安全配置

##  用户空间配置

################################# 各种配置类型示例 ###############################
# # 布尔类型选项
# set(ENABLE_FEATURE "@ENABLE_FEATURE@")  # 是否启用某个功能 (ON/OFF)
# # 字符串类型选项
# set(COMPILER_NAME "@COMPILER_NAME@")  # 指定编译器名称
# set(INSTALL_PREFIX "@INSTALL_PREFIX@")  # 安装路径前缀
# # 路径类型选项
# set(BUILD_DIR "@BUILD_DIR@")  # 构建目录路径
# # 数值类型选项
# set(BUFFER_SIZE "@BUFFER_SIZE@")  # 缓冲区大小 (单位: 字节)
# # 枚举类型选项
# set(LOG_LEVEL "@LOG_LEVEL@")  # 日志级别 (DEBUG, INFO, WARNING, ERROR)
# # 列表类型选项
# set(EXTRA_FLAGS "@EXTRA_FLAGS@")  # 额外的编译标志
# set(PLUGIN_LIST "@PLUGIN_LIST@")  # 插件列表
# # 文件类型选项
# set(CONFIG_FILE "@CONFIG_FILE@")  # 配置文件路径
# # 自定义选项
# set(MY_OPTION "@MY_OPTION@")  # 自定义选项示例
# set(MY_VALUE "@MY_VALUE@")    # 自定义值示例