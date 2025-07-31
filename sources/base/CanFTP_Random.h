#ifndef CANFTP_RANDOM_H_
#define CANFTP_RANDOM_H_

#include "CanFTP_BaseTypes_Defines.h"

/*
    Структура генерации случайных последовательностей
*/
typedef struct _CanFTP_Random
{
    // Последнее случайное значение 
    uint32_t value;

} CanFTP_Random_t;

/*
    Проинициализировать генератор случайных значений
*/
void CanFTP_Random_Init(CanFTP_Random_t* random, uint32_t seed);
/*
    Получить следующее случайное значение
*/
uint32_t CanFTP_Random_GetNext(CanFTP_Random_t* random);
/*
    Получить слудеющее случайное значение в заданном диапазоне
*/
uint32_t CanFTP_Random_GetNext_Range(CanFTP_Random_t* random, uint32_t min, uint32_t max);

#endif // CANFTP_RANDOM_H_
