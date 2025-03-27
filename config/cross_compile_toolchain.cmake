# 该文件用于配置交叉编译工具链
# 启用交叉编译模式
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_VERSION 1)
# 设置工具链路径变量
set(C_TOOLCHAIN_PATH /usr/local/bin/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin)
# C 语言交叉编译工具链配置
set(CMAKE_C_COMPILER ${C_TOOLCHAIN_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${C_TOOLCHAIN_PATH}/arm-none-eabi-g++)

# Rust 语言交叉编译工具链配置
set(CMAKE_RUST_COMPILER rustc)
set(CMAKE_RUST_FLAGS "--target=armv7-unknown-linux-gnueabihf")

# 设置查找路径模式
# 程序不在指定的根路径查找
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 库文件只在指定的根路径查找
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 头文件只在指定的根路径查找
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 软件包只在指定的根路径查找
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 设置查找根路径，可根据实际情况修改
# set(CMAKE_FIND_ROOT_PATH /path/rootfs)    