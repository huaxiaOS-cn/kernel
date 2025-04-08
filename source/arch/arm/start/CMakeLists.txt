# 清空源文件列表
set(SUBARCH_SOURCES "")

# 如果启用了特性 Y，则添加对应的源文件
if(ENABLE_FEATURE_Y)
    list(APPEND SUBARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/feature_y.c")
endif()

# 始终添加的源文件
list(APPEND SUBARCH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/subcommon.c")

# 将源文件传递给父目录
set(SUBARCH_SOURCES ${SUBARCH_SOURCES} PARENT_SCOPE)    