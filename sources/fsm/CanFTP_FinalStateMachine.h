/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_FINALSTATEMACHINE_H_
#define CANFTP_FINALSTATEMACHINE_H_

#include "CanFTP_FinalStateMachine_Defines.h"

/*
    Инициализация конечного автомата состояний
*/
void CanFTP_FinalStateMachine_Init(CanFTP_FinalStateMachine_t* fsm
    // Количество состояний
    , uint32_t statesCount
    // Массив обработчиков состояний
    , CanFTP_FinalStateMachine_State_t* statesHandlers
    // Состояние по умолчанию
    , uint32_t defauleState
);
/*
    Вызов конечного автомата состояний
*/
void CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_t* fsm);
/*
    Изменить состояние конечного автомата
*/
void CanFTP_FinalStateMachine_ChangeState(CanFTP_FinalStateMachine_t* fsm, CanFTP_FinalStateMachineStateIndex_t newState);
/*
    Функция приведения дочерней структуры к структуре конечного автомата
*/
CanFTP_FinalStateMachine_t* CanFTP_FinalStateMachine_Cast(void* fsmChild);

#endif // CANFTP_FINALSTATEMACHINE_H_