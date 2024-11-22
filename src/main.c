#include <stdio.h>
#include <string.h>
#include "portproxy.h"
#include "version.h"

int main(int argc, char* argv[]) {
    // 检查是否启用调试模式
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            debug_mode = 1;
            // 移除 debug 参数
            for (int j = i; j < argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            argc--;
            break;
        }
    }

    // 显示版本信息
    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        print_version();
        return 0;
    }

    // 显示帮助信息
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_version();
        print_usage(argv[0]);
        return 0;
    }

    // 如果没有参数，显示当前映射状态
    if (argc == 1) {
        show_mappings();
        return 0;
    }

    // 检查参数数量
    if (argc > 4) {
        printf("Error: Too many arguments\n");
        print_usage(argv[0]);
        return 1;
    }

    char* plc_type = NULL;
    char* listen_ip = "0.0.0.0";  // 默认监听地址
    char* target_ip = NULL;

    // 解析参数
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "plc=", 4) == 0) {
            plc_type = argv[i] + 4;
        } else if (strncmp(argv[i], "listen=", 7) == 0) {
            listen_ip = argv[i] + 7;
        } else if (strncmp(argv[i], "target=", 7) == 0) {
            target_ip = argv[i] + 7;
        } else {
            printf("Error: Unknown argument '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    // 验证必要参数
    if (!plc_type) {
        printf("Error: PLC type must be specified (jetter or siemens)\n");
        return 1;
    }

    if (argc > 2 && !target_ip) {
        printf("Error: Target IP must be specified when setting up mappings\n");
        return 1;
    }

    if (debug_mode) {
        printf("Debug mode enabled\n");
        printf("PLC type: %s\n", plc_type);
        printf("Listen IP: %s\n", listen_ip);
        printf("Target IP: %s\n", target_ip ? target_ip : "not specified");
    }

    // 删除现有映射
    delete_all_mappings(listen_ip);

    // 如果没有提供目标IP，仅删除映射后退出
    if (!target_ip) {
        return 0;
    }

    // 根据 PLC 类型添加新的映射
    if (strcmp(plc_type, "jetter") == 0) {
        for (size_t i = 0; i < jetter_ports_count; i++) {
            add_port_mapping(jetter_ports[i].port, listen_ip, target_ip);
        }
    } else if (strcmp(plc_type, "siemens") == 0) {
        for (size_t i = 0; i < siemens_ports_count; i++) {
            add_port_mapping(siemens_ports[i].port, listen_ip, target_ip);
        }
    } else {
        printf("Error: Invalid PLC type. Must be 'jetter' or 'siemens'\n");
        return 1;
    }

    return 0;
}
