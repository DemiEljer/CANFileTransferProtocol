#ifndef CANFTP_CANMESSAGE_H_
#define CANFTP_CANMESSAGE_H_

#include "CanFTP_ErrorHandlers.h"

/*
    Стркутура CAN-сообщения
*/
typedef struct _CanFTP_CanMessage
{
    // Идентификатор вектора данных
    uint32_t id;
    // Длина вектора данных
    uint8_t dataLength;
    // Вектор данных сообщения
    uint8_t data[8];

} CanFTP_CanMessage_t;

/*
    Инициализация сообщения
*/
void CanFTP_CanMessage_Init(CanFTP_CanMessage_t* message
    // Идентификатор сообщения 
    , uint32_t id
    // Длина вектора данных
    , uint8_t dataLength
    // Вектор данных
    , uint8_t* data
);

#endif // CANFTP_CANMESSAGE_H_
