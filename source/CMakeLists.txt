add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/arch/${CONFIG_ARCH_TYPE})      # 架构
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)                          # 内核核心
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/drivers)                       # 驱动程序
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/file_system)                   # 文件系统
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/net)                           # 网络协议栈
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cross_device)                  # 交叉设备支持
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules)                       # 模块
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/secure)                        # 安全与加密
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/usr_support)                   # 用户空间支持