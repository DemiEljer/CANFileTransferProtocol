/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_LINKEDLIST_H_
#define CANFTP_LINKEDLIST_H_

#include "CanFTP_LinkedList_Defines.h"

/*
    Проинициализировать список
*/
void CanFTP_LinkedList_Init(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementSize_t elementSize);
/*
    Функция приведения дочерней структуры к структуре списка
*/
CanFTP_LinkedList_t* CanFTP_LinkedList_Cast(void* childList);
/*
    Добавить элемент списка в начало
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_AppendHead(CanFTP_LinkedList_t* list);
/*
    Добавить элемент списка в конец
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_AppendTail(CanFTP_LinkedList_t* list);
/*
    Добавить элемент списка в указанную позицию
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_Insert(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index);
/*
    Удалить элемент спсика в начале
*/
CanFTP_Logical_t CanFTP_LinkedList_RemoveHead(CanFTP_LinkedList_t* list);
/*
    Удалить элемент спсика в конце
*/
CanFTP_Logical_t CanFTP_LinkedList_RemoveTail(CanFTP_LinkedList_t* list);
/*
    Удалить элемент спсика по указанному индексу
*/
void CanFTP_LinkedList_RemoveAt(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index);
/*
    Удалить элемент спсика
*/
CanFTP_Logical_t CanFTP_LinkedList_Remove(CanFTP_LinkedList_t* list, CanFTP_LinkedList_Element_t* element);
/*
    Получить элемент списка по указанному индексу
*/
CanFTP_LinkedList_Element_t* CanFTP_LinkedList_GetAt(CanFTP_LinkedList_t* list, CanFTP_LinkedList_ElementsCount_t index);
/*
    Очистить список
*/
void CanFTP_LinkedList_Clear(CanFTP_LinkedList_t* list);
/*
    Преобразовать список в массив (необходимо ручное преобразование к целевому типу)
*/
uint8_t* CanFTP_LinkedList_GetArray(CanFTP_LinkedList_t* list);

#endif // CANFTP_LINKEDLIST_H_
