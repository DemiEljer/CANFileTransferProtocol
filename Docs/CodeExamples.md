# Примеры кода

## Инициализация и обработка клиента

```C

// Обратный вызов отправки CAN-сообщений
void ClientTxCanMessageCallback(CanFTP_Client_t *client, CanFTP_CanMessage_t* message)
{
    printf("=== Client \"%u\" has sent message\r\n", client->deviceConfig.serialNumber);

    // Тут должен быть вызов какой-то логики отправки сообщения по CAN
}
// Обратный вызов запроса блокировки логики
CanFTP_Logical_t ClientLogicLockRequestCallback(CanFTP_Client_t *client)
{
    printf("=== Client \"%u\" logic lock has been requested\r\n", client->deviceConfig.serialNumber);

    // В случае успешной блокировки возвращается 1, в случае невозможности - 0
    return CANFTP_TRUE;
}
// Обратный вызов запроса разблокировки логики
CanFTP_Logical_t ClientLogicUnlockRequestCallback(CanFTP_Client_t *client)
{
    printf("=== Client \"%u\" logic unlock has been requested\r\n", client->deviceConfig.serialNumber);

    // В случае успешной разблокировки возвращается 1, в случае невозможности - 0
    return CANFTP_TRUE;
}
// Обратный вызов события конфигурации сессии передачи файла
CanFTP_Logical_t ClientSessionConfigurationRequestCallback(CanFTP_Client_t *client, CanFTP_Client_Session_Configuration_t* configuration)
{
    printf("=== Client \"%u\" session configuration has been requested\r\n", client->deviceConfig.serialNumber);

    printf("pageIndex : %u\r\n", configuration->pageIndex);
    printf("fileLength : %u\r\n", configuration->fileLength);
    printf("repeateAckCount : %u\r\n", configuration->repeateAckCount);
    printf("repeateBlockCount : %u\r\n", configuration->repeateBlockCount);
    printf("repeateInterval : %u\r\n", configuration->repeateInterval);

    // В случае успешной проверки конфигурации возвращается 1, в случае ошибки - 0
    return CANFTP_TRUE;
}
// Обратный вызов получения блока файла
CanFTP_Logical_t ClientSessionBlockRecievedCallback(CanFTP_Client_t *client, CanFTP_FileLength_t firstByteIndex, CanFTP_FileLength_t bytesCount, uint8_t* data)
{
    printf("=== Client \"%u\" session block has been recieved\r\n", client->deviceConfig.serialNumber);

    printf("start : %u\r\n", firstByteIndex);
    printf("count : %u\r\n", bytesCount);

    // Тут происходит перенос блока в файла в место его постоянного хранения
}
// Обратный вызов окончания сессии
CanFTP_Logical_t ClientSessionHasBeenFinishedCallback(CanFTP_Client_t *client, CanFTP_SessionStatus_t status, CanFTP_SoftwareVersion_t* version)
{
    printf("=== Client \"%u\" session has been finished\r\n", client->deviceConfig.serialNumber);

    printf("status : %u\r\n", status);
    printf("version.low : %u\r\n", version->lowerPart);
    printf("version.mid : %u\r\n", version->middlePart);
    printf("version.high : %u\r\n", version->higherPart);
}

/*
    Также должен быть обработчик приема CAN-сообщений из внешей среды
    с вызовом функции CanFTP_Client_RecieveCanMessage
*/

CanFTP_Client_t client;

CanFTP_Client_Init(&(client));
// Инициализация обратных вызовов
client.callbacks.sendMessageCallback = ClientTxCanMessageCallback;
client.callbacks.blockRecieceCallback = ClientSessionBlockRecievedCallback;
client.callbacks.lockLogicRequestCallback = ClientLogicLockRequestCallback;
client.callbacks.sessionConfigureationCallback = ClientSessionConfigurationRequestCallback;
client.callbacks.unlockLogicRequestCallback = ClientLogicUnlockRequestCallback;
client.callbacks.sessionFinishedCallback = ClientSessionHasBeenFinishedCallback;
// Разрешение на переход устройства в состояние Ping
client.control.pingPermition = CANFTP_TRUE;
// Разрешение на переход устройства в состояние активной сессии
client.control.sessionStartPermition = CANFTP_TRUE;
// Инициализация серийного комера
client.deviceConfig.serialNumber = 20;
// Инициализация идентификатора устройства
client.deviceConfig.identifier = 30;
// Инициализация типа устройства
client.deviceConfig.type = 500;
// Инициализация текущей версии программного обеспечения
client.deviceConfig.softVersion.lowerPart = 11;
client.deviceConfig.softVersion.middlePart = 12;
client.deviceConfig.softVersion.higherPart = 13;

while (CANFTP_TRUE)
{
    CanFTP_Client_Invoke(&(client));
}

```

## Инициализация и обработка сервера

```C

// Длина передаваемого файла
#define FILE_LENGTH 50000
// Содержимое файла
uint8_t file[FILE_LENGTH];
// Обратный вызов отправки CAN-сообщений
void ServerTxCanMessageCallback(CanFTP_Server_t *server, CanFTP_CanMessage_t* message)
{
    printf("=== Serever has sent message\r\n");

    // Тут должен быть вызов какой-то логики отправки сообщения по CAN
}
// Обратный вызов обнаружения клиента
void ClientFoundCallback(CanFTP_Server_t *server, CanFTP_Server_Client_t *client)
{
    printf("=== Client was found\r\n");
    printf("Device serial: %u\r\n", client->configuration.serialNumber);
    printf("Device identifier: %u\r\n", client->configuration.identifier);
    printf("Device type: %u\r\n", client->configuration.type);
    printf("Device software version low: %u\r\n", client->configuration.softVersion.lowerPart);
    printf("Device software version middle: %u\r\n", client->configuration.softVersion.middlePart);
    printf("Device software version high: %u\r\n", client->configuration.softVersion.higherPart);
}
// Обратный вызов события завершения сессии передачи файла
void SessionHasFinishedCallback(CanFTP_Server_t *server, CanFTP_Server_Session_t* session, CanFTP_SessionStatus_t status, CanFTP_DeviceCode_t clientsCount)
{
    printf("=== Session \"%u\" has finished :: %u [%u]\r\n", session->code, status, clientsCount);
}
// Обратный вызов освобождения клиента из сессии
void ClientHasBeenReleasedCallback(CanFTP_Server_t *server, CanFTP_Server_Session_t* session, CanFTP_Server_Client_t* client, CanFTP_SessionStatus_t status)
{
    printf("=== Client \"%u\" has been released from session \"%u\" :: %u\r\n", client->configuration.serialNumber, session->code, status);
}
// Обратный вызов инциализации нового блока файла
void InitFileBlockCallback(CanFTP_Server_t *server, CanFTP_Server_Session_t* session, CanFTP_Session_FileBlock_t* block, CanFTP_FileLength_t firstByteIndex, CanFTP_FileLength_t bytesCount)
{
    printf("=== Server session block has been requested be session \"%u\"\r\n", session->code);

    CanFTP_Session_FileBlock_MoveBlockData(block, (uint8_t*)(file + firstByteIndex));
}

/*
    Также должен быть обработчик приема CAN-сообщений из внешей среды
    с вызовом функции CanFTP_Server_RecieveCanMessage
*/

CanFTP_Server_t server;

CanFTP_Server_Init(&(server));
// Выставление флага управления, что сессии вызываются из логики сервера
server.controls.doesServerInvokeSessions = CANFTP_TRUE;
// Инициализация обратный вызовов
server.callbacks.sendMessageCallback = ServerTxCanMessageCallback;
server.callbacks.clientFoundCallback = ClientFoundCallback;
server.callbacks.clientReleaseCallback = ClientHasBeenReleasedEvent;
server.callbacks.getFileBlockCallback = InitFileBlock;
server.callbacks.sessionFinishedCallback = SessionHasFinishedEvent;

while (CANFTP_TRUE)
{
    CanFTP_Server_Invoke(&(server));
}

```

## Поиск устройств

```C

// Начало поиска
CanFTP_Server_StartPing(&(server), CANFTP_TRUE);
// Ожидание нахождения устройств
//------------------------------
//------------------------------
//------------------------------
// Остановка поиска
CanFTP_Server_StopPing(&(server));

```

### Запуск сессии

```C

// Создание экземпляра сессии
CanFTP_Server_Session_t* session = CanFTP_Server_CreateNewSession(&(server));
// Инициализация массива клиентов сессии
CanFTP_Server_Client_t* sessionClients1[] = 
{
    CanFTP_Server_GetClientByIndex(&(server), 0)
    , CanFTP_Server_GetClientByIndex(&(server), 1)
    , CanFTP_Server_GetClientByIndex(&(server), 3)
    , CanFTP_Server_GetClientByIndex(&(server), 5)
    , CanFTP_Server_GetClientByIndex(&(server), 6)
    , CanFTP_Server_GetClientByIndex(&(server), 9)
};
// Инициализация клиентов
CanFTP_Server_Session_InitClients(session, 6, sessionClients1);
// Инициализация передаваемого файла
CanFTP_Server_Session_InitFileConfiguration(session, 0, FILE_LENGTH);
// Инициализация новой версии программного обеспечения
session->fileConfiguration.newSoftVersion.lowerPart = 25;
session->fileConfiguration.newSoftVersion.middlePart = 26;
session->fileConfiguration.newSoftVersion.higherPart = 27;
// Запус сессии
CanFTP_Server_Session_Start(session);

```

## Остановка всех сессий

```C

// Начало освобождения клиентов
CanFTP_Server_StartRelease(&(server));
// Ожидание, что все активные сессии будут закончены
while (CanFTP_Server_GetActiveSessionsCount(&(server)) > 0)
{
    CanFTP_Server_Invoke(&(server));
}
// Остановка процесса освобождения клиентов
CanFTP_Server_StopPing(&(server));

```
