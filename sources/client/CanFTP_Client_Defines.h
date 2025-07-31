#ifndef CANFTP_CLIENT_DEFINES_H_
#define CANFTP_CLIENT_DEFINES_H_

#include "CanFTP_Random.h"
#include "CanFTP_Client_Agents_Defines.h"
#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_DeviceConfig_Defines.h"
#include "CanFTP_ClientState.h"
#include "CanFTP_Messages_Hub.h"

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Client_MessageSendCallback_t)(CanFTP_CanMessage_t*);
// Тип функции обратной связи запроса к внешней логике
typedef CanFTP_Logical_t (*CanFTP_Client_Requestallback_t)(void);

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
    
    } agents;
    // Состояние клиента
    CanFTP_ClientState_t* state;
    // Хаб приема сообщений
    CanFTP_Messages_Hub_t messagesHub;
    // Конфигурация устройства
    CanFTP_DeviveConfig_t devicveConfig;
    // Структура управления сессией

    // Обратные вызовы
    struct
    {
        // Обратный вызов отправки сообщений
        CanFTP_Client_MessageSendCallback_t sendMessageCallback;
        // Обратный вызов запроса на блокировку логики (0 - не заблокирована, 1 - заблокирована)
        CanFTP_Client_Requestallback_t lockLogicRequestCallback;
        // Обратный вызов запроса на разблокировку логики (0 - не разблокирована, 1 - разблокирована)
        CanFTP_Client_Requestallback_t unlockLogicRequestCallback;
    } callbacks;

} CanFTP_Client_t;

#endif // CANFTP_CLIENT_DEFINES_H_