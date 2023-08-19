# CMakeList.txt: is 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("is")

set(CMAKE_CXX_STANDARD 20)

# 将源代码添加到此项目的可执行文件。
add_executable (is "src/is.cpp" "src/imemory.cpp" "src/ioptions.h" "src/iansictrl.h" "src/iassert.h" "src/icontainers.h" "src/imemory.h" "src/itypes.h" "src/iutf8.h" "src/iutils.h" "src/iutf8.cpp" "src/istring.h" "src/istring.cpp" "src/itoken.h" "src/itoken.cpp" "src/itoken.inc" "src/ivalue.h" "src/ivalue.cpp")

# TODO: 如有需要，请添加测试并安装目标。
