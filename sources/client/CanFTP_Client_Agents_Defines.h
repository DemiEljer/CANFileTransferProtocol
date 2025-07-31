#ifndef CANFTP_CLIENT_AGENTS_DEFINES_H_
#define CANFTP_CLIENT_AGENTS_DEFINES_H_

#include "CanFTP_TimeHandlers.h"

/*
    Структура параметров состояния на этапе PING
*/
typedef struct _CanFTP_Client_Agent_PingControler
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
    // Флаги подтверждения приема сообщений Response 
    CanFTP_Logical_t pingResponsesAck[2];
    // Триггер повторной отправки сообщений в случае, если не был получен ответ
    CanFTP_TimeTrigger_t reapeateSendingTrigger;
    // Триггер возврата в состояние ожидания
    CanFTP_TimeTrigger_t coolingDownTrigger;
    // Номер запрашиваемого сообщения для отправки
    uint8_t requestedMessageIndex;

} CanFTP_Client_Agent_PingControler_t;
/*
    Структура управления процессом блокирования логики
*/
typedef struct _CanFTP_Client_LogicLockController
{
    // Структура запросов к агенту
    struct
    {
        // Запрос на блокирование логики
        CanFTP_Logical_t requestToLockLogic;
    } requsts;
    // Структура выходных параметров
    struct
    {
        // Состояние блокирование логики
        CanFTP_Logical_t isLocked;
    } statuses;

} CanFTP_Client_LogicLockController_t;


#endif // CANFTP_CLIENT_AGENTS_DEFINES_H_
