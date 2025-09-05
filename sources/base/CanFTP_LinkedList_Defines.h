/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_LINKEDLIST_DEFINES_H_
#define CANFTP_LINKEDLIST_DEFINES_H_

#include "CanFTP_ErrorHandlers.h"
#include "stdlib.h"

// Структура списка
typedef struct _CanFTP_LinkedList CanFTP_LinkedList_t;
// Структура элемента списка
typedef struct _CanFTP_LinkedList_Element CanFTP_LinkedList_Element_t;
// Тип размера элемента списка
typedef uint32_t CanFTP_LinkedList_ElementSize_t;
// Тип количества элементов спика
typedef uint32_t CanFTP_LinkedList_ElementsCount_t;

/*
    Структура элемента списка
*/
typedef struct _CanFTP_LinkedList_Element
{
    // Предыдущий элемент списка
    CanFTP_LinkedList_Element_t* prevElement;
    // Следущий элемент списка
    CanFTP_LinkedList_Element_t* nextElement;
    // Указатель на список
    CanFTP_LinkedList_t* list;

} CanFTP_LinkedList_Element_t;

/*
    Структура списка
*/
typedef struct _CanFTP_LinkedList
{
    // Указатель на первый элемент
    CanFTP_LinkedList_Element_t* head;
    // Указатель на последний элемент
    CanFTP_LinkedList_Element_t* tail;
    // Размер элемента
    CanFTP_LinkedList_ElementSize_t elementSize;
    // Количество элементов в списке
    CanFTP_LinkedList_ElementsCount_t elementsCount;

} CanFTP_LinkedList_t;

#endif // CANFTP_LINKEDLIST_DEFINES_H_
