# OpenHarmony Edge IoT Gateway

基于 OpenHarmony 的分布式边缘物联网网关。

## 1. Project Introduction

本项目基于 OpenHarmony 5.0 与 DAYU200 开发板，实现一个面向物联网场景的边缘智能网关。

网关计划支持：

- TCP 设备接入
- 边缘风险评估
- 本地硬件联动
- OpenHarmony NAPI 原生扩展
- 分布式软总线设备协同
- HDF 硬件抽象接口

项目采用 OpenHarmony 标准系统部件化开发方式，包含 `services`、`adapter`、`hardware`、`napi`、`interfaces` 等模块。

## 2. Architecture

```text
STM32 / ESP32 Sensor Node
        │
   TCP / MQTT / UART
        │
DAYU200 OpenHarmony Gateway
 ├── DeviceManager
 ├── RuleEngine
 ├── AlarmManager
 ├── HardwareCtrl
 ├── GatewayNAPI
 └── SoftBusAdapter
        │
 Distributed Communication
        │
Phone / Tablet / Other OpenHarmony Device
````

## 3. Directory Structure

```text
openharmony_gateway/
├── adapter/                 # TCP / SoftBus adapters
│   ├── BUILD.gn
│   ├── tcp_adapter.cpp
│   └── softbus_adapter.cpp
├── hardware/                # Hardware abstraction layer
│   ├── BUILD.gn
│   └── hardware_ctrl.cpp
├── interfaces/
│   └── inner_api/           # Internal APIs
│       └── gateway_manager.h
├── napi/                    # ArkTS native bridge
│   ├── BUILD.gn
│   └── gateway_napi.cpp
├── services/                # Gateway core services
│   ├── BUILD.gn
│   ├── gateway_service.cpp
│   ├── device_manager.cpp
│   ├── rule_engine.cpp
│   └── alarm_manager.cpp
├── BUILD.gn
└── bundle.json
```

## 4. Core Modules

### DeviceManager

负责设备注册、设备状态维护与设备生命周期管理。

### RuleEngine

负责边缘风险评估，根据传感器数据计算风险等级。

### AlarmManager

负责告警生成、本地告警状态维护与硬件联动控制。

### TcpAdapter

负责 TCP 设备接入、数据接收与协议解析。

### SoftBusAdapter

负责 OpenHarmony 分布式软总线通信，用于设备发现与跨设备协同。

### HardwareCtrl

负责封装本地硬件控制接口，例如 LED、蜂鸣器、继电器等。

### GatewayNAPI

负责向 ArkTS 层暴露网关原生能力接口。

## 5. Build

Place this component into the OpenHarmony source tree:

```text
/iot_gateway/openharmony_gateway
```

Then add this component to the product configuration.

Build full image:

```bash
./build.sh --product-name rk3568 --ccache
```

Build gateway component only:

```bash
./build.sh --product-name rk3568 --build-target gateway_component --ccache
```

## 6. Roadmap

* [x] OpenHarmony component integration
* [x] NAPI framework skeleton
* [x] Gateway service skeleton
* [ ] TCP sensor communication
* [ ] Edge rule engine
* [ ] Alarm manager
* [ ] Hardware control abstraction
* [ ] SoftBus distributed communication
* [ ] ArkTS UI panel
* [ ] System test on DAYU200

## 7. Tech Stack

* OpenHarmony 5.0
* DAYU200 / RK3568
* C++
* ArkTS
* NAPI
* GN / Ninja
* TCP Socket
* Distributed SoftBus
* HDF

## 8. License

Apache-2.0
