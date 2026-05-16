#include "gateway_common.h"
#include "network_manager.h"
#include "edge_ai_engine.h"

// 后台线程调度器
static void ExecuteWork(napi_env env, void* data) {
    SensorData* sensorData = (SensorData*)data;
    
    // 1. 调用网络层抓数据
    FetchDataFromSensor(sensorData);
    
    // 2. 调用 AI 层做决策
    CalculateFireRisk(sensorData);
}

static void CompleteWork(napi_env env, napi_status status, void* data) {
    SensorData* sensorData = (SensorData*)data;
    napi_value result;

    if (sensorData->success) {
        napi_create_object(env, &result);
        napi_value vTemp, vHum, vSmoke, vRisk;
        napi_create_double(env, sensorData->temp, &vTemp);
        napi_create_double(env, sensorData->humidity, &vHum);
        napi_create_double(env, sensorData->smoke, &vSmoke);
        napi_create_double(env, sensorData->fireRisk, &vRisk);

        napi_set_named_property(env, result, "temp", vTemp);
        napi_set_named_property(env, result, "humidity", vHum);
        napi_set_named_property(env, result, "smoke", vSmoke);
        napi_set_named_property(env, result, "fireRisk", vRisk);

        napi_resolve_deferred(env, sensorData->deferred, result);
    } else {
        napi_value errorMsg;
        napi_create_string_utf8(env, "Failed to get data", NAPI_AUTO_LENGTH, &errorMsg);
        napi_reject_deferred(env, sensorData->deferred, errorMsg);
    }

    napi_delete_async_work(env, sensorData->asyncWork);
    delete sensorData;
}

static napi_value GetSensorDataAsync(napi_env env, napi_callback_info info) {
    napi_value promise;
    SensorData* sensorData = new SensorData();
    napi_create_promise(env, &sensorData->deferred, &promise);
    napi_value resourceName;
    napi_create_string_utf8(env, "GetSensorDataAsync", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(env, nullptr, resourceName, ExecuteWork, CompleteWork, sensorData, &sensorData->asyncWork);
    napi_queue_async_work(env, sensorData->asyncWork);
    return promise;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        { "getSensorDataAsync", nullptr, GetSensorDataAsync, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module gatewayModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,       
    .nm_modname = "gateway",        
    .nm_priv = ((void*)0),
    .reserved = { nullptr },
};

extern "C" __attribute__((constructor)) void RegisterGatewayModule(void) {
    napi_module_register(&gatewayModule);
}