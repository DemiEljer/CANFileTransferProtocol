#ifndef CANFTP_SERVER_H_
#define CANFTP_SERVER_H_

#include "CanFTP_Server_Defines.h"

/*
    Инициализация сервера
*/
void CanFTP_Server_Init(CanFTP_Server_t *server);
/*
    Вызов логики обработки клиента
*/
void CanFTP_Server_Invoke(CanFTP_Server_t *server);
/*
    Обработка получения сообщений
*/
void CanFTP_Server_RecieveCanMessage(CanFTP_Server_t *server, CanFTP_CanMessage_t* canMessage);
/*
    Запустить процесс Ping
*/
CanFTP_Logical_t CanFTP_Server_StartPing(CanFTP_Server_t *server);
/*
    Остановить процесс Ping
*/
void CanFTP_Server_StopPing(CanFTP_Server_t *server);

#endif // CANFTP_SERVER_H_
