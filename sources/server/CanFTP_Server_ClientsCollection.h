#ifndef CANFTP_SERVER_CLIENTSCOLLECTION_H_
#define CANFTP_SERVER_CLIENTSCOLLECTION_H_

#include "CanFTP_Server_ClientsCollection_Defines.h"

/*
    Инициализация коллекции клиентов
*/
void CanFTP_Server_ClientsCollection_Init(CanFTP_Server_ClientsCollection_t* collection);
/*
    Получить количество клиентов
*/
CanFTP_LinkedList_ElementsCount_t CanFTP_Server_ClientsCollection_GetCount(CanFTP_Server_ClientsCollection_t* collection);
/*
    Добавить клиента в коллекцию
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_Append(CanFTP_Server_ClientsCollection_t* collection);
/*
    Очистить коллекцию клиентов
*/
void CanFTP_Server_ClientsCollection_Clear(CanFTP_Server_ClientsCollection_t* collection);
/*
    Получить клиента по индексу
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_GetAt(CanFTP_Server_ClientsCollection_t* collection, CanFTP_LinkedList_ElementsCount_t index);
/*
    Получить клиента по его серийному номеру
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_GetBySerial(CanFTP_Server_ClientsCollection_t* collection, CanFTP_DeviceSerial_t serial);
/*
    Верифицировать коллекцию на предмет инициализации всех клиентов
*/
void CanFTP_Server_ClientsCollection_Verify(CanFTP_Server_ClientsCollection_t* collection);

#endif // CANFTP_SERVER_CLIENTSCOLLECTION_H_
