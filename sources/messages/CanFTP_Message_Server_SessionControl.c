/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Message_Server_SessionControl.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_SessionControl_Unpack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, CANFTP_MESSAGE_DLC_SERVER_SESSIONCONTROL))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Server_SessionControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {
            messageModel->configuration.partIndex = (CanFTP_Message_Client_SessionControl_ConfigurationPart_t)((messageCan->data[0] >> 4) & 0x0F);

            if (messageModel->configuration.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0)
            {
                messageModel->configuration.part0.firstPageIndex = (CanFTP_PageIndex_t)(
                    (CanFTP_PageIndex_t)((messageCan->data[1] >> 0) & 0xFF) << 0
                    | (CanFTP_PageIndex_t)((messageCan->data[2] >> 0) & 0x03) << 8
                );
                messageModel->configuration.part0.pagesCount = (CanFTP_PageIndex_t)(
                    (CanFTP_PageIndex_t)((messageCan->data[2] >> 2) & 0x3F) << 0
                    | (CanFTP_PageIndex_t)((messageCan->data[3] >> 0) & 0x0F) << 6
                );
                messageModel->configuration.part0.sessionRepeateCount = (CanFTP_SendingRepeate_t)(
                    (CanFTP_SendingRepeate_t)((messageCan->data[3] >> 4) & 0x0F) << 0
                    | (CanFTP_SendingRepeate_t)((messageCan->data[4] >> 0) & 0x0F) << 4
                );
                messageModel->configuration.part0.sessionRepeateInterval = (CanFTP_SendingRepeateInterval_t)(
                    (CanFTP_SendingRepeate_t)((messageCan->data[4] >> 4) & 0x0F) << 0
                    | (CanFTP_SendingRepeate_t)((messageCan->data[5] >> 0) & 0x3F) << 4
                );
                messageModel->configuration.part0.blockRepeateCount = (CanFTP_SendingRepeate_t)(
                    (CanFTP_SendingRepeate_t)((messageCan->data[5] >> 6) & 0x03) << 0
                    | (CanFTP_SendingRepeate_t)((messageCan->data[6] >> 0) & 0x3F) << 2
                );
                messageModel->configuration.part0.blockRepeateInterval = (CanFTP_SendingRepeateInterval_t)(
                    (CanFTP_SendingRepeate_t)((messageCan->data[6] >> 6) & 0x03) << 0
                    | (CanFTP_SendingRepeate_t)((messageCan->data[7] >> 0) & 0xFF) << 2
                );
            }
            else if (messageModel->configuration.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART1)
            {
                messageModel->configuration.part1.fileLength = (CanFTP_FileLength_t)(
                    (CanFTP_FileLength_t)((messageCan->data[1] >> 0) & 0xFF) << 0
                    | (CanFTP_FileLength_t)((messageCan->data[2] >> 0) & 0xFF) << 8
                    | (CanFTP_FileLength_t)((messageCan->data[3] >> 0) & 0xFF) << 16
                    | (CanFTP_FileLength_t)((messageCan->data[4] >> 0) & 0xFF) << 24
                );
                messageModel->configuration.part1.newSoftVersion.lowerPart = (CanFTP_DeviceSoftwareVersionPart_t)(messageCan->data[5]);
                messageModel->configuration.part1.newSoftVersion.middlePart = (CanFTP_DeviceSoftwareVersionPart_t)(messageCan->data[6]);
                messageModel->configuration.part1.newSoftVersion.higherPart = (CanFTP_DeviceSoftwareVersionPart_t)(messageCan->data[7]);
            }
            else
            {
                CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_CONFIGURATION_PARTINDEXOUTOFRANGE);
            }
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
        {
            messageModel->finish.sessionStatus = (CanFTP_SessionStatus_t)(
                  (CanFTP_SessionStatus_t)((messageCan->data[0] >> 4) & 0x0F) << 0
                | (CanFTP_SessionStatus_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT)
        {
            messageModel->deleteClient.sessionStatus = (CanFTP_SessionStatus_t)(
                  (CanFTP_SessionStatus_t)((messageCan->data[0] >> 4) & 0x0F) << 0
                | (CanFTP_SessionStatus_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
            messageModel->deleteClient.deviceCode = (CanFTP_DeviceCode_t)(
                  (CanFTP_DeviceCode_t)((messageCan->data[1] >> 4) & 0x0F) << 0
                | (CanFTP_DeviceCode_t)((messageCan->data[2] >> 0) & 0x0F) << 4
            );
        }
        else
        {
            CanFTP_ThrowErrorWithCode(CANFTP_ERROR_MESSAGES_WRONGTYPE);
        }

        return CANFTP_TRUE;
    }
    else
    {
        return CANFTP_FALSE;
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Pack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {
            messageDataVector[0] |= ((messageModel->configuration.partIndex & 0x0F) << 4);

            if (messageModel->configuration.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0)
            {
                CanFTP_SendingRepeate_t sessionRepeateCount = messageModel->configuration.part0.sessionRepeateCount > 0xFF 
                    ? 0xFF 
                    : messageModel->configuration.part0.sessionRepeateCount;
                CanFTP_SendingRepeateInterval_t sessionRepeateInterval = messageModel->configuration.part0.sessionRepeateInterval > 0x03FF 
                    ? 0x03FF 
                    : messageModel->configuration.part0.sessionRepeateInterval;
                CanFTP_SendingRepeate_t blockRepeateCount = messageModel->configuration.part0.blockRepeateCount > 0xFF 
                    ? 0xFF 
                    : messageModel->configuration.part0.blockRepeateCount;
                CanFTP_SendingRepeateInterval_t blockRepeateInterval = messageModel->configuration.part0.blockRepeateInterval > 0x03FF 
                    ? 0x03FF 
                    : messageModel->configuration.part0.blockRepeateInterval;

                messageDataVector[1] |= ((messageModel->configuration.part0.firstPageIndex >> 0) & 0xFF) << 0;
                messageDataVector[2] |= (((messageModel->configuration.part0.firstPageIndex >> 8) & 0x03) << 0) 
                                        | (((messageModel->configuration.part0.pagesCount >> 0) & 0x3F) << 2);
                messageDataVector[3] |= ((messageModel->configuration.part0.pagesCount >> 6) & 0x0F) << 0
                                        | ((sessionRepeateCount >> 0) & 0x0F) << 4;
                messageDataVector[4] |= ((sessionRepeateCount >> 4) & 0x0F) << 0
                                        | ((sessionRepeateInterval >> 0) & 0x0F) << 4;
                messageDataVector[5] |= ((sessionRepeateInterval >> 4) & 0x3F) << 0
                                        | ((blockRepeateCount >> 0) & 0x03) << 6;
                messageDataVector[6] |= ((blockRepeateCount >> 2) & 0x3F) << 0
                                        | (((blockRepeateInterval >> 0) & 0x03) << 6);
                messageDataVector[7] |= (((blockRepeateInterval >> 2) & 0xFF) << 0);
            }
            else if (messageModel->configuration.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART1)
            {
                messageDataVector[1] |= ((messageModel->configuration.part1.fileLength >> 0) & 0xFF) << 0;
                messageDataVector[2] |= ((messageModel->configuration.part1.fileLength >> 8) & 0xFF) << 0;
                messageDataVector[3] |= ((messageModel->configuration.part1.fileLength >> 16) & 0xFF) << 0;
                messageDataVector[4] |= ((messageModel->configuration.part1.fileLength >> 24) & 0xFF) << 0;
                messageDataVector[5] |= messageModel->configuration.part1.newSoftVersion.lowerPart & 0xFF;
                messageDataVector[6] |= messageModel->configuration.part1.newSoftVersion.middlePart & 0xFF;
                messageDataVector[7] |= messageModel->configuration.part1.newSoftVersion.higherPart & 0xFF;
            }
            else
            {
                CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_CONFIGURATION_PARTINDEXOUTOFRANGE);
            }
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
        {
            messageDataVector[0] |= ((messageModel->finish.sessionStatus >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->finish.sessionStatus >> 4) & 0x0F) << 0);
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT)
        {
            messageDataVector[0] |= ((messageModel->deleteClient.sessionStatus >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->deleteClient.sessionStatus >> 4) & 0x0F) << 0) 
                                    | (((messageModel->deleteClient.deviceCode >> 0) & 0x0F) << 4);
            messageDataVector[2] |= (((messageModel->deleteClient.deviceCode >> 4) & 0x0F) << 0);
        }
        else
        {
            CanFTP_ThrowErrorWithCode(CANFTP_ERROR_MESSAGES_WRONGTYPE);
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCode(CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, messageModel->sessionCode)
        , CANFTP_MESSAGE_DLC_SERVER_SESSIONCONTROL
        , messageDataVector
    );
}
