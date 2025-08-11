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
typedef void (*CanFTP_Server_MessageSendCallback_t)(CanFTP_Server_t*, CanFTP_CanMessage_t*);
// Тип функции события находждения клиента
typedef void (*CanFTP_Server_ClientFoundCallback_t)(CanFTP_Server_t*, CanFTP_Server_Client_t*);

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
    // Агенты логики работы сервера
    struct
    {
        // Контроллер обработки процесса Ping
        CanFTP_Server_Agent_PingControler_t pingController;
    
    } agents;
    // Состояние сервера
    CanFTP_ServerState_t* state;
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

    } callbacks;
    // Параметры управления сервером
    struct
    {
        // Флаг управления вызовом сессий из сервера
        CanFTP_Logical_t doesServerInvokeSessions;

    } controls;

} CanFTP_Server_t;

#endif // CANFTP_SERVER_DEFINES_H_
