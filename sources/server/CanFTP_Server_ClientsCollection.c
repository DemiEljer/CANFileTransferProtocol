/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_ClientsCollection.h"

/*
    Преобразовать обобщенный элемент списка в элемент списка клиентов
*/
static CanFTP_Server_ClientsCollection_Element_t* CanFTP_Server_ClientsCollection_CastElement(CanFTP_LinkedList_Element_t* element)
{
    return (CanFTP_Server_ClientsCollection_Element_t*)(element);
}

/*
    Инициализация коллекции клиентов
*/
void CanFTP_Server_ClientsCollection_Init(CanFTP_Server_ClientsCollection_t* collection)
{
    CanFTP_LinkedList_Init(CanFTP_LinkedList_Cast(collection), sizeof(CanFTP_Server_ClientsCollection_Element_t));
}
/*
    Получить количество клиентов
*/
CanFTP_LinkedList_ElementsCount_t CanFTP_Server_ClientsCollection_GetCount(CanFTP_Server_ClientsCollection_t* collection)
{
    return CanFTP_LinkedList_Cast(collection)->elementsCount;
}
/*
    Добавить клиента в коллекцию
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_Append(CanFTP_Server_ClientsCollection_t* collection)
{
    CanFTP_Server_ClientsCollection_Element_t* listElement = CanFTP_Server_ClientsCollection_CastElement(CanFTP_LinkedList_AppendTail(CanFTP_LinkedList_Cast(collection)));

    return &(listElement->client);
}
/*
    Очистить коллекцию клиентов
*/
void CanFTP_Server_ClientsCollection_Clear(CanFTP_Server_ClientsCollection_t* collection)
{
    CanFTP_LinkedList_Clear(CanFTP_LinkedList_Cast(collection));
}
/*
    Получить клиента по индексу
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_GetAt(CanFTP_Server_ClientsCollection_t* collection, CanFTP_LinkedList_ElementsCount_t index)
{
    // Проверка на граничное условие количества клиентов в коллекции
    if (CanFTP_Server_ClientsCollection_GetCount(collection) <= index)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENTSCOLLECTION_OUTOFRANGE);

        return CANFTP_NULL;
    }

    CanFTP_Server_ClientsCollection_Element_t* listElement = CanFTP_Server_ClientsCollection_CastElement(CanFTP_LinkedList_GetAt(CanFTP_LinkedList_Cast(collection), index));

    if (listElement != CANFTP_NULL)
    {
        return &(listElement->client);
    }
    else
    {
        return CANFTP_NULL;
    }
}
/*
    Получить клиента по его серийному номеру
*/
CanFTP_Server_Client_t* CanFTP_Server_ClientsCollection_GetBySerial(CanFTP_Server_ClientsCollection_t* collection, CanFTP_DeviceSerial_t serial)
{
    CanFTP_LinkedList_Element_t* currentElement = CanFTP_LinkedList_Cast(collection)->head;

    while (currentElement != CANFTP_NULL)
    {
        if (CanFTP_Server_ClientsCollection_CastElement(currentElement)->client.configuration.serialNumber == serial)
        {
            return &(CanFTP_Server_ClientsCollection_CastElement(currentElement)->client);
        }
        else
        {
            currentElement = currentElement->nextElement;
        }
    }

    return CANFTP_NULL;
}
/*
    Верифицировать коллекцию на предмет инициализации всех клиентов
*/
void CanFTP_Server_ClientsCollection_Verify(CanFTP_Server_ClientsCollection_t* collection)
{
    CanFTP_LinkedList_Element_t* currentElement = CanFTP_LinkedList_Cast(collection)->head;

    while (currentElement != CANFTP_NULL)
    {
        if (!CanFTP_Server_Client_IsConfigured(&(CanFTP_Server_ClientsCollection_CastElement(currentElement)->client)))
        {
            CanFTP_LinkedList_Remove(CanFTP_LinkedList_Cast(collection), currentElement);
        }

        currentElement = currentElement->nextElement;
    }
}
