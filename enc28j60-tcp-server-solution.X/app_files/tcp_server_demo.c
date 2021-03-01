/*
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms,you may use this software and
 *  any derivatives exclusively with Microchip products.It is your responsibility
 *  to comply with third party license terms applicable to your use of third party
 *  software (including open source software) that may accompany Microchip software.
 *
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 *  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 *  PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 *  ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 *  THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/TCPIPLibrary/tcpv4.h"
#include "../mcc_generated_files/TCPIPLibrary/ipv4.h"
#include "../mcc_generated_files/TCPIPLibrary/tcpip_config.h"
#include "tcp_server_demo.h"

//Implement an echo server over TCP
void TCP_Demo_Echo_Server(void)
{
    // create the socket for the TCP Server
    static tcpTCB_t port7TCB;

    // create the TX and RX Server's buffers
    static uint8_t rxdataPort7[20];
    static uint8_t txdataPort7[20];

    uint16_t rxLen, txLen, i;
    socketState_t socket_state;

    socket_state = TCP_SocketPoll(&port7TCB);

    switch(socket_state)
    {
        case NOT_A_SOCKET:
            
        //Inserting and Initializing the socket
            TCP_SocketInit(&port7TCB);
            
            break;
        case SOCKET_CLOSED:
           
        // Configure the local port
            TCP_Bind(&port7TCB, 7);
           
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
            
            
        // Start the TCP server: Listen on port
            TCP_Listen(&port7TCB);
            
            break;
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can send another buffer
            if(TCP_SendDone(&port7TCB))
            {
                // check to see  if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if(rxLen > 0)
                {
                    rxLen = TCP_GetReceivedData(&port7TCB);

                    //simulate some buffer processing
                    for(i = 0; i < rxLen; i++)
                    {
                        txdataPort7[i] = rxdataPort7[i];
                    }

                    // reuse the RX buffer
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
                    txLen = rxLen;
                    //send data back to the source
                    TCP_Send(&port7TCB, txdataPort7, txLen);
                }
            }
            break;
        case SOCKET_CLOSING:
            TCP_SocketRemove(&port7TCB);
            break;
            
        default:
            // we should not end up here
            break;
    }
}
