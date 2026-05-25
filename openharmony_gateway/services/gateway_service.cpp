#include "gateway_manager.h"

namespace OHOS::IoTGateway {
namespace {
bool g_gatewayReady = false;
}

GatewayManager &GatewayManager::GetInstance()
{
    static GatewayManager instance;
    return instance;
}

bool GatewayManager::Init()
{
    g_gatewayReady = true;
    return g_gatewayReady;
}

void GatewayManager::Shutdown()
{
    g_gatewayReady = false;
}

bool GatewayManager::RegisterDevice(const char *deviceId)
{
    return g_gatewayReady && deviceId != nullptr;
}
}  // namespace OHOS::IoTGateway
