#ifndef CANFTP_CLIENT_DEFINES_H_
#define CANFTP_CLIENT_DEFINES_H_

#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_DeviceConfig_Defines.h"
#include "CanFTP_ClientState.h"
#include "CanFTP_Messages_Hub.h"

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Client_MessageSendCallback_t)(CanFTP_CanMessage_t*);

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
    } callbacks;

} CanFTP_Client_t;

#endif // CANFTP_CLIENT_DEFINES_H_