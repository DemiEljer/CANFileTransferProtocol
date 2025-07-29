#include "CanFTP_Client.h"
#include "stdio.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
static void CanFTP_Client_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

#ifndef CLIENT_STATE_IDLE_
#define CLIENT_STATE_IDLE_

/*
    Переход в состояние IDLE
*/
static void CanFTP_Client_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_IDLE_Enter\r\n");
}
/*
    Обработка тела состояния IDLE
*/
static uint32_t CanFTP_Client_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PING_RESPONSING;
}
/*
    Выход из состояния IDLE
*/
static void CanFTP_Client_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_IDLE_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_

#ifndef CLIENT_STATE_PING_RESPONSING_
#define CLIENT_STATE_PING_RESPONSING_

/*
    Переход в состояние IDLE
*/
static void CanFTP_Client_State_PING_RESPONSING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_RESPONSING_Enter\r\n");
}
/*
    Обработка тела состояния IDLE
*/
static uint32_t CanFTP_Client_State_PING_RESPONSING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PING_FINISHED;
}
/*
    Выход из состояния IDLE
*/
static void CanFTP_Client_State_PING_RESPONSING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_RESPONSING_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_

#ifndef CLIENT_STATE_PING_FINISHED_
#define CLIENT_STATE_PING_FINISHED_

/*
    Переход в состояние IDLE
*/
static void CanFTP_Client_State_PING_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_FINISHED_Enter\r\n");
}
/*
    Обработка тела состояния IDLE
*/
static uint32_t CanFTP_Client_State_PING_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_IDLE;
}
/*
    Выход из состояния IDLE
*/
static void CanFTP_Client_State_PING_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_FINISHED_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_

/*
    Инициализация клиента
*/
void CanFTP_Client_Init(CanFTP_Client_t *client)
{
    // Инициализация обработчиков состояний
    {
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].stateModel = 0;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.enterStateHandler = CanFTP_Client_State_IDLE_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.bodyStateHandler = CanFTP_Client_State_IDLE_Body;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.leaveStateHandler = CanFTP_Client_State_IDLE_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].stateModel = 0;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.enterStateHandler = CanFTP_Client_State_PING_RESPONSING_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.bodyStateHandler = CanFTP_Client_State_PING_RESPONSING_Body;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.leaveStateHandler = CanFTP_Client_State_PING_RESPONSING_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].stateModel = 0;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.enterStateHandler = CanFTP_Client_State_PING_FINISHED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.bodyStateHandler = CanFTP_Client_State_PING_FINISHED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.leaveStateHandler = CanFTP_Client_State_PING_FINISHED_Leave;

        CanFTP_FinalStateMachine_Init(&(client->fms.fms), CANFTP_CLIENTSTATES_COUNT, client->fms.states, CANFTP_CLIENTSTATE_IDLE);   
        // Инициализация обработчика события изменения состояния конечного автомата
        client->fms.fms.callbacks.changeStateCallback = CanFTP_Client_StateChanedEventHandler;
    }
}
/*
    Вызов логики обработки клиента
*/
void CanFTP_Client_Invoke(CanFTP_Client_t *client)
{
    CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_Cast(client));
}