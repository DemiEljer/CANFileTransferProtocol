#ifndef CANFTP_SERVER_SESSION_AGENTS_H_
#define CANFTP_SERVER_SESSION_AGENTS_H_

#include "CanFTP_Server_Session_Agents_Defines.h"

/*
    Сбросить контроллер регистрации
*/
void CanFTP_Server_Session_Agent_RegistrationConroller_Reset(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent);
/*
    Перейти к следующему клиенту
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_MoveToNextClient(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount);
/*
    Проверить, остались ли клиенты для регистрации
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount);
/*
    Сброисть контроллер управления сессией
*/
void CanFTP_Server_Session_Agent_SessionConroller_Reset(CanFTP_Server_Session_Agent_SessionConroller_t* agent);
/*
    Обновить параметры отправки соообщений
*/
void CanFTP_Server_Session_Agent_SessionConroller_UpdateSendingParams(CanFTP_Server_Session_Agent_SessionConroller_t* agent
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Сбросить контроллер блока
*/
void CanFTP_Server_Session_Agent_BlockConroller_Reset(CanFTP_Server_Session_Agent_BlockConroller_t* agent);
/*
    Обновить параметры отправки соообщений
*/
void CanFTP_Server_Session_Agent_BlockConroller_UpdateSendingParams(CanFTP_Server_Session_Agent_BlockConroller_t* agent
    // Интервал времени отправки
    , CanFTP_TimeInterval_t controlInterval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t controlMaxCount
    // Интервал времени отправки
    , CanFTP_TimeInterval_t dataInterval
    // Максимальное количество итераций отправки блока
    , CanFTP_IterationCounter_t blockMaxCount);
/*
    Сбросить флаги обработки блока, если запрошено
*/
void CanFTP_Server_Session_Agent_BlockConroller_ResetBlockFlagsIfRequested(CanFTP_Server_Session_Agent_BlockConroller_t* agent);
/*
    Сбросить контроллер перед отправкой блока
*/
void CanFTP_Server_Session_Agent_BlockConroller_ResetBeforeBlockStart(CanFTP_Server_Session_Agent_BlockConroller_t* agent);
/*
    Сбросить контроллер перед отправкой нового блока
*/
CanFTP_FileLength_t CanFTP_Server_Session_Agent_BlockConroller_NextBlock(CanFTP_Server_Session_Agent_BlockConroller_t* agent);

#endif // CANFTP_SERVER_SESSION_AGENTS_H_
