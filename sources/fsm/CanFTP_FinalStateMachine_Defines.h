#ifndef CANFTP_FINALSTATEMACHINE_DEFINES_H_
#define CANFTP_FINALSTATEMACHINE_DEFINES_H_

#include "CanFTP_TimeHandlers.h"

// Тип состояния конечного автомата
typedef uint32_t CanFTP_FinalStateMachineStateIndex_t;
// Предобъявление структуры обрабтчика конечного автомата
typedef struct _CanFTP_FinalStateMachine CanFTP_FinalStateMachine_t;
// Типы функций обратного вызова при обработке конечных автоматов
typedef void (*CanFTP_FinalStateMachine_Callback_t)(CanFTP_FinalStateMachine_t*);
/*
    Тип функций обработки состояния конечного автомата
    Arg1 - указатель на конечный автомат
    Arg2 - указатель на объект управления состоянием
*/ 
typedef void (*CanFTP_FinalStateMachine_LeaveEnterStateHandler_t)(CanFTP_FinalStateMachine_t*, void*);
/*
    Тип функций обработки состояния конечного автомата
    Return - номер состояния
    Arg1 - указатель на конечный автомат
    Arg2 - указатель на объект управления состоянием
*/ 
typedef CanFTP_FinalStateMachineStateIndex_t (*CanFTP_FinalStateMachine_BodyStateHandler_t)(CanFTP_FinalStateMachine_t*, void*);
/*
    Структура обработки состояния
*/
typedef struct _CanFTP_FinalStateMachine_State
{
    // Модель хранения параметров состояния
    void *stateModel;
    // Обработчики состояний
    struct
    {
        // Функция обработки входа в состояние
        CanFTP_FinalStateMachine_LeaveEnterStateHandler_t enterStateHandler;
        // Функция обработки тела состояния
        CanFTP_FinalStateMachine_BodyStateHandler_t bodyStateHandler;
        // Функция обработки выхода из состояния
        CanFTP_FinalStateMachine_LeaveEnterStateHandler_t leaveStateHandler;
    } handlers;

} CanFTP_FinalStateMachine_State_t;
/*
    Структура обобщенного конечного автомата
*/
typedef struct _CanFTP_FinalStateMachine
{
    // Состояние конечного автомата
    CanFTP_FinalStateMachineStateIndex_t state;
    // Метка времени изменения состояния
    CanFTP_TimeMark_t timemark;
    // Предыдущее состояние
    CanFTP_FinalStateMachineStateIndex_t previouseState;
    // Количество состояний
    uint32_t statesCount;
    // Обработчики состояний
    CanFTP_FinalStateMachine_State_t* statesHandlers;
    // Функции обратного вызова
    struct
    {
        // Обратный вызов при мзменение состояния конечного автомата
        CanFTP_FinalStateMachine_Callback_t changeStateCallback;
        // Обратный вызов при итерации логики работы
        CanFTP_FinalStateMachine_Callback_t iterationCallback;
    } callbacks;

} CanFTP_FinalStateMachine_t;

#endif // CANFTP_FINALSTATEMACHINE_DEFINES_H_