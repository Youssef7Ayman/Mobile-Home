/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : UART DRIVER   *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "UART_private.h"
# include "UART_config.h"
# include "UART_interface.h"



void UART_VidInit(void)
{
	u8 Local_u8UCSRCValue=0;
	/*Select UCSRC Register*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

	/*Select Character size 8-bit*/
	//CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);

	UCSRC=Local_u8UCSRCValue;

	/*Select Baud Rate in UBRRL Register*/
	UBRRL=BAUD_RATE;


	/*Enable the Reciever*/
	SET_BIT(UCSRB,UCSRB_RXEN);
	/*Enable the Transmiter*/
	SET_BIT(UCSRB,UCSRB_TXEN);

}


void UART_VidSendData(u8 Copy_u8Data)
{
	while (GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=Copy_u8Data;
}


u8 UART_u8RecieveData(void)
{
	while (GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}


void UART_VidSendString (u8 *pu8String)
{
	for (u8 i=0;pu8String[i]!='\0';i++)
	{
		UART_VidSendData(pu8String[i]);
	}

}

void UART_VidSendValue (u32 Copy_u32Value)
{
	static u8 OUT=0;

	if (Copy_u32Value==0 && OUT==0)
	{
		UART_VidSendData('0');
	}
	else if (Copy_u32Value!=0)
	{
		OUT=1;
		UART_VidSendValue(Copy_u32Value/10);
		UART_VidSendData((Copy_u32Value%10)+48);
	}

}

void UART_VidPuttyNewLine (void)
{
	UART_VidSendData('\n');
}




