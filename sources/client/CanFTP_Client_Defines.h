#ifndef CANFTP_CLIENT_DEFINES_H_
#define CANFTP_CLIENT_DEFINES_H_

#include "CanFTP_Random.h"
#include "CanFTP_Client_Agents_Defines.h"
#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_DeviceConfig.h"
#include "CanFTP_ClientState.h"
#include "CanFTP_Messages_Hub.h"

/*
    В процессе Ping каждый раз выбирается произвольный интервал ответа в заданном диапазоне
*/
// Минимальный интервал времени Ping
#define CANFTP_CLIENT_MINPINGINTERVAL 10
// Максимальный интервал времени Ping
#define CANFTP_CLIENT_MAXPINGINTERVAL 100

// Структура клиента передачи файла
typedef struct _CanFTP_Client CanFTP_Client_t;

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Client_MessageSendCallback_t)(CanFTP_Client_t*, CanFTP_CanMessage_t*);
// Тип функции обратной связи запроса к внешней логике
typedef CanFTP_Logical_t (*CanFTP_Client_RequestCallback_t)(CanFTP_Client_t*);
// Тип функции обратного вызова согласования сессии
typedef CanFTP_Logical_t (*CanFTP_Client_SessionConfigurationCallback)(CanFTP_Client_t*, CanFTP_Session_Configuration_t*);
// Тип функции обратной связи к внешней логике
typedef CanFTP_Logical_t (*CanFTP_Client_Callback_t)(CanFTP_Client_t*);
// Тип функции обратной связи успешного приема блока файла
typedef CanFTP_Logical_t (*CanFTP_Client_BlockRecieceCallback_t)(CanFTP_Client_t*, CanFTP_Session_FileBlock_t*);
// Тип функции обратной связи завершения сессии
typedef CanFTP_Logical_t (*CanFTP_Client_SessionFinishedCallback_t)(CanFTP_Client_t*, CanFTP_SessionStatus_t, CanFTP_SofwareVersion_t*);

/*
    Структура клиента передачи файла
*/
typedef struct _CanFTP_Client
{
    // Конечный автомат состояния клиента
    struct 
    {
        // Структура конечного автомата
        CanFTP_FinalStateMachine_t fms;
        // Обработчики конечного автомата
        CanFTP_FinalStateMachine_State_t states[CANFTP_CLIENTSTATES_COUNT]; 
    } fms;
    // Агенты логики работы клинета
    struct
    {
        // Генератор случайных значений
        CanFTP_Random_t random;
        // Контроллер блокирования логики работы
        CanFTP_Client_LogicLockController_t logicLockController;
        // Контроллер обработки процесса Ping
        CanFTP_Client_Agent_PingControler_t pingController;
        // Контроллер сесии
        CanFTP_Client_SessionController_t sessionController;
    
    } agents;
    // Состояние клиента
    CanFTP_ClientState_t* state;
    // Хаб приема сообщений
    CanFTP_Messages_Hub_t messagesHub;
    // Конфигурация устройства
    CanFTP_DeviveConfig_t devicveConfig;
    // Параметры управления
    struct
    {
        // Разрешенеи на переход в состояние Ping
        CanFTP_Logical_t pingPermition;
        // Разрешение на активацию сессии
        CanFTP_Logical_t sessionStartPermition;
        // Автоматически обновить номер версии при успешном завершении сессии
        CanFTP_Logical_t autpUpdateSoftVersion;

    } control;
    // Обратные вызовы
    struct
    {
        // Обратный вызов отправки сообщений
        CanFTP_Client_MessageSendCallback_t sendMessageCallback;
        // Обратный вызов запроса на блокировку логики (0 - не заблокирована, 1 - заблокирована)
        CanFTP_Client_RequestCallback_t lockLogicRequestCallback;
        // Обратный вызов запроса на разблокировку логики (0 - не разблокирована, 1 - разблокирована)
        CanFTP_Client_RequestCallback_t unlockLogicRequestCallback;
        // Обратный вызов конфигурации сессии (0 - сессия не прошла валидацию, 1 - сессия прошла валидацию)
        CanFTP_Client_SessionConfigurationCallback sessionConfigureationCallback;
        // Обратная связь успешного приема блока файла 
        CanFTP_Client_BlockRecieceCallback_t blockRecieceCallback;
        // Обратная связь завершения сессии
        CanFTP_Client_SessionFinishedCallback_t sessionFinishedCallback;

    } callbacks;

} CanFTP_Client_t;

#endif // CANFTP_CLIENT_DEFINES_H_