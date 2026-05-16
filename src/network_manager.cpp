#include "network_manager.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

void FetchDataFromSensor(SensorData* data) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        HILOG_ERROR("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    if(inet_pton(AF_INET, "192.168.137.1", &serv_addr.sin_addr) <= 0) {
        HILOG_ERROR("Invalid address / Address not supported");
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        HILOG_ERROR("Connection Failed to Sensor");
        close(sock);
        return;
    }

    int valread = read(sock, buffer, 1024);
    if(valread > 0) {
        sscanf(buffer, "%lf,%lf,%lf", &data->temp, &data->humidity, &data->smoke);
        data->success = true;
        HILOG_INFO("Successfully fetched sensor data: Temp=%.1f", data->temp);
    }
    close(sock);
}
