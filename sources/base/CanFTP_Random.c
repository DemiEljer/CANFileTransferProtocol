/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Random.h"

/*
    Проинициализировать генератор случайных значений
*/
void CanFTP_Random_Init(CanFTP_Random_t* random, uint32_t seed)
{
    random->value = seed;
}
/*
    Получить следующее случайное значение
*/
uint32_t CanFTP_Random_GetNext(CanFTP_Random_t* random)
{
    random->value = (random->value + 1) * (random->value - 1) + (random->value ^ 0xFFFFFFFF);

    return random->value;
}
/*
    Получить слудеющее случайное значение в заданном диапазоне
*/
uint32_t CanFTP_Random_GetNext_Range(CanFTP_Random_t* random, uint32_t min, uint32_t max)
{
    uint32_t randomValue = CanFTP_Random_GetNext(random);

    return min + (randomValue % (max - min));
}
