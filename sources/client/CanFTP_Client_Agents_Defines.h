#ifndef CANFTP_CLIENT_AGENTS_DEFINES_H_
#define CANFTP_CLIENT_AGENTS_DEFINES_H_

#include "CanFTP_TimeHandlers.h"
#include "CanFTP_Session.h"
#include "CanFTP_SessionStatus.h"
#include "CanFTP_IterationsHandler.h"
#include "CanFTP_ClientBlockHandlingStatus.h"
#include "CanFTP_SofwareVersion.h"

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
        // Версия протокола была верифицирована
        CanFTP_Logical_t isProtocolVersionVerified;
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
/*
    Структура управления сессией
*/
typedef struct _CanFTP_Client_SessionController
{
    // Структура запросов к агенту
    struct
    {
        // Запрос на запуск сессиии
        CanFTP_Logical_t requestSession;
        // Запрос на переход в состояние конфигурации
        CanFTP_Logical_t configurationRequest;
        // Запрос на начало сессии
        CanFTP_Logical_t startRequest;
        // Запрос на остановку сессии
        CanFTP_Logical_t stopRequest;
        // Запрос на начало чтения блока
        CanFTP_Logical_t startBlockRequest;
        // Запрос на обработку фреймов блока
        CanFTP_Logical_t recievingBlockRequest;
        // Запрос на окончание чтения блока
        CanFTP_Logical_t stopBlockRequest;
        // Подтверждение получения ответа о статусе блока
        CanFTP_Logical_t blockFinishAckRecieved;

    } requsts;
    // Структура выходных параметров
    struct
    {
        // Статус состояния сессии
        CanFTP_SessionStatus_t sessionStatus;
        // Флаг, что параметры сессии были согласованы
        CanFTP_Logical_t sessionHasBeenVerified;
        // Флаг, что все фреймы блока были получены
        CanFTP_Logical_t allBlocksFramesWereRecieved;
        // CRC-сумма блока
        uint8_t blockCRC[CANFTP_FILEBLOCK_CRCLENGTH];
        // Статус обработки блока
        CanFTP_ClientBlockHandlingStatus_t blockHandlingStatus;
        // Итоговая длина файла
        CanFTP_FileLength_t resultFileLength;
        // Флаг, что обрабатывается новый блок
        CanFTP_Logical_t newBlockIsHandling;

    } statuses;
    // Сессия передачи файла
    CanFTP_Session_t session;
    // Ассоция клиента c сессией
    CanFTP_Session_ClientAssosiation_t clientAssosiation;
    // Триггер повторной отправки сообщения подтверждения
    CanFTP_TimeTrigger_t repeateAckTrigger;
    // Триггер отключения сессии по потери связи с сервером
    CanFTP_TimeTrigger_t lostConnectionTrigger;
    // Счетчик количества повторений подтверждений Ack
    CanFTP_IterationsHandler_t repeateAckCounter;
    // Новая версия файла
    CanFTP_SofwareVersion_t newSoftVersion;

} CanFTP_Client_SessionController_t;


#endif // CANFTP_CLIENT_AGENTS_DEFINES_H_
