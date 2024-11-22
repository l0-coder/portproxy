#include "portproxy.h"
#include "version.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化调试模式标志
int debug_mode = 0;

// 端口配置定义
const PortMapping jetter_ports[] = {
    {80}, {502}, {50000}, {50001}, {52000}
};

const PortMapping siemens_ports[] = {
    {80}, {102}
};

const size_t jetter_ports_count = sizeof(jetter_ports) / sizeof(jetter_ports[0]);
const size_t siemens_ports_count = sizeof(siemens_ports) / sizeof(siemens_ports[0]);

// 执行系统命令
static void execute_command(const char* cmd) {
    if (debug_mode) {
        printf("Executing: %s\n", cmd);
    }
    system(cmd);
}

void show_mappings(void) {
    execute_command("netsh interface portproxy show all");
}

void add_port_mapping(int port, const char* listen_ip, const char* target_ip) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), 
            "netsh interface portproxy add v4tov4 listenport=%d listenaddress=%s connectaddress=%s connectport=%d",
            port, listen_ip, target_ip, port);
    execute_command(cmd);
}

void delete_all_mappings(const char* listen_ip) {
    char cmd[256];
    int all_ports[] = {80, 102, 502, 50000, 50001, 52000};
    int port_count = sizeof(all_ports) / sizeof(all_ports[0]);
    
    for (int i = 0; i < port_count; i++) {
        snprintf(cmd, sizeof(cmd), 
                "netsh interface portproxy delete v4tov4 listenport=%d listenaddress=%s",
                all_ports[i], listen_ip);
        execute_command(cmd);
    }
}

void print_version(void) {
    printf("%s version %s\n", APP_NAME, APP_VERSION);
    printf("%s\n", APP_COPYRIGHT);
    printf("%s\n", APP_DESCRIPTION);
}

void print_usage(const char* program_name) {
    printf("Usage: %s [plc=jetter|siemens] [listen=IP] [target=IP]\n\n", program_name);
    printf("Options:\n");
    printf("  No arguments   : Show current port mappings\n");
    printf("  plc=TYPE      : PLC type (jetter or siemens)\n");
    printf("  listen=IP     : Local IP address to listen on\n");
    printf("  target=IP     : Target IP address to forward to\n");
}
