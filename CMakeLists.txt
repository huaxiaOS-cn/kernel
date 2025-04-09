# 添加文件格式校验
add_custom_target(check_line_endings
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckLineEndings.cmake
)

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

# 定义最终的内核镜像目标
add_custom_target(huaxiaOSkernel_image
    # 链接所有模块的静态库
    COMMAND ${CMAKE_C_COMPILER} -o ${CMAKE_BINARY_DIR}/huaxiaOSkernel.bin 
            $<TARGET_FILE:arch_lib>
            $<TARGET_FILE:init_lib>
            $<TARGET_FILE:core_lib>
            $<TARGET_FILE:cross_device_lib>
            $<TARGET_FILE:drivers_lib>
            $<TARGET_FILE:file_system_lib>
            $<TARGET_FILE:net_lib>
            $<TARGET_FILE:usr_support_lib>
            
            # 可以继续添加其他模块的库
    DEPENDS arch_lib init_lib core_lib cross_device_lib drivers_lib file_system_lib net_lib usr_support_lib
    COMMENT "Building kernel image"
)
# 设置文件编码检测
set(CMAKE_CXX_ENCODING "UTF-8")
set(CMAKE_C_ENCODING "UTF-8")