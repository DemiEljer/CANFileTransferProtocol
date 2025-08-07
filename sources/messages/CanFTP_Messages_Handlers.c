#include "CanFTP_Messages_Handlers.h"

/*
    Получить код устройства во время сессии
*/
CanFTP_DeviceCode_t CanFTP_CanIdentifier_UnpackDeviceCode(uint32_t canId)
{
    return (CanFTP_DeviceCode_t)(canId & 0xFF);
}
/*
    Получить индекс фрейма блока во время сессии
*/
CanFTP_FrameIndex_t CanFTP_CanIdentifier_UnpackDataFrameIndex(uint32_t canId)
{
    return (CanFTP_FrameIndex_t)(canId & 0xFF);
}
/*
    Получить код сессии 
*/
CanFTP_SessionCode_t CanFTP_CanIdentifier_UnpackSessionCode(uint32_t canId)
{
    return (CanFTP_SessionCode_t)((canId >> 8) & 0xFF);
}
/*
    Получить код устройства в процессе Ping
*/
CanFTP_DeviceSerialCode_t CanFTP_CanIdentifier_UnpackDeviceSerialCode(uint32_t canId)
{
    return (CanFTP_DeviceSerialCode_t)(canId & 0xFFFF);
}
/*
    Упаковать идентификатор сообщения клиента в процессе Ping
*/
uint32_t CanFTP_CanIdentifier_PackWithSerialDeviceCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_DeviceSerialCode_t deviceSerialCode
)
{
    return (uint32_t)messageCodificator | (uint32_t)(deviceSerialCode & 0xFFFF);
}
/*
    Упаковать идентификатор сообщения c кодом сессии
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
)
{
    return (uint32_t)messageCodificator | (uint32_t)((sessionCode & 0xFF) << 8);
}
/*
    Упаковать идентификатор сообщения c кодом сессии и кодом устройства
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
    , CanFTP_DeviceCode_t deviceCode
)
{
    return (uint32_t)messageCodificator | (uint32_t)((sessionCode & 0xFF) << 8) | (uint32_t)(deviceCode & 0xFF);
}
/*
    Упаковать идентификатор сообщения c кодом сессии и индексом фрейма
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCodeAndFrameIndex
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
    , CanFTP_FrameIndex_t frameIndex
)
{
    return (uint32_t)messageCodificator | (uint32_t)((sessionCode & 0xFF) << 8) | (uint32_t)(frameIndex & 0xFF);
}
/*
    Верифицировать параметры сообщения
*/
CanFTP_Logical_t CanFTP_CanMessage_Verify(CanFTP_CanMessage_t* canMessage
    , CanFTP_CanMessageCodificator_t messageCodificator
    , uint8_t dataLength
)
{
    if (canMessage->dataLength != dataLength
        || (!CanFTP_CanMessage_CheckMessageCodification(canMessage, messageCodificator)))
    {
        CanFTP_ThrowError();

        return 0x00;
    }
    else
    {
        return 0x01;
    }
}
/*
    Проверить сообщение по кодификатору
*/
CanFTP_Logical_t CanFTP_CanMessage_CheckMessageCodification(CanFTP_CanMessage_t* canMessage
    , CanFTP_CanMessageCodificator_t messageCodificator)
{
    return (canMessage->id & CANFTP_MESSAGE_MASK) == messageCodificator;
}
