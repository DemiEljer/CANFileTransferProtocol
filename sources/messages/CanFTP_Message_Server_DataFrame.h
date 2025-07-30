#ifndef CANFTP_MESSAGE_SERVER_DATAFRAME_H_
#define CANFTP_MESSAGE_SERVER_DATAFRAME_H_

#include "CanFTP_Messages_Handlers.h"

// Количество байт в сообщении передачи элемента блока
#define CANFTP_DATAFRAME_BYTESCOUNT 8

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_DataFrame
{
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Индекс кадра в рамках блока
    CanFTP_FrameIndex_t frameIndex;
    // Вектор данных кадра блока
    uint8_t data[CANFTP_DATAFRAME_BYTESCOUNT];

} CanFTP_Message_Server_DataFrame_t;

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_DataFrame_Unpack(CanFTP_Message_Server_DataFrame_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_DataFrame_Pack(CanFTP_Message_Server_DataFrame_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_DATAFRAME_H_
