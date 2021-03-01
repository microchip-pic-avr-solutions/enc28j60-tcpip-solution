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

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/TCPIPLibrary/udpv4.h"
#include "mcc_generated_files/TCPIPLibrary/tcpip_config.h"
#include "mcc_generated_files/pin_manager.h"
#include "udp_demo.h"


static udpStart_t udpPacket;

typedef struct
{
    char command;
    char action;    
}udpDemoRecv_t;

void UDP_Demo_Recv(void)
{
    udpDemoRecv_t udpRecv;
    
   // Receive the UDP data
    /* 1. Read the UDP data   */
    UDP_ReadBlock(&udpRecv, sizeof(udpDemoRecv_t));
    
    if(udpRecv.command == 'C')
    {
        switch(udpRecv.action)
        {
            case '1':
                Toggle_Led1_LAT ^=1;
                break;
            case '2':
                Toggle_Led2_LAT ^=1;
                break;
            case '3':
                Toggle_Led3_LAT ^=1;
                break;
            case '4':
                Toggle_Led4_LAT ^=1;
                break;
            default:
                break;
        }
    }
}

void UDP_Demo_Initialize(void)
{
    //TODO[2] - Initialize the Destination IP address with your PC's IP address and Destination Port
    
    /* UDP Packet Initializations*/
    udpPacket.destinationAddress = MAKE_IPV4_ADDRESS(192,168,0,38);
    udpPacket.sourcePortNumber = 65533;
    
    udpPacket.destinationPortNumber = 65531;
    

 
}

/*** Application to send Potentiometer data using UDP protocol in multiples of 10 ***/

void UDP_Demo_Send (void)
{
    error_msg ret = ERROR;
    char text[] = "Hello World";
   
        /**************** Start UDP Packet ****************************
         * @Param1 - Destination Address
         * @Param2 - Source Port Number
         * @Param3 - Destination Port Number
         **********************************************************************/
    ret = UDP_Start(udpPacket.destinationAddress, udpPacket.sourcePortNumber, udpPacket.destinationPortNumber);
      
       
         /**************** Write UDP Packet ****************************
         * @Param1 - Data to write 
         ***********************************************************************/
       if(ret == SUCCESS)
       {
           
           UDP_WriteString(text);
         /**************** Send UDP Packet ****************************/
           UDP_Send();
             
       }        
    
}

int Button_Press(void)
{   
    static int8_t debounce = 100;
    static unsigned int buttonState = 0;
    static char buttonPressEnabled = 1;

    if(PORTBbits.RB4 == 0)
    {       
        if(buttonState < debounce)
        {
            buttonState++;
        }
        else if(buttonPressEnabled)
        {
            buttonPressEnabled = 0;
            return 1;
        }
    }
    else if(buttonState > 0 )
    {
        buttonState--;
    }
    else
    {
        buttonPressEnabled = 1;
    }
    return 0;
}
  

