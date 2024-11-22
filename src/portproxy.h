#ifndef PORTPROXY_H
#define PORTPROXY_H

// PLC 类型枚举
typedef enum {
    PLC_TYPE_JETTER,
    PLC_TYPE_SIEMENS
} PlcType;

// 端口映射结构
typedef struct {
    int port;
} PortMapping;

// 配置结构
typedef struct {
    PlcType type;
    const char* listen_ip;
    const char* target_ip;
} Config;

// 函数声明
void show_mappings(void);
int setup_mappings(const Config* config);
void print_version(void);
void print_usage(const char* program_name);

#endif // PORTPROXY_H
