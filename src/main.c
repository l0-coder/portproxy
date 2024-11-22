#include "portproxy.h"
#include "version.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Jetter PLC 端口配置
static const PortMapping JETTER_PORTS[] = {
    {80}, {502}, {50000}, {50001}, {52000}
};

// Siemens PLC 端口配置
static const PortMapping SIEMENS_PORTS[] = {
    {80}, {102}
};

// 执行系统命令
static void execute_command(const char* cmd) {
    printf("Executing: %s\n", cmd);
    system(cmd);
}

void show_mappings(void) {
    execute_command("netsh interface portproxy show all");
}

void print_version(void) {
    printf("%s version %s\n", APP_NAME, APP_VERSION);
    printf("%s\n", APP_COPYRIGHT);
    printf("%s\n", APP_DESCRIPTION);
}

void print_usage(const char* program_name) {
    printf("Usage: %s [plc=jetter|siemens] [listen=IP] [target=IP]\n\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     : Show this help message\n");
    printf("  -v, --version  : Show version information\n");
    printf("  No arguments   : Show current port mappings\n");
    printf("  plc=TYPE       : PLC type (jetter or siemens)\n");
    printf("  listen=IP      : Local IP address to listen on\n");
    printf("  target=IP      : Target IP address to forward to\n");
}

// 删除所有现有端口映射
void delete_all_mappings(const char* listen_ip) {
    char cmd[256];
    // 显示所有当前映射以供参考
    execute_command("netsh interface portproxy show all");
    
    // 为每个可能的端口执行删除操作
    int all_ports[] = {80, 102, 502, 50000, 50001, 52000};
    int port_count = sizeof(all_ports) / sizeof(all_ports[0]);
    
    for (int i = 0; i < port_count; i++) {
        snprintf(cmd, sizeof(cmd), 
                "netsh interface portproxy delete v4tov4 listenport=%d listenaddress=%s",
                all_ports[i], listen_ip);
        execute_command(cmd);
    }
}

// 添加端口映射
void add_port_mapping(int port, const char* listen_ip, const char* target_ip) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), 
            "netsh interface portproxy add v4tov4 listenport=%d listenaddress=%s connectaddress=%s connectport=%d",
            port, listen_ip, target_ip, port);
    execute_command(cmd);
}

int main(int argc, char* argv[]) {
    // 如果没有参数，显示当前映射状态
    if (argc == 1) {
        execute_command("netsh interface portproxy show all");
        return 0;
    }

    // 检查参数数量
    if (argc < 2 || argc > 4) {
        printf("Usage: %s [plc=jetter|siemens] [listen=IP] [target=IP]\n", argv[0]);
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

    // 删除现有映射
    delete_all_mappings(listen_ip);

    // 如果没有提供目标IP，仅删除映射后退出
    if (!target_ip) {
        return 0;
    }

    // 根据 PLC 类型添加新的映射
    if (strcmp(plc_type, "jetter") == 0) {
        for (size_t i = 0; i < sizeof(jetter_ports)/sizeof(jetter_ports[0]); i++) {
            add_port_mapping(jetter_ports[i].port, listen_ip, target_ip);
        }
    } else if (strcmp(plc_type, "siemens") == 0) {
        for (size_t i = 0; i < sizeof(siemens_ports)/sizeof(siemens_ports[0]); i++) {
            add_port_mapping(siemens_ports[i].port, listen_ip, target_ip);
        }
    } else {
        printf("Error: Invalid PLC type. Must be 'jetter' or 'siemens'\n");
        return 1;
    }

    return 0;
}
