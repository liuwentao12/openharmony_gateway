#include "edge_ai_engine.h"

void CalculateFireRisk(SensorData* data) {
    if (!data->success) return;
    
    HILOG_INFO("Starting Edge AI computation...");
    double tempRisk = (data->temp > 40.0) ? ((data->temp - 40.0) / 60.0) : 0.0;
    double smokeRisk = (data->smoke > 300.0) ? ((data->smoke - 300.0) / 700.0) : 0.0;
    
    data->fireRisk = (tempRisk * 0.4) + (smokeRisk * 0.6);
    if (data->fireRisk > 1.0) data->fireRisk = 1.0;
    
    HILOG_INFO("Computation done. Fire Risk: %.2f", data->fireRisk);
}
