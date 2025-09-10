/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Message_Client_SessionControl.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_SessionControl_Unpack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL, CANFTP_MESSAGE_DLC_CLIENT_SESSIONCONTROL))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Client_SessionControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {
            messageModel->registrationAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {
            messageModel->configurationAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
            messageModel->configurationAck.partIndex = (CanFTP_Message_Client_SessionControl_ConfigurationPart_t)(messageCan->data[1] & 0x0F);
            
            if (messageModel->configurationAck.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0)
            {
                // Ничего не делаем
            }
            else if (messageModel->configurationAck.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART1)
            {
                messageModel->configurationAck.part1.maxBlockLength = (CanFTP_BlockLength_t)
                (
                      (CanFTP_BlockLength_t)((messageCan->data[1] >> 4) & 0x0F) << 0
                    | (CanFTP_BlockLength_t)((messageCan->data[2] >> 0) & 0xFF) << 4
                );
            }
            else
            {
                CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_CONFIGURATION_PARTINDEXOUTOFRANGE);
            }
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {
            messageModel->startSessionAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {
            messageModel->finishSessionAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
            messageModel->finishSessionAck.sessionStatus = (CanFTP_SessionStatus_t)(messageCan->data[1]);
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
void CanFTP_Message_Client_SessionControl_Pack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {
            messageDataVector[0] |= ((messageModel->registrationAck.status >> 0) & 0x0F) << 4;
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {
            messageDataVector[0] |= ((messageModel->configurationAck.status >> 0) & 0x0F) << 4;
            messageDataVector[1] |= messageModel->configurationAck.partIndex & 0x0F;

            if (messageModel->configurationAck.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0)
            {
                // Ничего не делаем
            }
            else if (messageModel->configurationAck.partIndex == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART1)
            {
                messageDataVector[1] |= ((messageModel->configurationAck.part1.maxBlockLength >> 0) & 0x0F) << 4;
                messageDataVector[2] |= ((messageModel->configurationAck.part1.maxBlockLength >> 4) & 0xFF) << 0;
            }
            else
            {
                CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_CONFIGURATION_PARTINDEXOUTOFRANGE);
            }
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {
            messageDataVector[0] |= ((messageModel->startSessionAck.status >> 0) & 0x0F) << 4;
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {
            messageDataVector[0] |= ((messageModel->finishSessionAck.status >> 0) & 0x0F) << 4;
            messageDataVector[1] |= messageModel->finishSessionAck.sessionStatus & 0xFF;
        }
        else
        {
            CanFTP_ThrowErrorWithCode(CANFTP_ERROR_MESSAGES_WRONGTYPE);
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL, messageModel->sessionCode, messageModel->deviceCode)
        , CANFTP_MESSAGE_DLC_CLIENT_SESSIONCONTROL
        , messageDataVector
    );
}
