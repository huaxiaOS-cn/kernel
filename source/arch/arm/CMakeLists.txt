
# 清空源文件列表
set(ARCH_SOURCES "")

# 如果启用了特性 X，则添加对应的源文件
if(ENABLE_FEATURE_X)
    list(APPEND ARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/feature_x.c")
endif()

# 始终添加的源文件
list(APPEND ARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/common.c")

# 包含子目录
# 厂商
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/${CONFIG_VENDOR_TYPE})
# 启动文件
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/start)

# 合并子目录的源文件
list(APPEND ARCH_SOURCES ${SUBARCH_SOURCES})

# 创建一个静态库目标，名为 arch_lib
add_library(arch_lib STATIC ${ARCH_SOURCES})  