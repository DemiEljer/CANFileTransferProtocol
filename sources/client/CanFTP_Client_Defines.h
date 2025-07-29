#ifndef CANFTP_CLIENT_DEFINES_H_
#define CANFTP_CLIENT_DEFINES_H_

#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_DeviceConfig_Defines.h"
#include "CanFTP_ClientState.h"


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
    // Конфигурация устройства
    CanFTP_DeviveConfig_t devicveConfig;
    // Структура управления сессией

    // События
    

} CanFTP_Client_t;

#endif // CANFTP_CLIENT_DEFINES_H_