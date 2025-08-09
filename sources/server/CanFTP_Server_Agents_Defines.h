#ifndef CANFTP_SERVER_AGENTS_DEFINES_H_
#define CANFTP_SERVER_AGENTS_DEFINES_H_

#include "CanFTP_Server_Params.h"
#include "CanFTP_Message_Client_PingResponse.h"
#include "CanFTP_TimeHandlers.h"

/*
    Струкутура контроллера процесса Ping на стороне сервера
*/
typedef struct _CanFTP_Server_Agent_PingControler
{
    // Структура запросов к агенту
    struct
    {
        // Запрос на начало процесса Ping
        CanFTP_Logical_t requestPinging;

    } requsts;
    // Структура выходных параметров
    struct
    {

    } statuses;
    // Триггер повторной отправки сообщений в случае, если не был получен ответ
    CanFTP_TimeTrigger_t reapeateSendingTrigger;
    // Серийный номер устройства, которому посылается подтверждение
    CanFTP_DeviceSerial_t responsingDeviceSerial;
    // Тип сообщения
    CanFTP_Message_Client_PingResponse_Type_t responsingMessageType;  

} CanFTP_Server_Agent_PingControler_t;

#endif // CANFTP_SERVER_AGENTS_DEFINES_H_
