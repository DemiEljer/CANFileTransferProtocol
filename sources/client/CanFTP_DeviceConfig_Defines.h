#ifndef CANFTP_DEVICECONFIG_DEFINES_H_
#define CANFTP_DEVICECONFIG_DEFINES_H_

#include "CanFTP_SofwareVersion.h"

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
    CanFTP_SofwareVersion_t softVersion;

} CanFTP_DeviveConfig_t;

#endif // CANFTP_CLIENT_DEVICECONFIG_DEFINES_H_