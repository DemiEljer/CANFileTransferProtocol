#ifndef CANFTP_SERVER_CLIENTSCOLLECTION_DEFINES_H_
#define CANFTP_SERVER_CLIENTSCOLLECTION_DEFINES_H_

#include "CanFTP_LinkedList.h"
#include "CanFTP_Server_Client.h"
#include "CanFTP_Server_Params.h"

/*
    Элемент коллекции
*/
typedef struct _CanFTP_Server_ClientsCollection_Element
{
    // Структура элемента списка
    CanFTP_LinkedList_Element_t listElement;
    // Структура клиента
    CanFTP_Server_Client_t client;

} CanFTP_Server_ClientsCollection_Element_t;
/*
    Структура коллекции клиентов (allias)
*/
typedef CanFTP_LinkedList_t CanFTP_Server_ClientsCollection_t;

#endif // CANFTP_SERVER_CLIENTSCOLLECTION_DEFINES_H_
