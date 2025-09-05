/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENT_DEFINES_H_
#define CANFTP_CLIENT_DEFINES_H_

#include "CanFTP_Random.h"
#include "CanFTP_Client_Agents_Defines.h"
#include "CanFTP_FinalStateMachine.h"
#include "CanFTP_DeviceConfig.h"
#include "CanFTP_ClientState.h"
#include "CanFTP_Messages_Hub.h"
#include "CanFTP_Client_Debug.h"

// Структура клиента передачи файла
typedef struct _CanFTP_Client CanFTP_Client_t;

// Тип функции обратной связи отпраки сообщения
typedef void (*CanFTP_Client_MessageSendCallback_t)(CanFTP_Client_t* client, CanFTP_CanMessage_t* message);
// Тип функции обратной связи запроса к внешней логике
typedef CanFTP_Logical_t (*CanFTP_Client_RequestCallback_t)(CanFTP_Client_t* client);
// Тип функции обратного вызова согласования сессии
typedef CanFTP_Logical_t (*CanFTP_Client_SessionConfigurationCallback_t)(CanFTP_Client_t* client, CanFTP_Client_Session_Configuration_t* sessionConfiguration);
// Тип функции обратной связи успешного приема блока файла
typedef void (*CanFTP_Client_BlockRecieceCallback_t)(CanFTP_Client_t* client
    , CanFTP_FileLength_t startByteIndex
    , CanFTP_FileLength_t bytesCount
    , uint8_t* data);
// Тип функции обратной связи завершения сессии
typedef void (*CanFTP_Client_SessionFinishedCallback_t)(CanFTP_Client_t* client
    , CanFTP_SessionStatus_t sessionStatus
    , CanFTP_SoftwareVersion_t* newSoftVersion);

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
    // Агенты логики работы клинета
    struct
    {
        // Генератор случайных значений
        CanFTP_Random_t random;
        // Контроллер блокирования логики работы
        CanFTP_Client_Agent_LogicLockController_t logicLockController;
        // Контроллер обработки процесса Ping
        CanFTP_Client_Agent_PingControler_t pingController;
        // Контроллер сесии
        CanFTP_Client_Agent_SessionController_t sessionController;
    
    } agents;
    // Состояние клиента
    CanFTP_ClientState_t* state;
    // Хаб приема сообщений
    CanFTP_Messages_Hub_t messagesHub;
    // Конфигурация устройства
    CanFTP_DeviceConfig_t deviceConfig;
    // Параметры управления
    struct
    {
        // Разрешенеи на переход в состояние Ping
        CanFTP_Logical_t pingPermition;
        // Разрешение на активацию сессии
        CanFTP_Logical_t sessionStartPermition;
        // Автоматически обновить номер версии при успешном завершении сессии
        CanFTP_Logical_t autpUpdateSoftVersion;

    } control;
    // Обратные вызовы
    struct
    {
        // Обратный вызов отправки сообщений
        CanFTP_Client_MessageSendCallback_t sendMessageCallback;
        // Обратный вызов запроса на блокировку логики (0 - не заблокирована, 1 - заблокирована)
        CanFTP_Client_RequestCallback_t lockLogicRequestCallback;
        // Обратный вызов запроса на разблокировку логики (0 - не разблокирована, 1 - разблокирована)
        CanFTP_Client_RequestCallback_t unlockLogicRequestCallback;
        // Обратный вызов конфигурации сессии (0 - сессия не прошла валидацию, 1 - сессия прошла валидацию)
        CanFTP_Client_SessionConfigurationCallback_t sessionConfigureationCallback;
        // Обратный вызов успешного приема блока файла 
        CanFTP_Client_BlockRecieceCallback_t blockRecieceCallback;
        // Обратный вызов завершения сессии
        CanFTP_Client_SessionFinishedCallback_t sessionFinishedCallback;

    } callbacks;

} CanFTP_Client_t;

#endif // CANFTP_CLIENT_DEFINES_H_