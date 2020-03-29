cmake_minimum_required(VERSION 3.9)
project(Random-Draw) # 填写项目名称

set(CMAKE_CXX_STANDARD 17) # 设置 C++ 标准版本为 C++17

include(extern/cqcppsdk/cqcppsdk.cmake) # 包含 SDK 的 CMake 脚本

include_directories(src)

# 从 app_id.txt 文件读取 app id, 也可以直接设置
# file(READ "app_id.txt" APP_ID)
# string(STRIP "${APP_ID}" APP_ID)
cq_set_app_id("cn.skincrab.randomdraw") # 设置 app id

if (CQ_CAN_BUILD_STD_MODE)
    cq_add_std_app(src/main.cpp) # 添加 std 模式的动态链接库构建目标
    cq_install_std_app() # 向 CMAKE_INSTALL_PREFIX 指定的 酷Q 位置安装应用
endif ()

# 添加 dev 模式的可执行文件构建目标
cq_add_dev_app(src/main.cpp)