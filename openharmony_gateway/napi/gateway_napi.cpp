#include "gateway_manager.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace {
napi_value InitGateway(napi_env env, napi_callback_info info)
{
    (void)info;
    OHOS::IoTGateway::GatewayManager::GetInstance().Init();

    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    return result;
}

napi_value GatewayExport(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        {"initGateway", nullptr, InitGateway, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
}  // namespace

static napi_module g_gatewayModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = GatewayExport,
    .nm_modname = "gateway",
    .nm_priv = nullptr,
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterGatewayModule(void)
{
    napi_module_register(&g_gatewayModule);
}
