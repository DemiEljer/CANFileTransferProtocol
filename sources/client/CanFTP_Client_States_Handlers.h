#ifndef CANFTP_CLIENT_STATES_HANDLERS_H_
#define CANFTP_CLIENT_STATES_HANDLERS_H_

#include "CanFTP_Client_Messages_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Client_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms);
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Client_IterationEventHandler(CanFTP_FinalStateMachine_t *fms);

/*
    Обработка состояния IDLE
*/
void CanFTP_Client_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния PING_RESPONSING
*/
void CanFTP_Client_State_PING_RESPONSING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_PING_RESPONSING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_PING_RESPONSING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния PING_FINISHED
*/
void CanFTP_Client_State_PING_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_PING_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_PING_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния PROTOCOL_ACTIVE
*/
void CanFTP_Client_State_PROTOCOL_ACTIVE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_PROTOCOL_ACTIVE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_PROTOCOL_ACTIVE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния SESSION_REGISTRATED
*/
void CanFTP_Client_State_SESSION_REGISTRATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_SESSION_REGISTRATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_SESSION_REGISTRATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния SESSION_CONFIGURED
*/
void CanFTP_Client_State_SESSION_CONFIGURED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_SESSION_CONFIGURED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_SESSION_CONFIGURED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния SESSION_STARTED
*/
void CanFTP_Client_State_SESSION_STARTED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_SESSION_STARTED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_SESSION_STARTED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния SESSION_FINISHED
*/
void CanFTP_Client_State_SESSION_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_SESSION_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_SESSION_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_RECIEVING
*/
void CanFTP_Client_State_BLOCK_RECIEVING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_BLOCK_RECIEVING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_BLOCK_RECIEVING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_FINISHED
*/
void CanFTP_Client_State_BLOCK_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_BLOCK_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_BLOCK_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_NEXTBLOCKREADY
*/
void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_NEXTBLOCKREADY
*/
void CanFTP_Client_State_PROTOCOL_DISABLING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Client_State_PROTOCOL_DISABLING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Client_State_PROTOCOL_DISABLING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);

#endif // CANFTP_CLIENT_STATES_HANDLERS_H_
