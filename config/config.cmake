# CMake 选项配置模板

set(架构类型 "" CACHE STRING "选择目标架构")
set_property(CACHE 架构类型 PROPERTY STRINGS "arm" "riscv" "x86")  # 可选的架构类型

# # 布尔类型选项
# set(ENABLE_FEATURE "")  # 是否启用某个功能 (ON/OFF)

# # 字符串类型选项
# set(COMPILER_NAME "")  # 指定编译器名称
# set(INSTALL_PREFIX "")  # 安装路径前缀

# # 路径类型选项
# set(SOURCE_DIR "")  # 源代码目录路径
# set(BUILD_DIR "")  # 构建目录路径

# # 数值类型选项
# set(BUFFER_SIZE "")  # 缓冲区大小 (单位: 字节)
# set(THREAD_COUNT "")  # 线程数量

# # 枚举类型选项
# set(LOG_LEVEL "")  # 日志级别 (DEBUG, INFO, WARNING, ERROR)
# set(ARCH_TYPE "")  # 架构类型 (ARM, X86, MIPS)

# # 列表类型选项
# set(EXTRA_FLAGS "")  # 额外的编译标志
# set(PLUGIN_LIST "")  # 插件列表

# # 文件类型选项
# set(CONFIG_FILE "")  # 配置文件路径
# set(LICENSE_FILE "")  # 许可证文件路径

# # 自定义选项
# set(MY_OPTION "")  # 自定义选项示例
# set(MY_VALUE "")    # 自定义值示例
