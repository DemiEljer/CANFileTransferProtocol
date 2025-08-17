#ifndef CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_
#define CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_

#include "CanFTP_TimeHandlers.h"
#include "CanFTP_IterationsHandler.h"
#include "CanFTP_Server_Session_Params.h"
#include "CanFTP_Session_FileBlock.h"
#include "CanFTP_ClientBlockHandlingStatus.h"

/*
    Контроллер регистрации клиентов
*/
typedef struct _CanFTP_Server_Session_Agent_RegistrationConroller
{
    // Индекс регистрируемого клиента
    CanFTP_DeviceCode_t clientIndex;
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendMessageCounter;

} CanFTP_Server_Session_Agent_RegistrationConroller_t;
/*
    Контроллер отправки сообщений управления сессией
*/
typedef struct _CanFTP_Server_Session_Agent_SessionConroller
{
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendMessageCounter;

} CanFTP_Server_Session_Agent_SessionConroller_t;
/*
    Контроллер отправки сообщений блока файла
*/
typedef struct _CanFTP_Server_Session_Agent_BlockConroller
{
    // Запросы к контроллеру
    struct
    {
        // Запрос на сброс блока
        CanFTP_Logical_t blockFramesFlagsResetRequst;

    } requests;
    // Статусы
    struct
    {
        // Флаг, что обрабатывается новый блока
        CanFTP_Logical_t newBlockIsHanling;

    } statuses;
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendControlMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendControlMessageCounter;
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendDataMessageTrigger;
    // Счетчик повторной отправки блока
    CanFTP_IterationsHandler_t sendBlockCounter;
    // Идекс первого байта блока
    CanFTP_FileLength_t firstBlockByteIndex;
    // Блок файла
    CanFTP_Session_FileBlock_t fileBlock;
    // Идекс кадра
    CanFTP_FrameIndex_t currentFrameIndex;
    // Идекс кадра
    CanFTP_BlockIndex_t currentBlockIndex;
    // CRC-сумма блока
    uint8_t fileBlockCRC[8];

} CanFTP_Server_Session_Agent_BlockConroller_t;

#endif // CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_
