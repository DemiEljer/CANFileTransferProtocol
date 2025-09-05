/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGES_HANDLERS_H_
#define CANFTP_MESSAGES_HANDLERS_H_

#include "CanFTP_CanMessage.h"
#include "CanFTP_Messages_Params.h"

/*
    Получить код устройства во время сессии
*/
CanFTP_DeviceCode_t CanFTP_CanIdentifier_UnpackDeviceCode(uint32_t canId);
/*
    Получить индекс фрейма блока во время сессии
*/
CanFTP_FrameIndex_t CanFTP_CanIdentifier_UnpackDataFrameIndex(uint32_t canId);
/*
    Получить код сессии 
*/
CanFTP_SessionCode_t CanFTP_CanIdentifier_UnpackSessionCode(uint32_t canId);
/*
    Получить код устройства в процессе Ping
*/
CanFTP_DeviceSerialCode_t CanFTP_CanIdentifier_UnpackDeviceSerialCode(uint32_t canId);
/*
    Упаковать идентификатор сообщения клиента в процессе Ping
*/
uint32_t CanFTP_CanIdentifier_PackWithSerialDeviceCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_DeviceSerialCode_t deviceSerialCode
);
/*
    Упаковать идентификатор сообщения c кодом сессии
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
);
/*
    Упаковать идентификатор сообщения c кодом сессии и кодом устройства
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
    , CanFTP_DeviceCode_t deviceCode
);
/*
    Упаковать идентификатор сообщения c кодом сессии и индексом фрейма
*/
uint32_t CanFTP_CanIdentifier_PackWithSessionCodeAndFrameIndex
(
    CanFTP_CanMessageCodificator_t messageCodificator
    , CanFTP_SessionCode_t sessionCode
    , CanFTP_FrameIndex_t frameIndex
);
/*
    Верифицировать параметры сообщения
*/
CanFTP_Logical_t CanFTP_CanMessage_Verify(CanFTP_CanMessage_t* canMessage
    , CanFTP_CanMessageCodificator_t messageCodificator
    , uint8_t dataLength);
/*
    Проверить сообщение по кодификатору
*/
CanFTP_Logical_t CanFTP_CanMessage_CheckMessageCodification(CanFTP_CanMessage_t* canMessage
    , CanFTP_CanMessageCodificator_t messageCodificator);

#endif // CANFTP_MESSAGES_HANDLERS_H_