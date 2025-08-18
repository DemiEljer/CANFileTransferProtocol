# Описания сущностей прикладного уровня

> Под **функциональным API** подразумеваются функции, вызываемые из основной логики, **обратные вызовы** - функции, вызывающиеся из логики библиотеки как события (необходима их инициализация).

---
## CanFTP_Client_t

> Включение ```#include "CanFTP_Client.h"```

#### Функциональное API

> Для детального ознакомления см. файл **/source/client/CanFTP_Client.h**.

|Имя функции|Описание|
|-----------|--------|
|CanFTP_Client_Init|Инициализация клиента|
|CanFTP_Client_Invoke|Вызов логики обработки клиента|
|CanFTP_Client_RecieveCanMessage|Обработка получения сообщений|
|CanFTP_Client_InitRanmod|Проинициализировать функцию генерации случайных значений|
|CanFTP_Client_TerminateSession|Принудительно остановить сессию|
|CanFTP_Client_LockLogic|Заблокировать логику|
|CanFTP_Client_UnlockLogic|Разблокировать логику|
|CanFTP_Client_CheckIsPinging|Проверить, находится ли клиент в состоянии Ping|
|CanFTP_Client_CheckIsInSession|Проверить, находится ли клиент в соcтоянии активной сессии|

#### Обратные вызовы

> Связывание осуществляется с помощью композиционно включенной структуры callbacks: client.callbacks.

> Для детального ознакомления см. файл **/source/client/CanFTP_Client_Defines.h**.

|Имя обратного вызова|Описание|
|--------------------|--------|
|callbacks.sendMessageCallback|Обратный вызов отправки сообщений|
|callbacks.lockLogicRequestCallback|Обратный вызов запроса на блокировку логики (0 - не заблокирована, 1 - заблокирована)|
|callbacks.unlockLogicRequestCallback|Обратный вызов запроса на разблокировку логики (0 - не разблокирована, 1 - разблокирована)|
|callbacks.sessionConfigureationCallback|Обратный вызов конфигурации сессии (0 - сессия не прошла валидацию, 1 - сессия прошла валидацию)|
|callbacks.blockRecieceCallback|Обратный вызов успешного приема блока файла|
|callbacks.sessionFinishedCallback|Обратный вызов завершения сессии|

> **Примечание.** При отсуствии инициализации обратных вызовов **lockLogicRequestCallback**, **unlockLogicRequestCallback**, **sessionConfigureationCallback** они считаются по умолчанию успешными.

> **Примечание.** Обратный вызов **sessionConfigureationCallback** предполагает проверку возможности передачи файла заданного размера и подготовку устройства к приему файла.

#### Параметры управления и конфигурации

> Для детального ознакомления см. файл **/source/client/CanFTP_Client_Defines.h**.

|Имя параметра|Описание|
|-------------|--------|
|deviceConfig.serialNumber|Серийный номер устройства|
|deviceConfig.identifier|Идентификатор устройства|
|deviceConfig.type|Тип устройства|
|deviceConfig.softVersion.lowerPart|Младшая часть версии|
|deviceConfig.softVersion.middlePart|Средняя часть версии|
|deviceConfig.softVersion.higherPart|Страршая часть версии|
|control.pingPermition|Разрешенеи на переход в состояние Ping|
|control.sessionStartPermition|Разрешение на активацию сессии|
|control.autpUpdateSoftVersion|Автоматически обновить номер версии при успешном завершении сессии|

---
## CanFTP_Server_t

> Включение ```#include "CanFTP_Server.h"```

#### Функциональное API

> Для детального ознакомления см. файл **/source/server/CanFTP_Server.h**.

|Имя функции|Описание|
|-----------|--------|
|CanFTP_Server_Init|Инициализация сервера|
|CanFTP_Server_Invoke|Вызов логики обработки клиента|
|CanFTP_Server_RecieveCanMessage|Обработка получения сообщений|
|CanFTP_Server_StartPing|Запустить процесс Ping|
|CanFTP_Server_StartRelease|Запустить процесс разблокировки логик клиентов|
|CanFTP_Server_StopPing|Остановить процесс Ping|
|CanFTP_Server_GetClientsCount|Получить количество клиентов|
|CanFTP_Server_GetClientByIndex|Получить клиента по индексу|
|CanFTP_Server_CreateNewSession|Создать экземпляр сессии|
|CanFTP_Server_GetActiveSessionsCount|Получить количество активных сессий|
|CanFTP_Server_GetActiveSessionByIndex|Получить активную сессию по иднексу|

> **Примечание.** После начала поиска устройств (**CanFTP_Server_StartPing**) или их освобождения (**CanFTP_Server_StartRelease**) необходимо вызвать **CanFTP_Server_StopPing**, чтобы остановить процесс. 

> **Примечание.** Все обратные вызовы сессий и их клиентов, как и обработка получаемых сообщений, осуществляется через сервер. 

#### Обратные вызовы

> Связывание осуществляется с помощью композиционно включенной структуры callbacks: server.callbacks.

> Для детального ознакомления см. файл **/source/server/CanFTP_Server_Defines.h**.

|Имя обратного вызова|Описание|
|--------------------|--------|
|callbacks.sendMessageCallback|Обратный вызов отправки сообщений|
|callbacks.clientFoundCallback|Обратный вызов нахождения клиента|
|callbacks.sessionFinishedCallback|Обратный вызов события завершения сессии|
|callbacks.getFileBlockCallback|Обратный вызов запроса блока файла|
|callbacks.clientReleaseCallback|Обратный вызов особождения клиента из сессии|

#### Параметры управления и конфигурации

> Для детального ознакомления см. файл **/source/server/CanFTP_Server_Defines.h**.

|Имя параметра|Описание|
|-------------|--------|
|controls.doesServerInvokeSessions|Флаг управления вызовом сессий из сервера|
|defaultSessionConfiguration.registrationInterval|Интервалы времени отправки сообщений при регистрации клиентов|
|defaultSessionConfiguration.registrationRepeateCount|Количество повторений отправки сообщений при регистрации клиентов|
|defaultSessionConfiguration.sessionControlInterval|Интервалы времени отправки сообщений при управлении сессией|
|defaultSessionConfiguration.sessionControlRepeateCount|Количество повторений отправки сообщений при управлении сессей|
|defaultSessionConfiguration.repeateBlockCount|Количество повторений отправки блока|
|defaultSessionConfiguration.blockControlInterval|Интервалы времени отправки сообщений при управлении процессом отправки блока|
|defaultSessionConfiguration.blockControlRepeateCount|Количество повторений отправки сообщений при управлении процессом отправки блока|
|defaultSessionConfiguration.frameSendingInterval|Интервалы времени отправки кадров блока|
|defaultSessionConfiguration.repeateAckInterval|Интервалы времени отправки подтверждений со стороны клиента|
|defaultSessionConfiguration.repeateAckCount|Количество повторений отправки сообщений от клиентов|

---
## CanFTP_Server_Client_t

> Включение ```#include "CanFTP_Server.h"```

#### Функциональное API

> Для детального ознакомления см. файл **/source/server/CanFTP_Server_Client.h**.

|Имя функции|Описание|
|-----------|--------|
|CanFTP_Server_Client_IsConfigured|Проверить, что клиент сконфигурирован|
|CanFTP_Server_Client_IsInSession|Проверить, что клиент вовлечен в сессию|

### CanFTP_Server_Session_t

> Включение ```#include "CanFTP_Server.h"```

#### Функциональное API

> Для детального ознакомления см. файл **/source/session/CanFTP_Server_Session.h**.

|Имя функции|Описание|
|-----------|--------|
|CanFTP_Server_Session_Init|Проинициализировать сессию|
|CanFTP_Server_Session_Dispose|Удалить сессию|
|CanFTP_Server_Session_InitClients|Проинициализировать клиентов, участвующих в сессии|
|CanFTP_Server_Session_InitFileConfiguration|Проинициализировать параметры отправляемого файла|
|CanFTP_Server_Session_InitNewSoftVersion|Проинициализировать новую версию программного обеспечения|
|CanFTP_Server_Session_Invoke|Вызов логики сессии|
|CanFTP_Server_Session_Start|Запрос на запуск сессии|
|CanFTP_Server_Session_Stop|Запрос на остановку сессии|
|CanFTP_Server_Session_Delete|Запрос на удаление сессии|
|CanFTP_Server_Session_GetCompletingPercent|Получить процент завршения работы сессии|
|CanFTP_Server_Session_CheckIsActive|Проверить, находится ли сессия в активном состоянии|
|CanFTP_Server_Session_CheckCanBeDisposed|Проверить, что сессия может быть удалена|
|CanFTP_Server_Session_GetStatus|Получить статус сессии|
|CanFTP_Server_Session_GetClientsCount|Получить количество клиентов|
|CanFTP_Server_Session_GetActiveClientsCount|Получить количество активных клиентов|
|CanFTP_Server_Session_GetClientByIndex|Получить клиента по индексу|

> **Примечание.** Фактическое удаление сессии осуществляется из логики сервера. 

> **Примечание.** Перед запуском сессии необходимо вызвать функции **CanFTP_Server_Session_InitClients** и **CanFTP_Server_Session_InitFileConfiguration**.

> **Примечание.** При инициализации клиентов происходит поиск самой старшей версии среди них, и полученная версия по умолчанию становится новой. 

#### Параметры управления и конфигурации

> Для детального ознакомления см. файл **/source/session/CanFTP_Server_Session_Defines.h**.

|Имя параметра|Описание|
|-------------|--------|
|configuration.registrationInterval|Интервалы времени отправки сообщений при регистрации клиентов|
|configuration.registrationRepeateCount|Количество повторений отправки сообщений при регистрации клиентов|
|configuration.sessionControlInterval|Интервалы времени отправки сообщений при управлении сессией|
|configuration.sessionControlRepeateCount|Количество повторений отправки сообщений при управлении сессей|
|configuration.repeateBlockCount|Количество повторений отправки блока|
|configuration.blockControlInterval|Интервалы времени отправки сообщений при управлении процессом отправки блока|
|configuration.blockControlRepeateCount|Количество повторений отправки сообщений при управлении процессом отправки блока|
|configuration.frameSendingInterval|Интервалы времени отправки кадров блока|
|configuration.repeateAckInterval|Интервалы времени отправки подтверждений со стороны клиента|
|configuration.repeateAckCount|Количество повторений отправки сообщений от клиентов|
|fileConfiguration.pageIndex|Индекс страницы|
|fileConfiguration.fileLength|Длина файла|
|fileConfiguration.maxBlockLength|Максимальный длина блока|
|fileConfiguration.newSoftVersion.lowerPart|Младшая часть версии|
|fileConfiguration.newSoftVersion.middlePart|Средняя часть версии|
|fileConfiguration.newSoftVersion.higherPart|Страршая часть версии|

---
## CanFTP_Server_Session_Client_t

> Включение ```#include "CanFTP_Server.h"```

#### Функциональное API

> Для детального ознакомления см. файл **/source/session/CanFTP_Server_Session_Client.h**.

|Имя функции|Описание|
|-----------|--------|
|CanFTP_Server_Session_Client_Dispose|Удаление клиента|
|CanFTP_Server_Session_Client_GetSessionStatus|Получить статус сессии|
