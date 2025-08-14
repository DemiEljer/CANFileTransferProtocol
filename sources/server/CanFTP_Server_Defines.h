#ifndef CANFTP_SERVER_DEFINES_H_
#define CANFTP_SERVER_DEFINES_H_

#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_ServerState.h"
#include "CanFTP_Server_Agents.h"
#include "CanFTP_Messages_Hub.h"
#include "CanFTP_Server_Session.h"
#include "CanFTP_Server_Debug.h"
#include "CanFTP_Server_Agents.h"
#include "CanFTP_Server_ClientsCollection.h"
#include "CanFTP_Server_SessionsCollection.h"
#include "CanFTP_Server_Session_Configuration.h"

// Структура сервера
typedef struct _CanFTP_Server CanFTP_Server_t;

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Server_MessageSendCallback_t)(CanFTP_Server_t* server, CanFTP_CanMessage_t* message);
// Тип функции события находждения клиента
typedef void (*CanFTP_Server_ClientFoundCallback_t)(CanFTP_Server_t* server, CanFTP_Server_Client_t* client);
// Тип функции события завершения сессии
typedef void (*CanFTP_Server_SessionFinishCallback_t)(CanFTP_Server_t* server
    , CanFTP_Server_Session_t* session
    , CanFTP_SessionStatus_t status
    , CanFTP_DeviceCode_t activeClientsCount);
// Тип функции запроса установки параметров блока
typedef void (*CanFTP_Server_GetFileBlockCallback_t)(CanFTP_Server_t* server
    , CanFTP_Server_Session_t* session
    , CanFTP_Session_FileBlock_t* fileBlock
    , CanFTP_FileLength_t startByteIndex
    , CanFTP_FileLength_t bytesCount);
// Тип функции события освобождения клиента из сессии
typedef void (*CanFTP_Server_ClientReleaseCallback_t)(CanFTP_Server_t* server
    , CanFTP_Server_Session_t* session
    , CanFTP_Server_Client_t* client
    , CanFTP_SessionStatus_t status);


/*
    Структура сервера
*/
typedef struct _CanFTP_Server
{
    // Конечный автомат состояния сервера
    struct 
    {
        // Структура конечного автомата
        CanFTP_FinalStateMachine_t fms;
        // Обработчики конечного автомата
        CanFTP_FinalStateMachine_State_t states[CANFTP_SERVERSTATES_COUNT]; 

    } fms;
    // Состояние сервера
    CanFTP_ServerState_t* state;
    // Агенты логики работы сервера
    struct
    {
        // Контроллер обработки процесса Ping
        CanFTP_Server_Agent_PingControler_t pingController;
    
    } agents;
    // Хаб приема сообщений
    CanFTP_Messages_Hub_t messagesHub;
    // Коллекция клиентов
    CanFTP_Server_ClientsCollection_t clients;
    // Коллекция сессий
    CanFTP_Server_SessionsCollection_t sessions;
    // Конфигурация сессии по умолчанию
    CanFTP_Server_Session_Configuration_t defaultSessionConfiguration;
    // Обратные вызовы
    struct
    {
        // Обратный вызов отправки сообщений
        CanFTP_Server_MessageSendCallback_t sendMessageCallback;
        // Событие находления клиента
        CanFTP_Server_ClientFoundCallback_t clientFoundCallback;
        // Обратный вызов события завершения сессии
        CanFTP_Server_SessionFinishCallback_t sessionFinishedCallback;
        // Обратный вызов запроса блока файла
        CanFTP_Server_GetFileBlockCallback_t getFileBlockCallback;
        // Обратный вызов особождения клиента из сессии
        CanFTP_Server_ClientReleaseCallback_t clientReleaseCallback;

    } callbacks;
    // Параметры управления сервером
    struct
    {
        // Флаг управления вызовом сессий из сервера
        CanFTP_Logical_t doesServerInvokeSessions;

    } controls;

} CanFTP_Server_t;

#endif // CANFTP_SERVER_DEFINES_H_
