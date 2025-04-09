# 该路径包含架构下通用的功能文件
# 清空源文件列表
set(ARCH_SOURCES "")

# 包含子目录
# 启动文件
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/start)
# 厂商
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/${CONFIG_VENDOR_TYPE})

if(CONFIG_MMU_EN)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mmu.S)
endif()

# 始终添加的源文件
list(APPEND ARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lookup_processor.S") # 查找处理器类型
list(APPEND ARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/weak.S") # 弱符号定义，对未开启功能的处理
# 合并子目录的源文件
list(APPEND ARCH_SOURCES ${SUBARCH_SOURCES})

# 创建一个静态库目标，名为 arch_lib
add_library(arch_lib STATIC ${ARCH_SOURCES})