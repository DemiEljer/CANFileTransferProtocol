#ifndef CANFTP_BASETYPES_DEFINES_H_
#define CANFTP_BASETYPES_DEFINES_H_

#include "stdint.h"
#include "CanFTP_Configs.h"
#include "CanFTP_Debug.h"

#define CANFTP_FALSE 0x00
#define CANFTP_TRUE 0x01
#define CANFTP_NONE 0x02

#define CANFTP_NULL 0x00

// Логический тип
typedef uint8_t CanFTP_Logical_t;

// Тип серийного номера устройства
typedef uint32_t CanFTP_DeviceSerial_t;
// Тип идентификатора устройства
typedef uint16_t CanFTP_DeviceIdentifier_t;
// Тип идентификатора устройства
typedef uint32_t CanFTP_DeviceType_t;
// Тип идентификатора устройства
typedef uint8_t CanFTP_DeviceSoftwareVersionPart_t;
// Тип кода сессии сессии
typedef uint16_t CanFTP_SessionCode_t;
// Тип индекса фрейма в рамках блока кода
typedef uint16_t CanFTP_FrameIndex_t;
// Тип кода устройства
typedef uint16_t CanFTP_DeviceCode_t;
// Тип кода устройства
typedef uint16_t CanFTP_DeviceSerialCode_t;
// Тип мндекса блока кода
typedef uint32_t CanFTP_BlockIndex_t;
// Тип длины блока кода
typedef uint16_t CanFTP_BlockLength_t;
// Тип версии протокола
typedef uint16_t CanFTP_ProtocolVersion_t;
// Тип индекса страницы записи
typedef uint16_t CanFTP_PageIndex_t;
// Тип размера передаваемого файла
typedef uint32_t CanFTP_FileLength_t;
// Тип параметра количества повтореных отправок
typedef uint16_t CanFTP_SendingRepeate_t;
// Тип параметра периодов повторных отправок
typedef uint16_t CanFTP_SendingRepeateInterval_t;
// Тип кодификатора идентификаторов сообщений
typedef uint32_t CanFTP_CanMessageCodificator_t;

#endif // CANFTP_BASETYPES_DEFINES_H_
