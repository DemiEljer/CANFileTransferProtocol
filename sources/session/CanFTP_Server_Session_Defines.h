#ifndef CANFTP_SERVER_SESSION_DEFINES_H_
#define CANFTP_SERVER_SESSION_DEFINES_H_

#include "CanFTP_Server_Session_Client.h"
#include "CanFTP_Messages_Hub.h"
#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_SessionState.h"
#include "CanFTP_Server_Session_Configuration.h"
#include "CanFTP_Server_Session_ClientsCollection.h"
#include "CanFTP_SessionStatus.h"

// Структура сессии на стороне серевера
typedef struct _CanFTP_Server_Session CanFTP_Server_Session_t;

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Server_Session_MessageSendCallback_t)(void*, CanFTP_CanMessage_t*);
// Тип функции события завершения сессии
typedef void (*CanFTP_Server_Session_SessionFinishCallback_t)(void*, CanFTP_Server_Session_t session, CanFTP_SessionStatus_t);

/*
    Структура сессии на стороне серевера
*/
typedef struct _CanFTP_Server_Session
{
    // Конечный автомат состояния сессии
    struct 
    {
        // Структура конечного автомата
        CanFTP_FinalStateMachine_t fms;
        // Обработчики конечного автомата
        CanFTP_FinalStateMachine_State_t states[CANFTP_SESSIONSTATES_COUNT]; 

    } fms;
    // Состояние сессии
    CanFTP_SessionState_t* state;
    // Запросы к сессии
    struct 
    {
        // Запрос на запуск сессии
        CanFTP_Logical_t startRequest;
        // Запрос на остановку сессии
        CanFTP_Logical_t stopRequest;
        // Запрос на удаление сессии
        CanFTP_Logical_t deleteRequest;

    } requests; 
    // Статусы сессии
    struct 
    {
        // Флаг, что сессия была завершена и может быть удалена
        CanFTP_Logical_t canBeDisposed;
        // Подтверждение факта инициализации клиентов
        CanFTP_Logical_t clientsAreInited;

    } statuses; 
    // Обратные вызовы
    struct
    {
        // Обратный вызов отправки сообщений
        CanFTP_Server_Session_MessageSendCallback_t sendMessageCallback;
        // Обратный вызов события завершения сессии
        CanFTP_Server_Session_SessionFinishCallback_t sessionFinishedCallback;

    } callbacks;
    // Указатель на сервер, с которым ассоциирована сессия
    void* server;
    // Код сессии
    CanFTP_SessionCode_t code;
    // Конфигурация сессии
    CanFTP_Server_Session_Configuration_t configuration;
    // Коллекция клиентов сессии
    CanFTP_Server_Session_ClientsCollection_t clients;

} CanFTP_Server_Session_t;

#endif // CANFTP_SERVER_SESSION_DEFINES_H_
