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

// 函数声明
void show_mappings(void);
void add_port_mapping(int port, const char* listen_ip, const char* target_ip);
void delete_all_mappings(const char* listen_ip);
void print_version(void);
void print_usage(const char* program_name);

// 导出端口配置
extern const PortMapping jetter_ports[];
extern const PortMapping siemens_ports[];
extern const size_t jetter_ports_count;
extern const size_t siemens_ports_count;

#endif // PORTPROXY_H
