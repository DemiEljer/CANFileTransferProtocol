#include "CanFTP_Server_Session_States_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Server_Session_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Server_Session_IterationEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}

#ifndef SERVER_SESSION_STATE_CREATED_
#define SERVER_SESSION_STATE_CREATED_
/*
    Обработка состояния CREATED
*/

void CanFTP_Server_Session_State_CREATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}

uint32_t CanFTP_Server_Session_State_CREATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_CREATED;



    return resultState;
}

void CanFTP_Server_Session_State_CREATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_CREATED_

/*
    Обработка состояния REGISTRATING
*/
#ifndef SERVER_SESSION_STATE_REGISTRATING_
#define SERVER_SESSION_STATE_REGISTRATING_

void CanFTP_Server_Session_State_REGISTRATING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_REGISTRATING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_REGISTRATING;


    
    return resultState;
}

void CanFTP_Server_Session_State_REGISTRATING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_CREATED_

/*
    Обработка состояния CONFIGURING
*/
#ifndef SERVER_SESSION_STATE_CONFIGURING_
#define SERVER_SESSION_STATE_CONFIGURING_

void CanFTP_Server_Session_State_CONFIGURING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_CONFIGURING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_CONFIGURING;


    
    return resultState;
}

void CanFTP_Server_Session_State_CONFIGURING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_CONFIGURING_

/*
    Обработка состояния STARTING
*/
#ifndef SERVER_SESSION_STATE_STARTING_
#define SERVER_SESSION_STATE_STARTING_

void CanFTP_Server_Session_State_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_STARTING;


    
    return resultState;
}

void CanFTP_Server_Session_State_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_STARTING_

/*
    Обработка состояния FINISHING
*/
#ifndef SERVER_SESSION_STATE_FINISHING_
#define SERVER_SESSION_STATE_FINISHING_

void CanFTP_Server_Session_State_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_FINISHING;


    
    return resultState;
}

void CanFTP_Server_Session_State_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_FINISHING_

/*
    Обработка состояния FINISHED
*/
#ifndef SERVER_SESSION_STATE_FINISHED_
#define SERVER_SESSION_STATE_FINISHED_

void CanFTP_Server_Session_State_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_FINISHED;


    
    return resultState;
}

void CanFTP_Server_Session_State_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_FINISHING_

/*
    Обработка состояния BLOCK_STARTING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_STARTING_
#define SERVER_SESSION_STATE_BLOCK_STARTING_

void CanFTP_Server_Session_State_BLOCK_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_STARTING_

/*
    Обработка состояния BLOCK_SENDING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_SENDING_
#define SERVER_SESSION_STATE_BLOCK_SENDING_

void CanFTP_Server_Session_State_BLOCK_SENDING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_SENDING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_SENDING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_SENDING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_SENDING_

/*
    Обработка состояния BLOCK_FINISHING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_FINISHING_
#define SERVER_SESSION_STATE_BLOCK_FINISHING_

void CanFTP_Server_Session_State_BLOCK_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_FINISHING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_FINISHING_
