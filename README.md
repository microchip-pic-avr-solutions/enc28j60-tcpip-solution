<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# ARCHIVED TCP/IP Lite solutions using ENC28J60

Please refer to the following links for updated solutions for PICs and AVRs:
- https://github.com/microchip-pic-avr-solutions/pic-tcpip-lite-enc28j60-solution
- https://github.com/microchip-pic-avr-solutions/avr-tcpip-lite-enc28j60-solution

# TCP/IP Lite solutions using ENC28J60

This repository provides MPLAB X IDE projects that can work out of the box. The solutions that are included in the repository include functionality for UDP, TCP Server and TCP Client Demos. Note that the TCP/IP Lite stack needs to be serviced every 1 second and the timer callback function needs to be set to 1 second.

---

## Related Documentation

More details can be found at the following links:
- [Microchip Ethernet Controllers](https://www.microchip.com/design-centers/ethernet/ethernet-devices/products/ethernet-controllers)
- [ENC28J60](https://www.microchip.com/wwwproducts/en/en022889)
- [Curiosity HPC Board](https://www.microchip.com/developmenttools/ProductDetails/dm164136)


## Software Used

- MPLAB® X IDE v5.40 or later [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 v2.20 or later [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- TCP/IP Lite Stack v3.0.0
- Ethernet Drivers Library v3.0.0
- TCPIP Demo GUI v2.0
- [Wireshark Tool](https://www.wireshark.org/)

## Hardware Used

- Curiosity High Pin Count (HPC) Development Board [(dm164136)](https://www.microchip.com/developmenttools/ProductDetails/dm164136)
- ETH Click by MikroE [(ETH Click)](https://www.mikroe.com/eth-click)
- [PIC18F26K42](https://www.microchip.com/wwwproducts/en/PIC18F26K42)

---

## UDP Solution

1. Open MPLABX IDE.
<br><img src="images/mplabIcon.png" alt="mplabIcon" width="75"/>
2. From the downloaded projects, open enc28j60-udp-solution.X.
3. Open Windows Command Prompt application on your PC. Type “ipconfig” to get the IP address of your PC.
<br><img src="images/enc28j60/udpSolution/ipconfig.png" alt="ipconfig"/>
4.	Sending UDP Packets: In udp_demo.c, under the function UDP_DEMO_Send ():
<br>
    - Modify the Destination IP address with PC’s IP address as noted in Step 3.
<br>
    - Destination Port (anything in the range of dynamic ports)
<br><img src="images/enc28j60/udpSolution/destinationPort.png" alt="destinationPort"/>
<br>
5.	Receiving UDP Packets: In Source Files\MCC generated files\ udpv4_port_handler_table.c, add the following code:
<br>
    - In UDP_CallBackTable, add the following code to perform UDP Receive:
<br><img src="images/enc28j60/udpSolution/udpReceive.png" alt="udpReceive"/>
<br>
6.	Click on Program Device to program the code to the device.
<br>
7. Launch Wireshark. From the Capture menu, click Options.
Select an Interface from the list to which your board and PC are connected, click Start for capturing packets.
<br>e.g.: Local Area Network
<br>
8. In Wireshark, set the filter field as bootp||arp||icmp.
<br><img src="images/enc28j60/udpSolution/wiresharkFilter.png" alt="wiresharkFilter"/>
9. In Wireshark, notice the DHCP packets handshake to get the device IP address.
<br><img src="images/enc28j60/udpSolution/wiresharkDHCPCapture.png" alt="wiresharkDHCPCapture"/>
10.	In Wireshark, double click on “Offer” packet. Expand “Dynamic Host Configuration Protocol” to get the device IP address.
<br><img src="images/enc28j60/udpSolution/DHCPPacket.png" alt="DHCPPacket"/>
11.	Open the Java application TCPIP_Demo.exe. Go to the UDP tab and assign the same port number as ‘DestPort’(65531). Click on ‘Listen’ button. Click “Allow Access” if warning occurs. Assign the IP Address of your board which is found from step 10(192.168.0.37). Click on ‘Claim’ button.
<br><img src="images/enc28j60/udpSolution/udpDemoGUI.png" alt="udpDemoGUI"/>
<br>
12.	In Wireshark, set the filter field as bootp||udp.port==65531.
<br>
13.	In Demo GUI, click on LED 1, 2, 3, 4 to light the LEDs D1, D2, D3, D4, respectively and observe the Wireshark capture. 
<br><img src="images/enc28j60/udpSolution/udpWiresharkPacket.png" alt="udpWiresharkPacket"/>
<br>
14.	In Demo GUI, type data(e.g.: “Hello World”) inside Send Data box and press the Send button and observe the Wireshark capture.
<br><img src="images/enc28j60/udpSolution/udpWiresharkSend.png" alt="udpWiresharkSend"/>
<br>
15.	On the Curiosity HPC Board, press the Switch S1 and observe the Wireshark capture.
<br><img src="images/enc28j60/udpSolution/udpWiresharkReceive.png" alt="udpWiresharkReceive"/>

---

## TCP Client Solution

1. Open MPLABX IDE.
<br><img src="images/mplabIcon.png" alt="mplabIcon" width="75"/>
2. From the downloaded projects, open enc28j60-tcp-client-solution.X.
3. Open Windows Command Prompt application on your PC. Type “ipconfig” to get the IP address of your PC.
<br><img src="images/enc28j60/tcpClientSolution/ipconfig.png" alt="ipconfig"/>
4.	Modify the server IP address with PC's IP address in tcp_client_demo.c under function call TCP_Client_Initialize:
<br><img src="images/enc28j60/tcpClientSolution/tcpClientInit.png" alt="tcpClientInit"/>
4.	Click on Program Device to program the code to the device.
5.	Open the Java application TCPIP_Demo.exe. Go to the TCP Server Demo tab and assign the port number as ‘65534’. Click on ‘Listen’ button. The status of the TCP Connection is printed inside the STATUS text box.
<br><img src="images/enc28j60/tcpClientSolution/tcpClientSolutionGUI.png" alt="tcpClientSolutionGUI"/>
<br>
Also in Wireshark, observe the TCP packets by setting the filter “tcp.port == 65534”.
<br><img src="images/enc28j60/tcpClientSolution/tcpClientWiresharkPacket.png" alt="tcpWiresharkPacket"/>
6.	After the connection is established:
<br>
    - Type text inside the Send text box and click on ‘Send’ button. The text sent is displayed inside the Sent/Received Data box.
<br><img src="images/enc28j60/tcpClientSolution/tcpClientSend.png" alt="tcpSend"/>
<br>
Also in Wireshark, observe the TCP packets by setting the filter “tcp.port == 65534”
<br><img src="images/enc28j60/tcpClientSolution/tcpClientWiresharkSend.png" alt="tcpWiresharkSend"/>
<br>
    - Click on the Led buttons {0, 1, 2, 3, 4}. This will toggle LEDs on board.
<br><img src="images/enc28j60/tcpClientSolution/tcpClientReceive.png" alt="tcpClientReceive"/>
<br>
Also in Wireshark, observe the TCP packets by setting the filter “tcp.port == 65534”
<br><img src="images/enc28j60/tcpClientSolution/tcpClientWiresharkReceive.png" alt="tcpClientWiresharkReceive"/>
7. Push ‘Disconnect’ button, to close the TCP Connection. A client disconnected message will appear on the STATUS text box.  

---

## TCP Server Solution

1. Open MPLABX IDE.
<br><img src="images/mplabIcon.png" alt="mplabIcon" width="75"/>
2. From the downloaded projects, open enc28j60-tcp-server-solution.X.
3.	Click on Program Device to program the code to the device.
4. Launch Wireshark. From the Capture menu, click Options.
Select an Interface from the list to which your board and PC are connected, click Start for capturing packets.
<br>e.g.: Local Area Network
<br>
5. In Wireshark, set the filter field as bootp||arp||icmp.
<br><img src="images/enc28j60/tcpServerSolution/wiresharkFilter.png" alt="wiresharkFilter"/>
6. In Wireshark, notice the DHCP packets handshake to get the device IP address.
<br><img src="images/enc28j60/tcpServerSolution/wiresharkDHCPCapture.png" alt="wiresharkDHCPCapture"/>
7.	In Wireshark, double click on “Offer” packet. Expand “Dynamic Host Configuration Protocol” to get the device IP address.
<br><img src="images/enc28j60/tcpServerSolution/DHCPPacket.png" alt="DHCPPacket"/>
8.	Open the Java application TCPIP_Demo.exe. Go to the TCP Client Demo tab, assign the board IP address as Server IP address in the GUI from step 7. Assign the port number as ‘7’. Click on ‘Connect’ button. The status of the TCP Connection is printed inside the STATUS text box.
<br><img src="images/enc28j60/tcpServerSolution/tcpServerDemoGUI.png" alt="tcpServerDemoGUI"/>
9.	After the connection is established:
<br>
    - Type text inside the Send text box and click on ‘Send’ button. The text sent is echoed and displayed inside the Sent/Received Data box.
<br><img src="images/enc28j60/tcpServerSolution/tcpServerSend.png" alt="tcpServerSend"/>
<br>
    - Also in Wireshark, observe the TCP packets by setting the filter “tcp.port == 7”
<br><img src="images/enc28j60/tcpServerSolution/tcpServerWiresharkSend.png" alt="tcpServerWiresharkSend"/>
<br>
10.	Push ‘Disconnect’ button, to close the TCP Connection. TCP server closing the connection message will appear on the STATUS text box.

---
