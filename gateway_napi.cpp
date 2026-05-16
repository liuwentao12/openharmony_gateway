#include "napi/native_api.h"
#include "napi/native_node_api.h"

static napi_value GetTemperature(napi_env env,napi_callback_info info)
{
    napi_value result;
    double temp=26.5; // 模拟获取温度数据

    //napi核心：把C++数据转换成JavaScript可用的类型
    napi_create_double(env,temp,&result);
    return result;
}

//2.模块初始化，绑定函数名
EXTERN_C_START
static napi_value Init(napi_env env,napi_value exports)
{
    //定义导出对象的属性：前端调用的名字叫"getTemperature"，对应C++函数是GetTemperature
    napi_property_descriptor desc[] = {
        {"getTemperature",nullptr,GetTemperature,nullptr,nullptr,nullptr,napi_default,nullptr}
    };
    // 将属性挂载到 exports 对象上
    napi_define_properties(env,exports,sizeof(desc)/sizeof(desc[0]),desc);
    return exports;
}
EXTERN_C_END

//3.定义模块的身份信息
static napi_module gatewayModule ={
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "gateway",
    .nm_priv = ((void*)0),
    .reserved = { nullptr },
};

// 4. 在系统启动该动态库时，自动注册模块
extern "C" __attribute__((constructor)) void RegisterModule()
{
    napi_module_register(&gatewayModule);
}