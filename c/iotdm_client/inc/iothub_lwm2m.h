// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_LWM2M_H
#define IOTHUB_LWM2M_H

#include "iothub_client.h"
#include "iothub_client_ll.h"

#include "threadapi.h"
#include "iot_logging.h"


typedef void *IOTHUB_CHANNEL_HANDLE;
typedef enum IOTHUB_TRANSPORT_TAG
{
    COAP_TCPIP = 0
} IOTHUB_TRANSPORT;


typedef void(*ON_DM_CONNECT_COMPLETE)(IOTHUB_CLIENT_RESULT result, void *context);


/** @brief      Creates a IoT DM client for communication with an existing
*               IoT DM Service using the specified connection string parameter.
*
*   @param      connectionString    Pointer to a character string representing a device connection.
*               transport           Connection type. Reserved for future use.
*
*   @return     A non-NULL @c IOTHUB_CHANNEL_HANDLE value that is used when
*               invoking other functions for IoT DM client and @c NULL on failure.
*/
extern IOTHUB_CHANNEL_HANDLE IoTHubClient_DM_Open(const char *connectionString, IOTHUB_TRANSPORT transport);


/**
*   @brief      Closes the connection for the given client and disposes of resources allocated
*               by the IoT DM client. This is a blocking call.
*
*   @param      iotDMClientHandle   The handle created by a call to the create function.
*/
extern void IoTHubClient_DM_Close(IOTHUB_CHANNEL_HANDLE iotDMClientHandle);

/**
*   @brief      Creates the default LWM2M objects provided in the SDK. Upon success,
*               the client can sepcify the starting default value for any or all
*               resources as appropriate.
*
*   @param      iotDMClientHandle   The handle created by a call to the create function.
*
*   @return     IOTHUB_CLIENT_OK upon success or an error code upon failure.
*/
extern IOTHUB_CLIENT_RESULT IoTHubClient_DM_CreateDefaultObjects(IOTHUB_CHANNEL_HANDLE iotDMClientHandle);


/** @brief      Starts the client and remain running. A high level function which makes use
*               of IoTHubClient_DM_Connect and IoTHubClient_DM_DoWork.
*
*   @param      iotDMClientHandle   The handle created by a call to the create function.
*
*   @return     IOTHUB_CLIENT_OK upon success or an error code upon failure.
*/
extern IOTHUB_CLIENT_RESULT IoTHubClient_DM_Start(IOTHUB_CHANNEL_HANDLE iotDMClientHandle);


/** @brief      Connects the client to the the IoT DM service represented in the iotDMClientHandle.
*
*   @param      iotDMClientHandle   The handle created by a call to the create function.
*               onComplete          The pointer to a function to be called when the connection is completed.
*               callbackContext     The pointer to a chunck of memory to be interpreted by the call back function.
*
*   @return     IOTHUB_CLIENT_OK upon success or an error code upon failure.
*/
extern IOTHUB_CLIENT_RESULT IoTHubClient_DM_Connect(IOTHUB_CHANNEL_HANDLE iotDMClientHandle, ON_DM_CONNECT_COMPLETE onComplete, void *callbackContext);


/** @brief      Performs one unit of work. One unit of work consists of serveral steps as follows:
*               - Accept and process any pending requests from the DM service.
*               - Evaluate and process any observe / notify attributes.
*
*   @param      iotDMClientHandle   The handle created by a call to the create function.
*
*   @return     true if work is succesfully completed.
*/
extern bool IoTHubClient_DM_DoWork(IOTHUB_CHANNEL_HANDLE iotDMClientHandle);

#endif /* IOTHUB_LWM2M_H */
