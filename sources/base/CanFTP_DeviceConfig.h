#ifndef CANFTP_DEVICECONFIG_H_
#define CANFTP_DEVICECONFIG_H_

#include "CanFTP_SoftwareVersion.h"

/* 
    Структура конфигурации клиента
*/
typedef struct _CanFTP_DeviveConfig
{
    // Серийный номер устройства
    CanFTP_DeviceSerial_t serialNumber;
    // Идентификатор устройства
    CanFTP_DeviceIdentifier_t identifier;
    // Тип устройства
    CanFTP_DeviceType_t type;
    // Версия программного обеспечения устройства
    CanFTP_SoftwareVersion_t softVersion;

} CanFTP_DeviceConfig_t;

/*
    Сбросить конфигурацию
*/
void CanFTP_DeviceConfig_Reset(CanFTP_DeviceConfig_t* configuration);

#endif // CANFTP_CLIENT_DEVICECONFIG_DEFINES_H_
