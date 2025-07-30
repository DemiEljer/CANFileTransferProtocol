#include "CanFTP_Client_States_Handlers.h"

#include "stdio.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Client_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

/*
    Обработка состояния IDLE
*/
#ifndef CLIENT_STATE_IDLE_
#define CLIENT_STATE_IDLE_

void CanFTP_Client_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_IDLE_Enter\r\n");
}

uint32_t CanFTP_Client_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PING_RESPONSING;
}

void CanFTP_Client_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_IDLE_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_
/*
    Обработка состояния PING_RESPONSING
*/
#ifndef CLIENT_STATE_PING_RESPONSING_
#define CLIENT_STATE_PING_RESPONSING_

void CanFTP_Client_State_PING_RESPONSING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_RESPONSING_Enter\r\n");
}

uint32_t CanFTP_Client_State_PING_RESPONSING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PING_FINISHED;
}

void CanFTP_Client_State_PING_RESPONSING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_RESPONSING_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_
/*
    Обработка состояния PING_FINISHED
*/
#ifndef CLIENT_STATE_PING_FINISHED_
#define CLIENT_STATE_PING_FINISHED_

void CanFTP_Client_State_PING_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_FINISHED_Enter\r\n");
}

uint32_t CanFTP_Client_State_PING_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_IDLE;
}

void CanFTP_Client_State_PING_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    printf("CanFTP_Client_State_PING_FINISHED_Leave\r\n");
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния SESSION_REGISTRATED
*/
#ifndef CLIENT_STATE_SESSION_REGISTRATED_
#define CLIENT_STATE_SESSION_REGISTRATED_

void CanFTP_Client_State_SESSION_REGISTRATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

uint32_t CanFTP_Client_State_SESSION_REGISTRATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
}

void CanFTP_Client_State_SESSION_REGISTRATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния SESSION_CONFIGURED
*/
#ifndef CLIENT_STATE_SESSION_CONFIGURED_
#define CLIENT_STATE_SESSION_CONFIGURED_

void CanFTP_Client_State_SESSION_CONFIGURED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_SESSION_CONFIGURED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_CONFIGURED;
}

void CanFTP_Client_State_SESSION_CONFIGURED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния SESSION_STARTED
*/
#ifndef CLIENT_STATE_SESSION_STARTED_
#define CLIENT_STATE_SESSION_STARTED_

void CanFTP_Client_State_SESSION_STARTED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_SESSION_STARTED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_STARTED;
}

void CanFTP_Client_State_SESSION_STARTED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния SESSION_FINISHED
*/
#ifndef CLIENT_STATE_SESSION_FINISHED_
#define CLIENT_STATE_SESSION_FINISHED_

void CanFTP_Client_State_SESSION_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_SESSION_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_FINISHED;
}

void CanFTP_Client_State_SESSION_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния BLOCK_RECIEVING
*/
#ifndef CLIENT_STATE_BLOCK_RECIEVING_
#define CLIENT_STATE_BLOCK_RECIEVING_

void CanFTP_Client_State_BLOCK_RECIEVING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_BLOCK_RECIEVING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_RECIEVING;
}

void CanFTP_Client_State_BLOCK_RECIEVING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния BLOCK_FINISHED
*/
#ifndef CLIENT_STATE_BLOCK_FINISHED_
#define CLIENT_STATE_BLOCK_FINISHED_

void CanFTP_Client_State_BLOCK_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_BLOCK_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_FINISHED;
}

void CanFTP_Client_State_BLOCK_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_

/*
    Обработка состояния BLOCK_NEXTBLOCKREADY
*/
#ifndef CLIENT_STATE_BLOCK_NEXTBLOCKREADY_
#define CLIENT_STATE_BLOCK_NEXTBLOCKREADY_

void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY;
}

void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_IDLE_
