#ifndef CANFTP_SERVER_STATES_HANDLERS_H_
#define CANFTP_SERVER_STATES_HANDLERS_H_

#include "CanFTP_Server_Messages_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Server_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms);
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Server_IterationEventHandler(CanFTP_FinalStateMachine_t *fms);

/*
    Обработка состояния IDLE
*/
void CanFTP_Server_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния PING
*/
void CanFTP_Server_State_PING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_State_PING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_State_PING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния SESSION
*/
void CanFTP_Server_State_SESSION_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_State_SESSION_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_State_SESSION_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);

#endif // CANFTP_SERVER_STATES_HANDLERS_H_
