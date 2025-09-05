/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_LinkedList.h"

/*
    Проинициализировать список
*/
void CanFTP_LinkedList_Init(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementSize_t elementSize)
{
    list->head = CANFTP_NULL;
    list->tail = CANFTP_NULL;
    list->elementsCount = 0;

    CanFTP_LinkedList_ElementSize_t minimumElementSize = sizeof(CanFTP_LinkedList_Element_t);
    // Ограничение размера элемента минимальныйм размером
    list->elementSize = minimumElementSize > elementSize ? minimumElementSize : elementSize;
}
/*
    Функция приведения дочерней структуры к структуре списка
*/
CanFTP_LinkedList_t* CanFTP_LinkedList_Cast(void* childList)
{
    return (CanFTP_LinkedList_t*)(childList);
}
/*
    Добавить элемент в начало списка 
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_AppendHead(CanFTP_LinkedList_t* list)
{
    CanFTP_LinkedList_Element_t* newElement = (CanFTP_LinkedList_Element_t*)malloc(list->elementSize);
    newElement->list = list;
    
    if (list->elementsCount == 0)
    {
        newElement->nextElement = CANFTP_NULL;
        newElement->prevElement = CANFTP_NULL;

        list->head = newElement;
        list->tail = newElement;
    }
    else
    {
        list->head->prevElement = newElement;
        newElement->nextElement = list->head;
        newElement->prevElement = CANFTP_NULL;

        list->head = newElement;
    }

    list->elementsCount++;

    return newElement;
}
/*
    Добавить элемент в конец списка 
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_AppendTail(CanFTP_LinkedList_t* list)
{
    CanFTP_LinkedList_Element_t* newElement = (CanFTP_LinkedList_Element_t*)malloc(list->elementSize);
    newElement->list = list;

    if (list->elementsCount == 0)
    {
        newElement->nextElement = CANFTP_NULL;
        newElement->prevElement = CANFTP_NULL;

        list->head = newElement;
        list->tail = newElement;
    }
    else
    {
        list->tail->nextElement = newElement;
        newElement->nextElement = CANFTP_NULL;
        newElement->prevElement = list->tail;

        list->tail = newElement;
    }

    list->elementsCount++;

    return newElement;
}
/*
    Добавить элемент списка в указанную позицию
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_Insert(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index)
{
    if (index == 0)
    {
        return CanFTP_LinkedList_AppendHead(list);
    }
    else if (index == list->elementsCount)
    {
        return CanFTP_LinkedList_AppendTail(list);
    }
    else if (list->elementsCount == 0)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_LIST_OUTOFEANGE);

        return CANFTP_NULL;
    }
    else
    {
        CanFTP_LinkedList_Element_t* insertingPositionElement = CanFTP_LinkedList_GetAt(list, index);

        if (insertingPositionElement != CANFTP_NULL)
        {
            CanFTP_LinkedList_Element_t* newElement = (CanFTP_LinkedList_Element_t*)malloc(list->elementSize);
            newElement->list = list;

            newElement->prevElement = insertingPositionElement->prevElement;
            newElement->nextElement = insertingPositionElement;
            insertingPositionElement->prevElement->nextElement = newElement;
            insertingPositionElement->prevElement = newElement;

            return newElement;
        } 
        else
        {
            return CANFTP_NULL;
        }
    }
}
/*
    Удалить элемент спсика в начале
*/
CanFTP_Logical_t CanFTP_LinkedList_RemoveHead(CanFTP_LinkedList_t* list)
{
    if (list->elementsCount > 0)
    {
        CanFTP_LinkedList_Remove(list, list->head);

        return CANFTP_TRUE;
    }
    else 
    {
        return CANFTP_FALSE;
    }
}
/*
    Удалить элемент спсика в конце
*/
CanFTP_Logical_t CanFTP_LinkedList_RemoveTail(CanFTP_LinkedList_t* list)
{
    if (list->elementsCount > 0)
    {
        CanFTP_LinkedList_Remove(list, list->tail);

        return CANFTP_TRUE;
    }
    else 
    {
        return CANFTP_FALSE;
    }
}
/*
    Удалить элемент спсика по указанному индексу
*/
void CanFTP_LinkedList_RemoveAt(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index)
{
    CanFTP_LinkedList_Element_t* deletingPtr = CanFTP_LinkedList_GetAt(list, index);

    CanFTP_LinkedList_Remove(list, deletingPtr);
}
/*
    Удалить элемент спсика
*/
CanFTP_Logical_t CanFTP_LinkedList_Remove(CanFTP_LinkedList_t* list, CanFTP_LinkedList_Element_t* element)
{
    if (element != CANFTP_NULL)
    {
        if (element->list != list)
        {
            CanFTP_ThrowErrorWithCode(CANFTP_ERROR_LIST_STRANGERELEMENT);

            return CANFTP_FALSE;
        }

        if (list->elementsCount == 1)
        {
            list->head = CANFTP_NULL;
            list->tail = CANFTP_NULL;

            free(element);
            list->elementsCount--;
        }
        else
        {
            if (element == list->head)
            {
                list->head = element->nextElement;
                list->head->prevElement = CANFTP_NULL;
            }
            else if (element == list->tail)
            {
                list->tail = element->prevElement;
                list->tail->nextElement = CANFTP_NULL;
            }
            else
            {
                element->nextElement->prevElement = element->prevElement;
                element->prevElement->nextElement = element->nextElement;
            }

            free(element);
            list->elementsCount--;
        }

        return CANFTP_TRUE;
    }
    else
    {
        return CANFTP_FALSE;
    }
}
/*
    Получить элемент списка по указанному индексу
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_GetAt(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index)
{
    if (index >= list->elementsCount)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_LIST_OUTOFEANGE);

        return CANFTP_NULL;
    }
    else
    {
        CanFTP_LinkedList_ElementsCount_t i = 0;

        CanFTP_LinkedList_Element_t* resultPtr = list->head;
        // Последовательный проход по списку
        for (i = 0; i < index; i++)
        {
            resultPtr = resultPtr->nextElement;
        }

        return resultPtr;
    }
}
/*
    Очистить список
*/
void CanFTP_LinkedList_Clear(CanFTP_LinkedList_t* list)
{
    CanFTP_LinkedList_Element_t* currentPtr = list->head;
    CanFTP_LinkedList_Element_t* removingPtr = currentPtr;
    // Последовательное удаление элементов
    while (currentPtr != CANFTP_NULL)
    {
        currentPtr = currentPtr->nextElement;
        free(removingPtr);
        removingPtr = currentPtr;
    }
    // Зануление базовых полей
    list->head = CANFTP_NULL;
    list->tail = CANFTP_NULL;
    list->elementsCount = 0;
}
/*
    Преобразовать список в массив (необходимо ручное преобразование к целевому типу)
*/
uint8_t* CanFTP_LinkedList_GetArray(CanFTP_LinkedList_t* list)
{
    if (list->elementsCount > 0)
    {
        uint8_t* resultArray = malloc(list->elementsCount * list->elementSize);

        CanFTP_LinkedList_ElementSize_t elementByteIndex = 0;
        CanFTP_LinkedList_ElementsCount_t elementIndex = 0;
        CanFTP_LinkedList_Element_t* currentElement = list->head;
        // Копирование содержимого списка в массив
        for (elementIndex = 0; elementIndex < list->elementsCount; elementIndex++)
        {
            for (elementByteIndex = 0; elementByteIndex < list->elementSize; elementByteIndex++)
            {
                resultArray[elementIndex * elementIndex + elementByteIndex] = ((uint8_t*)(currentElement))[elementByteIndex];
            }

            currentElement = currentElement->nextElement;
        }
    }
    else
    {
        return CANFTP_NULL;
    }
}
