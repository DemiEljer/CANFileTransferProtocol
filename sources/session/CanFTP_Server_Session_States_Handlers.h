/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_STATES_HANDLERS_H_
#define CANFTP_SERVER_SESSION_STATES_HANDLERS_H_

#include "CanFTP_Server_Session_Messages_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Server_Session_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms);
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Server_Session_IterationEventHandler(CanFTP_FinalStateMachine_t *fms);

/*
    Обработка состояния CREATED
*/
void CanFTP_Server_Session_State_CREATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_CREATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_CREATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния REGISTRATING
*/
void CanFTP_Server_Session_State_REGISTRATING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_REGISTRATING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_REGISTRATING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния CONFIGURING
*/
void CanFTP_Server_Session_State_CONFIGURING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_CONFIGURING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_CONFIGURING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния STARTING
*/
void CanFTP_Server_Session_State_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния FINISHING
*/
void CanFTP_Server_Session_State_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния FINISHED
*/
void CanFTP_Server_Session_State_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_STARTING
*/
void CanFTP_Server_Session_State_BLOCK_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_BLOCK_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_BLOCK_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_SENDING
*/
void CanFTP_Server_Session_State_BLOCK_SENDING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_BLOCK_SENDING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_BLOCK_SENDING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);
/*
    Обработка состояния BLOCK_FINISHING
*/
void CanFTP_Server_Session_State_BLOCK_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel);
uint32_t CanFTP_Server_Session_State_BLOCK_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel);
void CanFTP_Server_Session_State_BLOCK_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel);


#endif // CANFTP_SERVER_SESSION_STATES_HANDLERS_H_