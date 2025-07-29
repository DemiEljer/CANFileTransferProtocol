#include "CanFTP_CanMessage.h"

/*
    Инициализация сообщения
*/
void CanFTP_CanMessage_Init(CanFTP_CanMessage_t* message
    // Идентификатор сообщения 
    , uint32_t id
    // Длина вектора данных
    , uint8_t dataLength
    // Вектор данных
    , uint8_t* data
)
{
    message->id = id;
    message->dataLength = dataLength;
    // Копирование вектора данных
    {
        uint8_t i = 0;
        for (i = 0; i < message->dataLength; i++)
        {
            message->data[i] = data[i];
        }
    }    
}
