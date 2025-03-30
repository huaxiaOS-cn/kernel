# 该文件为 kernel 的根CMakeLists.txt，管理 kernel 项目的构建和测试
# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.19.0)

# 定义项目名称和语言
project(huaxiaOSkernel VERSION 0.1.0)
set(CMAKE_SYSTEM_NAME huaxiaOSkernel)               # 设置目标系统
# 设置目标架构 **按需修改**
set(CMAKE_SYSTEM_PROCESSOR arm架构)
# 包含 交叉编译工具链文件，配合目标架构使用
include(${CMAKE_SOURCE_DIR}/config/cross_compile_toolchain.cmake)
include(${CMAKE_SOURCE_DIR}/config/config.cmake)
# 设置 CMake 查找程序、库和头文件的规则
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)    # 不在sysroot中查找可执行程序
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)     # 只在sysroot中查找库文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)     # 只在sysroot中查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)     # 只在sysroot中查找包

# 设置 C++ 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# 设置 Rust 标准
set(CMAKE_RUST_STANDARD 17)
set(CMAKE_RUST_STANDARD_REQUIRED ON)

# 添加源码目录
add_subdirectory(${CMAKE_SOURCE_DIR}/source)

# 配置文件
configure_file(
    "${CMAKE_SOURCE_DIR}/config/config.in"      # 输入文件
    "${CMAKE_SOURCE_DIR}/config/config.cmake"   # 输出文件
)