#!/bin/bash
# 编译脚本

# 参数检查
if [ $# -ne 1 ]; then
    echo "用法: $0 <debug|release>"
    exit 1
fi

# 配置
MODE=$1
PRESET=""

case $MODE in
    debug)
        PRESET="debug"
        ;;
    release)
        PRESET="release"
        ;;
    *)
        echo "错误：无效的模式 '$MODE'"
        echo "请使用 'debug' 或 'release'"
        exit 1
        ;;
esac

# 清理
echo "清理构建目录..."
rm -rf build/${MODE}
mkdir -p build/${MODE}

# 配置项目
echo "配置项目 (模式: $MODE)..."
cmake --preset=${PRESET}

# 编译项目
echo "开始编译..."
cmake --build --preset=${PRESET}

# 完成
echo "构建完成！"
echo "输出文件位于 build/${MODE}"