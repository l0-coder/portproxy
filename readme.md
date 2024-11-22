```markdown
# PortProxy

PortProxy 是一个用于 PLC 设备端口转发的命令行工具，支持 Jetter 和 Siemens PLC 设备的端口映射配置。

[English](README_EN.md) | 简体中文

## 功能特点

- 支持 Jetter PLC 端口映射 (80, 502, 50000, 50001, 52000)
- 支持 Siemens PLC 端口映射 (80, 102)
- 简单的命令行界面
- 支持查看当前端口映射状态
- Windows 平台支持

## 安装

### 从源码构建

1. 克隆仓库：
```bash
git clone https://github.com/yourusername/portproxy.git
cd portproxy
```

2. 创建构建目录：
```bash
mkdir build
cd build
```

3. 配置和构建：
```bash
cmake ..
cmake --build . --config Release
```

构建完成后，可执行文件将位于 `build/Release/portproxy.exe`。

### 预编译版本

您可以从 [Releases](https://github.com/yourusername/portproxy/releases) 页面下载最新的预编译版本。

## 使用说明

### 基本命令

```bash
# 显示帮助信息
portproxy --help

# 显示版本信息
portproxy --version

# 显示当前端口映射
portproxy
```

### 端口映射配置

```bash
# 配置 Jetter PLC 端口映射
portproxy plc=jetter listen=192.168.1.1 target=192.168.2.11

# 配置 Siemens PLC 端口映射
portproxy plc=siemens listen=192.168.1.1 target=192.168.2.11
```

### 命令行参数

| 参数 | 说明 | 示例 |
|------|------|------|
| 无参数 | 显示当前端口映射 | `portproxy` |
| plc=TYPE | PLC类型(jetter/siemens) | `plc=jetter` |
| listen=IP | 本地监听IP地址 | `listen=192.168.1.1` |
| target=IP | 目标转发IP地址 | `target=192.168.2.11` |
| -h, --help | 显示帮助信息 | `portproxy --help` |
| -v, --version | 显示版本信息 | `portproxy --version` |

### 使用示例

1. 查看当前映射状态：
```bash
portproxy
```

2. 配置 Jetter PLC 端口转发：
```bash
portproxy plc=jetter listen=192.168.1.1 target=192.168.2.11
```

将配置以下端口映射：
- 80    -> 192.168.2.11:80
- 502   -> 192.168.2.11:502
- 50000 -> 192.168.2.11:50000
- 50001 -> 192.168.2.11:50001
- 52000 -> 192.168.2.11:52000

3. 配置 Siemens PLC 端口转发：
```bash
portproxy plc=siemens listen=192.168.1.1 target=192.168.2.11
```

将配置以下端口映射：
- 80  -> 192.168.2.11:80
- 102 -> 192.168.2.11:102

## 系统要求

- Windows 操作系统（Windows 7 或更高版本）
- 管理员权限（执行 netsh 命令需要）
- 用于构建（可选）：
  - Visual Studio 2019 或更高版本
  - CMake 3.10 或更高版本

## 常见问题

1. **执行时提示权限不足**
   - 请以管理员身份运行命令提示符
   - 右键点击命令提示符，选择"以管理员身份运行"

2. **端口被占用**
   - 使用 `netstat -ano | findstr "PORT"` 检查端口占用
   - 确保目标端口未被其他程序使用

## 更新日志

### v1.0.0 (2024-01-01)
- 初始版本发布
- 支持 Jetter 和 Siemens PLC 端口映射
- 基本命令行界面实现

## 贡献指南

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

## 开源协议

版权所有 (c) 2024 Your Name。保留所有权利。

特此授权，免费向任何获得本软件及相关文档文件（以下简称"软件"）副本的人提供使用、复制、修改、合并、出版、发布、再许可和/或销售软件副本的权利，但须遵守以下条件：

上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

本软件按"原样"提供，不提供任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和非侵权性的保证。在任何情况下，作者或版权持有人均不对任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权行为或其他方面，与软件或软件的使用或其他交易有关。

## 联系方式

- 作者：L0
- 邮箱：l0@fastmail.com
- 项目主页：https://github.com/yourusername/portproxy

## 致谢

感谢所有为这个项目做出贡献的开发者。

---

**注意**：本工具需要管理员权限才能执行端口映射操作。请在使用时确保具有足够的系统权限。
```