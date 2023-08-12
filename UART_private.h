/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : UART DRIVER   *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# ifndef UART_PRIVATE_H
# define UART_PRIVATE_H


#define UCSRA           		 *((volatile u8*)0x2B)		/*USART Control and Status Register A*/
#define UCSRA_RXC 							7				//USART Receive Complete
#define UCSRA_TXC 							6				//USART Transmit Complete
#define UCSRA_UDRE 							5               //USART Data Register Empty
#define UCSRA_FE							4               //Frame Error
#define UCSRA_DOR							3               //Data OverRun
#define UCSRA_PE 							2               //Parity Error
#define UCSRA_U2X							1               //Double the USART Transmission Speed
#define UCSRA_MPCM							0				//Multi-processor Communication Mode

#define UCSRB           		 *((volatile u8*)0x2A)		/*USART Control and Status Register B*/
#define UCSRB_RXCIE 						7				//RX Complete Interrupt Enable
#define UCSRB_TXCIE 						6				//TX Complete Interrupt Enable
#define UCSRB_UDRIE							5	            //USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN							4	            //Receiver Enable
#define UCSRB_TXEN							3	            //Transmitter Enable
#define UCSRB_UCSZ2 						2	            //Character Size
#define UCSRB_RXB8							1               //Receive Data Bit 8
#define UCSRB_TXB8							0				//Transmit Data Bit 8

#define UCSRC           		 *((volatile u8*)0x20)		/*USART Control and Status Register B*/
#define UCSRC_URSEL						7					//Register Select
#define UCSRC_UMSEL						6					//USART Mode Select
#define UCSRC_UPM1						5	            	//Parity Mode
#define UCSRC_UPM0						4	            	//Parity Mode
#define UCSRC_USBS						3	            	//Stop Bit Select
#define UCSRC_UCSZ1						2	            	//Character Size
#define UCSRC_UCSZ0						1               	//Character Size
#define UCSRC_UCPOL						0					//Clock Polarity

#define UBRRL           		 *((volatile u8*)0x29)		/*USART Baud Rate Register Low Byte*/
#define UBRRH           		 *((volatile u8*)0x40)		/*USART Baud Rate Register High Byte*/
#define UDR           		 	 *((volatile u8*)0x2C)		/*USART I/O Data Register for transmitting or recieving data*/


#define BAUD_RATE_2400				207
#define BAUD_RATE_4800				103
#define BAUD_RATE_9600				51
#define BAUD_RATE_14_POINT_4K		34
#define BAUD_RATE_19_POINT_2K		25
#define BAUD_RATE_28_POINT_8K		16
#define BAUD_RATE_38_POINT_4K		12
#define BAUD_RATE_57_POINT_6K		8
#define BAUD_RATE_76_POINT_8K		6
#define BAUD_RATE_115_POINT_2K		3
#define BAUD_RATE_230_POINT_4K		1
#define BAUD_RATE_250K				1
#define BAUD_RATE_0_POINT_5M		0
#define BAUD_RATE_1M				-




#endif

