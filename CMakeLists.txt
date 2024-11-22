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

# Windows 特定配置
if(MSVC)
    # 设置 MSVC 输出目录
    foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${CONFIG} CONFIG_UPPER)
        set_target_properties(portproxy PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} "${CMAKE_BINARY_DIR}/${CONFIG}"
        )
    endforeach()
endif()

# 安装配置
install(TARGETS portproxy
    RUNTIME DESTINATION bin
)
