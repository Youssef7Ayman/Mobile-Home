/*
 * main.c
 *
 *  Created on: Sep 24, 2022
 *      Author: hp
 */
# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "TIMER_interface.h"
# include "UART_interface.h"
# include <util/delay.h>

# define USERS_SIZE          10
# define DIGITS_SIZE         20
# define NO					  0
# define YES				  1

/************************  Declaration for the called Functions  ************************/
void CLRInputDataArray     (u8 *Copy_Array);
void DisplayInputDataArray (u8 *Copy_Array);
void DisplayMenu   (void);
void CheckName     (void);
void CheckPassword (void);
/*************************************  Struct and its created object (Array of struct)  *************************************/
typedef struct NODE
{
	u8 name      [DIGITS_SIZE];
	u8 password  [DIGITS_SIZE];

}User_node;
User_node Arr[USERS_SIZE]={{"Youssef             ","123                 "} ,  //1
	                       {"Waleed              ","059753804           "} ,  //2
	                       {"Salma               ","789                 "} ,  //3
	                       {"Mostafa             ","147                 "} ,  //4
	                       {"Mina                ","258                 "} ,  //5
	                       {"Amr                 ","369                 "} ,  //6
	                       {"Nada                ","951                 "} ,  //7
	                       {"Ayman               ","75310398            "} ,  //8
	                       {"Kareem              ","109                 "} ,  //9
	                       {"Mai                 ","734                 "}};  //10
/****************************************************************  Global variables & Global Arrays  ********************************************************/
u8 Gloal_u8Location='0';			//Store the Row no. of the Users Arrary (if CheckName() is correct)
u8 Gloal_u8DigitCounts=0;		    //Store no. of entered digits for both Name & Password (After Name is correct it will be Cleared to be used for Password)
u8 Gloal_u8PasswordAcceptance;		//Determine the ability of person to open the Door (if the Entered Password is correct[YES])
u8 NAME[DIGITS_SIZE]    ={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};   //Store the input digit for the Name
u8 PASSWORD[DIGITS_SIZE]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};   //Store the input digit for the Password


/****************************************************************  Main [Start] *****************************************************************************/
int main ()
{
	/*-------------------------------------------  Setting the Directions of the DIO Pins  ----------------------------------------------------------------*/
	/*----------------------------------------------------------LCD--------------------------------------------------------------------------------*/
	DIO_VidSetPortDirection(Port_A,0b11100000); // LCD CMD Pins  : Port_A {7,6,5--->OutPut} RS,RW,E respectively only
	DIO_VidSetPortDirection(Port_C,0b11111111); // LCD DATA Pins : Port_C {7,6,5,4,3,2,1,0--->OutPut}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	/*---------------------------------------------------------UART--------------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_D,Pin0,Input);  //UART RX pin in Controller -------------------> Bluetooth Tx pin
	DIO_VidSetPinDirection(Port_D,Pin1,Output);	//UART TX pin in Controller -------------------> Bluetooth Rx pin
	/*---------------------------------------------------------TIMER--------------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_D,Pin5,Output); //PWM Pin in Controller [PD5] ------------> Upper SERVO pin
	//---------------------------------------------------------------------------------------------------------------------------------------------
	DIO_VidSetPinDirection(Port_A,Pin0,Output);	// PA0 ---------------> Base (Middle pin of the Transistor) for Solenoid Activation
	DIO_VidSetPinDirection(Port_A,Pin1,Output);	// PA1 ---------------> Left Yellow LED (Solenoid lamp)
	DIO_VidSetPinDirection(Port_A,Pin2,Output);	// PA2 ---------------> Left pin of Buzzer (Make Sound)
	DIO_VidSetPinDirection(Port_A,Pin3,Output);	// PA3 ---------------> Left Red LED (Buzzer lamp)
	//---------------------------------------------------------------------------------------------------------------------------------------------
	DIO_VidSetPortDirection(Port_B,0b11111111);	// Room Lamps : {Green LEDs--->PB3&PB2}  {Yellow LEDs--->PB4&PB5}  {Red LEDs--->PB6&PB7}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	LCD_VidInit();
	LCD_VidDisplayClear();

	UART_VidInit();

	TIMER1_VidFPWMInit();
	Timer1_VidSetAngle(90);       //Make the Door at Locked position (SERVO at 90 degree)
	/*--------------  Local variabled & Local Arrays Used in Main Function   -------------------------------------------------------*/
	u8 Local_u8ReceivedLetter=0,Local_u8ReceivedNumber=0,Local_u8Enter=0;
	u8 Local_u8Index;
	u8 Flag1=0,Flag2=0,TRY=0,i;
	//NOTE : the Bluetooth Module Send unknown extra elements, So we use the Alphabetic Arrays to check that each letter is alphabetic one and each no. is from 1->9
	u8 ALPHA1[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	u8 ALPHA2[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	u8 Number[10]={'0','1','2','3','4','5','6','7','8','9'};
	/*----------------------------------------------------------  While Loop (start)  --------------------------------------------------------*/
	while (1)
	{
		if (Flag1==0)
		{
			LCD_VidSendString("For Entry :-");
			LCD_VidGotoXY(1,0);
			LCD_VidSendString("Name : ");
			LCD_VidGotoXY(1,6);

			UART_VidPuttyNewLine();
			UART_VidSendString(" For Entry :-");
			UART_VidPuttyNewLine();
			UART_VidSendString("----------------");
			UART_VidPuttyNewLine();

			UART_VidPuttyNewLine();
			UART_VidSendString("Name :- ");
			UART_VidPuttyNewLine();

			Flag1=1;          					  //Used to Print the previous lines for one time only
		}
		/*---------------------  Receiving the Input Letters (start)  --------------------------------------------------------*/
		while (1)
		{
			Local_u8ReceivedLetter=UART_u8RecieveData();
			UART_VidSendData(Local_u8ReceivedLetter);
			if(Local_u8ReceivedLetter==' ')
			{
				UART_VidPuttyNewLine();
				break;
			}
			else
			{
				for (Local_u8Index=0 ; Local_u8Index<26 ; Local_u8Index++)  // 26 is the size of the AlPHA1,ALPHA2 Arrays
				{
					if (Local_u8ReceivedLetter==ALPHA1[Local_u8Index] || Local_u8ReceivedLetter==ALPHA2[Local_u8Index])
					{
						NAME[Gloal_u8DigitCounts]=Local_u8ReceivedLetter;
						Gloal_u8DigitCounts++;
						break;
					}
				}
			}

		}
		/*---------------------  Receiving the Input Letters (end)  --------------------------------------------------------*/
		DisplayInputDataArray (NAME);   	// Clearing NAME Array
		_delay_ms(1000);

		CheckName ();						// Check if the entered Name match any Name of the Users or Not and Clear the NAME Array for further Operartion
		u8 Local_u8DigitCounts=Gloal_u8DigitCounts;		    //Store no. of entered digits for both Name

		Gloal_u8DigitCounts=0;				// Returning to its zero initial value to be used again for PASSWORD Array
		/*---------------------  After accepting the Name, Check the Password (start)  --------------------------------------------------------*/
		if (Gloal_u8Location!='0')
		{
			while (1)
			{
				if (Flag2==0)
				{
					LCD_VidDisplayClear();
					LCD_VidSendString("For Entry :-");
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("Pass. : ");
					LCD_VidGotoXY(1,7);

					UART_VidSendString("--------------------------------");
					UART_VidPuttyNewLine();
					UART_VidSendString("Password :-");

					TRY=0;
					Flag2=1;
				}
				/*---------------------  Receiving the Input Numbers (start)  --------------------------------------------------------*/
				while (1)
				{
					Local_u8ReceivedNumber=UART_u8RecieveData();
					UART_VidSendData(Local_u8ReceivedNumber);

					if(Local_u8ReceivedNumber==' ')
					{
						UART_VidPuttyNewLine();
						break;
					}
					else
					{
						for (Local_u8Index=0 ; Local_u8Index<10 ; Local_u8Index++)    // 10 is the size of the Number Array
						{
							if (Local_u8ReceivedNumber==Number[Local_u8Index])
							{
								PASSWORD[Gloal_u8DigitCounts]=Local_u8ReceivedNumber;
								Gloal_u8DigitCounts++;
								break;
							}
						}
					}
				}
				/*---------------------  Receiving the Input Numbers (start)  --------------------------------------------------------*/
				DisplayInputDataArray (PASSWORD); // Clearing PASSWORD Array
				_delay_ms(1000);

				CheckPassword ();				  // Check if the entered Password match any Password of the UserName or Not and Clear the PASSWORD Array for further Operartion
				//NOTE : If the Processor reaches here, it means that the user has entered the correct Name & Password
				/*---------------------  The User Has entered the correct Password  --------------------------------------------------------*/
				if (Gloal_u8PasswordAcceptance==YES)
				{
					LCD_VidDisplayClear();
					LCD_VidSendString("Welcome ");

					UART_VidSendString("--------------------------------");
					UART_VidPuttyNewLine();
					UART_VidSendString("Welcome ");
					for (i=0;i<Local_u8DigitCounts;i++)
					{
						LCD_VidSendData(Arr[Gloal_u8Location].name[i]);
						UART_VidSendData(Arr[Gloal_u8Location].name[i]);
					}
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("Door Will Open !");
					_delay_ms(1000);

					UART_VidSendString(" , The Door Will Open Now !");
					UART_VidPuttyNewLine();
					UART_VidSendString("*********************************");

					DIO_VidSetPinValue(Port_A,Pin0,PinHigh);		//Solenoid is On
					DIO_VidSetPinValue(Port_A,Pin1,PinHigh);		//Left Yellow Led is On

					LCD_VidDisplayClear();
					LCD_VidSendString("Press->L to Lock");			//After the user has closed the Door to ensure that it is completely Locked
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("Door at closing");

					UART_VidPuttyNewLine();
					UART_VidSendString("To Lock the Door Press ---> [ L ]");
					/*---------------------  Waiting for the User Door Locking Response  --------------------------------------------------------*/
					while (1)
					{
						u8 press=UART_u8RecieveData();
						if (press=='L')
						{
							DIO_VidSetPinValue(Port_A,Pin0,PinLow);
							DIO_VidSetPinValue(Port_A,Pin1,PinLow);

							LCD_VidDisplayClear();
							LCD_VidSendString("   Enjoy your  ");
							LCD_VidGotoXY(1,0);
							LCD_VidSendString("    Home !");
							Gloal_u8DigitCounts=0;
							break;
						}
					}
					Local_u8Enter=1;		// the user is ready to control his home
					break;
				}
				/*-------------------------------------------  The User Locked the Door  --------------------------------------------------------*/
				/*---------------------  The User Has entered  incorrect Password & still has Tries  --------------------------------------------------------*/
				else if (TRY<2)
				{
					Gloal_u8DigitCounts=0;
					for (i=0;i<4;i++)
					{
						DIO_VidSetPinValue(Port_A,Pin2,PinHigh);
						DIO_VidSetPinValue(Port_A,Pin3,PinHigh);
						_delay_ms(50);
						DIO_VidSetPinValue(Port_A,Pin2,PinLow);
						DIO_VidSetPinValue(Port_A,Pin3,PinLow);
						_delay_ms(50);
					}
					LCD_VidDisplayClear();
					LCD_VidSendString("Incorrect Pass.!");
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("Try[");
					LCD_VidSendValue(TRY+2);
					LCD_VidSendString("]:");
					LCD_VidGotoXY(1,7);

					UART_VidSendString("Incorrect Password ! , Try[");
					UART_VidSendValue(TRY+2);
					UART_VidSendString("] :-");
					TRY++;            //Reduce the User No. of Tries
				}
				/*---------------------  The User Has entered  incorrect Password & has no more Tries  --------------------------------------------------------*/
				else
				{
					LCD_VidDisplayClear();
					LCD_VidSendString("    InCorrect");
					LCD_VidGotoXY(1,4);
					LCD_VidSendString("Password!");
					_delay_ms(1000);
					LCD_VidDisplayClear();
					LCD_VidSendString("3 times wrong");
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("Passwords !");
					_delay_ms(1000);
					LCD_VidDisplayClear();
					LCD_VidSendString("No More Tries!!");
					LCD_VidGotoXY(1,0);
					LCD_VidSendString("***************");

					UART_VidSendString("*************************************");

					UART_VidPuttyNewLine();
					UART_VidSendString("Password Incorrect for 3 Times");
					UART_VidPuttyNewLine();
					UART_VidSendString("        SORRY NO MORE TRIES !");
					UART_VidPuttyNewLine();
					UART_VidSendString("*************************************");
					while (1)
					{
						DIO_VidSetPinValue(Port_A,Pin2,PinHigh);
						DIO_VidSetPinValue(Port_A,Pin3,PinHigh);
						_delay_ms(80);
						DIO_VidSetPinValue(Port_A,Pin2,PinLow);
						DIO_VidSetPinValue(Port_A,Pin3,PinLow);
						_delay_ms(80);
						//the Processor will stucked in this loop forever, Someone try to steal the house
					}
					break;
				}

			}
		}
		/*---------------------  After accepting the Name, Check the Password (end)  --------------------------------------------------------*/
		/*---------------------  Refusing the entered Name and make a new entering Chance (start)  ------------------------------------------*/
		else
		{
			for (i=0;i<4;i++)
			{
				DIO_VidSetPinValue(Port_A,Pin2,PinHigh);
				DIO_VidSetPinValue(Port_A,Pin3,PinHigh);
				_delay_ms(50);
				DIO_VidSetPinValue(Port_A,Pin2,PinLow);
				DIO_VidSetPinValue(Port_A,Pin3,PinLow);
				_delay_ms(50);
			}
			LCD_VidDisplayClear();
			LCD_VidSendString("Incorrect Name !");
			LCD_VidGotoXY(1,0);
			LCD_VidSendString("Try[");
			LCD_VidSendValue(TRY+2);
			LCD_VidSendString("]:");
			LCD_VidGotoXY(1,7);

			UART_VidSendString("Incorrect Name ! , Try[");
			UART_VidSendValue(TRY+2);
			UART_VidSendString("] :-");

			Gloal_u8DigitCounts=0;
			TRY++;
		}
		/*---------------------  Refusing the entered Name and make a new entering Chance (end)  ------------------------------------------*/
		Gloal_u8DigitCounts=0;
/***************************************  The User is now able to control his home from his Mobile  *********************************************************** */
		if (Local_u8Enter==1)
		{
			UART_VidPuttyNewLine();
			UART_VidPuttyNewLine();

			DisplayMenu();                   /***** Menu is displayed on the User Mobile ********/
			UART_VidPuttyNewLine();
			while (1)
			{
				u8 choice=UART_u8RecieveData();
				switch (choice)
				{
					case '1' :
					{
						UART_VidPuttyNewLine();
						UART_VidSendString("L------>Lock ,U------>UnLock");
						UART_VidPuttyNewLine();
						u8 door=0;
						while(1)
						{
							door=UART_u8RecieveData();
							if (door!=0)
							{
								if (door=='L')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(door);
									UART_VidPuttyNewLine();
									Timer1_VidSetAngle(90);break;
								}
								else if (door=='U')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(door);
									UART_VidPuttyNewLine();
									Timer1_VidSetAngle(180);break;
								}
							}
						}
						DisplayMenu();

					}break;
					case '2' :
					{
						UART_VidPuttyNewLine();
						UART_VidSendString("L->Low,M->Medium,H->High,C->close");
						UART_VidPuttyNewLine();

						u8 light=0;
						while(1)
						{
							light=UART_u8RecieveData();
							if (light!=0)
							{
								if (light=='H')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(light);
									UART_VidPuttyNewLine();
									DIO_VidSetPortValue(Port_B,0b00000000);
									DIO_VidSetPinValue(Port_B,Pin7,PinHigh);DIO_VidSetPinValue(Port_B,Pin6,PinHigh);	//Turn On Red LEDs
									DIO_VidSetPinValue(Port_B,Pin5,PinHigh);DIO_VidSetPinValue(Port_B,Pin4,PinHigh);	//Turn On Yellow LEDs
									DIO_VidSetPinValue(Port_B,Pin3,PinHigh);DIO_VidSetPinValue(Port_B,Pin2,PinHigh);	//Turn On Green LEDs
									break;
								}
								else if (light=='M')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(light);
									UART_VidPuttyNewLine();
									DIO_VidSetPortValue(Port_B,0b00000000);
									DIO_VidSetPinValue(Port_B,Pin5,PinHigh);DIO_VidSetPinValue(Port_B,Pin4,PinHigh);	//Turn On Yellow LEDs
									DIO_VidSetPinValue(Port_B,Pin3,PinHigh);DIO_VidSetPinValue(Port_B,Pin2,PinHigh);	//Turn On Green LEDs
									break;
								}
								else if (light=='L')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(light);
									UART_VidPuttyNewLine();
									DIO_VidSetPortValue(Port_B,0b00000000);
									DIO_VidSetPinValue(Port_B,Pin3,PinHigh);DIO_VidSetPinValue(Port_B,Pin2,PinHigh);   //Turn On Green LEDs
									break;
								}
								else if (light=='C')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(light);
									UART_VidPuttyNewLine();
									DIO_VidSetPortValue(Port_B,0b00000000);break;  										//Turn Off All LEDs
								}
							}
						}
						DisplayMenu();

					}break;
					case '3' :
					{
						UART_VidPuttyNewLine();
						UART_VidSendString("Fan On --> O, Fan Off --> F");
						UART_VidPuttyNewLine();
						DIO_VidSetPinValue(Port_B,Pin1,PinLow);							//Used as a Ground [All Ground pins are full]

						u8 speed=0;
						while(1)
						{
							speed=UART_u8RecieveData();
							if (speed!=0)
							{
								if (speed=='O')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(speed);
									UART_VidPuttyNewLine();
									DIO_VidSetPinValue(Port_B,Pin0,PinHigh);			//Turn On DC Motor
									break;
								}
								else if (speed=='F')
								{
									UART_VidSendString("Your Choice is : ");
									UART_VidSendData(speed);
									UART_VidPuttyNewLine();
									DIO_VidSetPinValue(Port_B,Pin0,PinLow);				//Turn On DC Motor
									break;
								}
							}
						}
						DisplayMenu();
					}break;
					case '4' :
					{
						WTD_VidEnable();
						/*WatchDog Timer will sleep for 1.0 second then will reset the program due to entering endless while loop*/
						WTD_VidSleep(SLEEP_1_POINT_0_S);
						while(1);
					}break;
				}
			}
		}
	}
	/*----------------------------------------------------------  While Loop (end)  --------------------------------------------------------*/
}
/****************************************************************  Main [End] *****************************************************************************/

/************************  Implementation for the called Functions  ************************/
void CLRInputDataArray (u8 *Copy_Array)
{
	u8 Local_u8CLRCounter;
	for (Local_u8CLRCounter=0 ; Local_u8CLRCounter<20 ; Local_u8CLRCounter++)
	{
		Copy_Array[Local_u8CLRCounter]=' ';
	}
}
/*********************************************************************************************/
void DisplayInputDataArray (u8 *Copy_Array)
{
	u8 Local_u8DISPCounter;
	for (Local_u8DISPCounter=0 ; Local_u8DISPCounter<Gloal_u8DigitCounts ; Local_u8DISPCounter++)
	{
		LCD_VidSendData(Copy_Array[Local_u8DISPCounter]);
	}
}
/*********************************************************************************************/
void DisplayMenu (void)
{
	UART_VidSendString("--------------------------------------------");
	UART_VidPuttyNewLine();
	UART_VidSendString("To control The Door   Press -> [ 1 ]");
	UART_VidPuttyNewLine();
	UART_VidSendString("To control The Light  Press -> [ 2 ]");
	UART_VidPuttyNewLine();
	UART_VidSendString("To control The Fan    Press -> [ 3 ]");
	UART_VidPuttyNewLine();
	UART_VidSendString("To  RESET The System  Press -> [ 4 ]");
	UART_VidPuttyNewLine();
	UART_VidSendString("--------------------------------------------");
}
/*********************************************************************************************/
void CheckName (void)
{
	u8 Local_u8Row , Local_u8DigitNum , Local_u8Exist;
	for (Local_u8Row=0 ; Local_u8Row<USERS_SIZE ; Local_u8Row++)
	{
		for (Local_u8DigitNum=0 ; Local_u8DigitNum<=Gloal_u8DigitCounts ; Local_u8DigitNum++)
		{
			if (Arr[Local_u8Row].name[Local_u8DigitNum]==NAME[Local_u8DigitNum])
			{
				Gloal_u8Location=Local_u8Row;
				if (Local_u8DigitNum==Gloal_u8DigitCounts   &&   Gloal_u8Location!='0')
				{
					Local_u8Exist=1;
					break;
				}
			}
			else
			{
				Gloal_u8Location='0';
				break;
			}
		}
		if (Local_u8Exist==1)   // saving time : if equal 1 it will not continue searching
		{
			break;
		}
	}
	CLRInputDataArray (NAME);
}
/*********************************************************************************************/
void CheckPassword (void)
{
	u8 Local_u8DigitNum ;
	for (Local_u8DigitNum=0 ; Local_u8DigitNum<=Gloal_u8DigitCounts ; Local_u8DigitNum++)
	{
		if (Arr[Gloal_u8Location].password[Local_u8DigitNum]==PASSWORD[Local_u8DigitNum])
		{
			Gloal_u8PasswordAcceptance=YES;
		}
		else
		{
			Gloal_u8PasswordAcceptance=NO;
			break;
		}
	}
	CLRInputDataArray(PASSWORD);
}
/*********************************************************************************************/
