#ifndef CANFTP_MESSAGE_SERVER_BLOCKCONTROL_H_
#define CANFTP_MESSAGE_SERVER_BLOCKCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_ClientBlockHandlingStatus.h"

/*
    Тип сообщения управления блоком
*/
typedef enum _CanFTP_Message_Server_BlockControl_Type
{
    CANFTP_MESSAGE_SERVER_BLOCKCONTROL_START = 0,
    CANFTP_MESSAGE_SERVER_BLOCKCONTROL_FINISH = 1,
    CANFTP_MESSAGE_SERVER_BLOCKCONTROL_FEEDBACKACK = 2,
} CanFTP_Message_Server_BlockControl_Type_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_BlockControl
{
    // Тип сообщения
    CanFTP_Message_Server_BlockControl_Type_t messageType;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;

    // STARTBLOCKACK
    struct
    {
        // Индекс блока
        CanFTP_BlockIndex_t blockIndex;
        // Длина блока
        CanFTP_BlockLength_t blockLength;

    } start;
    // FINISHBLOCKACK
    struct
    {
        // Индекс блока
        CanFTP_BlockIndex_t blockIndex;

    } finish;
    // FEEDBACKACK
    struct
    {
        // Код устройства
        CanFTP_DeviceCode_t deviceCode;
        // Статус обработки блока
        CanFTP_ClientBlockHandlingStatus_t blockHandlingStatus;

    } feedbackAck;

} CanFTP_Message_Server_BlockControl_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_BlockControl_Unpack(CanFTP_Message_Server_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_BlockControl_Pack(CanFTP_Message_Server_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_BLOCKCONTROL_H_
