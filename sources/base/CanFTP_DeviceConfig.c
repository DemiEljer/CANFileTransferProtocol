#include "CanFTP_DeviceConfig.h"

/*
    Сбросить конфигурацию
*/
void CanFTP_DeviveConfig_Reset(CanFTP_DeviveConfig_t* configuration)
{
    configuration->identifier = 0;
    configuration->serialNumber = 0;
    configuration->type = 0;
    CanFTP_SofwareVersion_Reset(&(configuration->softVersion));
}
