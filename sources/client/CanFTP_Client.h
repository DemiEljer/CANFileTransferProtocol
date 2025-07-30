#ifndef CANFTP_CLIENT_H_
#define CANFTP_CLIENT_H_

#include "CanFTP_Client_Defines.h"

/*
    Инициализация клиента
*/
void CanFTP_Client_Init(CanFTP_Client_t *client);
/*
    Вызов логики обработки клиента
*/
void CanFTP_Client_Invoke(CanFTP_Client_t *client);
/*
    Обработка получения сообщений
*/
void CanFTP_Client_RecieveCanMessage(CanFTP_Client_t *client, CanFTP_CanMessage_t* canMessage);

#endif // CANFTP_CLIENT_H_