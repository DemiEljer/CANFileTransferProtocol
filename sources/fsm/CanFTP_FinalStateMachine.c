#include "CanFTP_FinalStateMachine.h"

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
)
{
    // Инициализация конечного автомата
    {
        fsm->state = defauleState;
        fsm->previouseState = defauleState;
        CanFTP_TimeHandlers_UpdateTimeMark(&(fsm->timemark));
        fsm->statesCount = statesCount;
        fsm->statesHandlers = statesHandlers;
        fsm->callbacks.changeStateCallback = 0;
        fsm->callbacks.iterationCallback = 0;
    }
    // Верификация обработчиков состояний
    {
        uint32_t i = 0;

        for (i = 0; i < fsm->statesCount; i++)
        {
            CanFTP_FinalStateMachine_State_t* state = &(fsm->statesHandlers[i]);
            // Вызов исключения в случае, если не установлен один из обязательных параметров
            if (state->handlers.bodyStateHandler == 0)
            {
                CanFTP_ThrowError();
            }
        }
    }
    // Обработка состояния по умолчанию
    {
        // Проверка, что назначено валидное состоние
        if (fsm->statesCount > 0
            && fsm->state != 0
            && fsm->state >= fsm->statesCount)
        {
            CanFTP_ThrowError();
        }
        else if (fsm->statesCount > 0)
        {
            CanFTP_FinalStateMachine_State_t* state = &(fsm->statesHandlers[fsm->state]);
            // Вызов логики входа в состояние
            if (state->handlers.enterStateHandler != 0)
            {
                state->handlers.enterStateHandler(fsm, state->stateModel);
            }
        }
    }
}
/*
    Вызов конечного автомата состояний
*/
void CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_t* fsm)
{
    // Вызов обратного вызова итерации логики работы
    if (fsm->callbacks.iterationCallback != 0)
    {
        fsm->callbacks.iterationCallback(fsm);
    }
    // Обработка вызова логики состояния
    {
        CanFTP_FinalStateMachine_State_t* currentState = &(fsm->statesHandlers[fsm->state]);
        // Вызов логики обработки состояния
        CanFTP_FinalStateMachineStateIndex_t nextStateIndex = currentState->handlers.bodyStateHandler(fsm, currentState->stateModel);

        CanFTP_FinalStateMachine_ChangeState(fsm, nextStateIndex);
    }
}
/*
    Изменить состояние конечного автомата
*/
void CanFTP_FinalStateMachine_ChangeState(CanFTP_FinalStateMachine_t* fsm, CanFTP_FinalStateMachineStateIndex_t newState)
{
    // Обработка перехода в другое состояние
    if (newState != fsm->state)
    {
        CanFTP_FinalStateMachine_State_t* currentState = &(fsm->statesHandlers[fsm->state]);
        // Вызов логики выхода из состояния
        if (currentState->handlers.leaveStateHandler != 0)
        {
            currentState->handlers.leaveStateHandler(fsm, currentState->stateModel);
        }
        // Проверка валидности перехода в новое состояние
        if (newState >= fsm->statesCount)
        {
            CanFTP_ThrowError();
        }
        else
        {
            // Обновление параметров конечного автомата
            {
                fsm->previouseState = fsm->state;
                fsm->state = newState;
                CanFTP_TimeHandlers_UpdateTimeMark(&(fsm->timemark));
            }
            // Обработка логики входа в новое состояние
            {
                CanFTP_FinalStateMachine_State_t* nextState = &(fsm->statesHandlers[fsm->state]);

                if (nextState->handlers.enterStateHandler != 0)
                {
                    nextState->handlers.enterStateHandler(fsm, currentState->stateModel);
                }
            }
            //
            if (fsm->callbacks.changeStateCallback != 0)
            {
                fsm->callbacks.changeStateCallback(fsm);
            }
        }
    }
}
/*
    Метод приведения дочерней структуры к структуре конечного автомата
*/
CanFTP_FinalStateMachine_t* CanFTP_FinalStateMachine_Cast(void* fsmChild)
{
    return (CanFTP_FinalStateMachine_t*)(fsmChild);
}
