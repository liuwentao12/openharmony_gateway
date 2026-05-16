#ifndef GATEWAY_COMMON_H
#define GATEWAY_COMMON_H

#include "napi/native_api.h"
#include "hilog/log.h" // 引入鸿蒙官方日志库

// -----------------------------------------------------
// ⚠️ 极其重要：先取消掉系统头文件里的默认宏定义，防止重复定义报错
#undef LOG_DOMAIN
#undef LOG_TAG
#undef HILOG_INFO
#undef HILOG_ERROR
// -----------------------------------------------------

// 定义专属的日志标签 (在 hdc hilog 里可以通过这个标签过滤你的网关日志)
#define LOG_DOMAIN 0x0000
#define LOG_TAG "SmartGateway"
#define HILOG_INFO(...) ((void)HILOG_IMPL(LOG_CORE, LOG_INFO, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))
#define HILOG_ERROR(...) ((void)HILOG_IMPL(LOG_CORE, LOG_ERROR, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

// 核心数据载体
struct SensorData {
    napi_async_work asyncWork = nullptr;
    napi_deferred deferred = nullptr;
    double temp = 0.0;
    double humidity = 0.0;
    double smoke = 0.0;
    double fireRisk = 0.0;
    bool success = false;
};

#endif