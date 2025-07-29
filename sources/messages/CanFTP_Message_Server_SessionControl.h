#ifndef CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_
#define CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_ClientSessionFinishStatus.h"

/*
    Тип сообщения при управлении сессией
*/
typedef enum _CanFTP_Message_Server_SessionControl_Type
{
    CANFT_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION = 0,
    CANFT_MESSAGE_SERVER_SESSIONCONTROL_START = 1,
    CANFT_MESSAGE_SERVER_SESSIONCONTROL_FINISH = 2,
} CanFTP_Message_Server_SessionControl_Type_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_SessionControl
{
    // Тип сообщения
    CanFTP_Message_Server_SessionControl_Type_t messageType;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    
    // CONFIGURATION
    struct
    {
        // Индекс страницы записи
        CanFTP_PageIndex_t pageIndex;
        // Длина передаваемого файла
        CanFTP_FileLength_t fileLength;
        // Количество повторных отправок блока файла
        CanFTP_SendingRepeate_t repeateBlockCount;
        // Количество повторных отправок сообщений подтверждения
        CanFTP_SendingRepeate_t repeateAckCount;
        // Интервал времени повторной отправки
        CanFTP_SendingRepeateInterval_t repeateInterval;

    } configuration;
    // START
    struct
    {
        // Тут ничего не упаковывается
    } start;
    // FINISH 
    struct
    {
        // Статус завершения операции
        CanFTP_ClientSessionFinishStatus_t status;

    } finish;

} CanFTP_Message_Server_SessionControl_t;

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Unpack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Pack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_
