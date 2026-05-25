#pragma once

namespace OHOS::IoTGateway {
class GatewayManager {
public:
    static GatewayManager &GetInstance();

    bool Init();
    void Shutdown();
    bool RegisterDevice(const char *deviceId);
};
}  // namespace OHOS::IoTGateway
