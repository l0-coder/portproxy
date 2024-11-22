cmake_minimum_required(VERSION 3.10)
project(portproxy C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加源文件
add_executable(portproxy 
    src/main.c
    src/portproxy.c
)

# 包含头文件目录
target_include_directories(portproxy PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 添加 Windows 资源文件
target_sources(portproxy PRIVATE src/resource.rc)

# 设置输出目录
set_target_properties(portproxy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
)

# 安装配置
install(TARGETS portproxy
    RUNTIME DESTINATION bin
)
