/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : TIMER DRIVER  *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/


# ifndef TIMER_INTERFACE_H
# define TIMER_INTERFACE_H


/****************************************************** TIMER 0 ***********************************************************************/
void TIMER0_VidNormalInit (void);

void TIMER0_VidCTCInit (void);

void TIMER0_VidFPWMInit (void);

void TIMER0_VidPhaseCorrectPWMInit (void);

void Timer0_VidSetDuty(u8 Copy_u8Duty);

/*TIMER0 Normal&CTC ISR*/
u8 TIMER0_Normal_u8SetCallBack (void (* Copy_pvCallBackFunc)(void));

u8 TIMER0_CTC_u8SetCallBack (void (* Copy_pvCallBackFunc)(void));


/****************************************************** TIMER 1 ***********************************************************************/
//------------------------------------------------------------------------------
/*Software Input Capture Unit*/
//------------------------------------------------------------------------------
void TIMER1_VidNormalInit (void);

void TIMER1_VidSetTimerValue (u16 Copy_u16Value); //ofeten used with TIMER1_VidNormalInit FUNCTION

u16 TIMER1_u16GetTimerValue (void);               //ofeten used with TIMER1_VidNormalInit FUNCTION
//------------------------------------------------------------------------------
/*Servo Motor Applications*/
//------------------------------------------------------------------------------
void TIMER1_VidFPWMInit (void);

void Timer1_VidSetAngle(u8 Copy_u8Angle);


//------------------------------------------------------------------------------
/*Hardware Input Capture Unit*/
//------------------------------------------------------------------------------
# define ICU_HW_FALLING			0
# define ICU_HW_RISING			1
# define ICU_HW_INT_ENABLE		2
# define ICU_HW_INT_DISABLE		3


/*Initiate ICU of Timer1*/
void ICU_VidInit (void);

/*Set ICU Edge sense control [Rising - Falling]*/
void ICU_VidSetSenseControl (u8 Copy_u8ICUEdge);

/*Disable ICU Inturrupt and Enable*/
void ICU_VidInturruptControl (u8 Copy_u8InturruptStatus);

/*Get ICU Value inside the register*/
u16 ICU_u16GetICUValue (void);

/*ICU ISR*/
u8 ICU_u8SetCallBack (void (* Copy_pvCallBackFunc)(void));

/****************************************************** WATCHDOG TIMER ***********************************************************************/

/* Select WatchDog Timer (Prescaler) */

#define SLEEP_16_POINT_3_MS					0
#define SLEEP_32_POINT_5_MS					1
#define SLEEP_65_POINT_0_MS					2
#define SLEEP_0_POINT_13_S					3
#define SLEEP_0_POINT_26_S					4
#define SLEEP_0_POINT_52_S					5
#define SLEEP_1_POINT_0_S					6
#define SLEEP_2_POINT_1_S					7


void WTD_VidSleep (u8 Copy_u8SleepTime);

void WTD_VidEnable (void);

void WTD_VidDisable (void);

/****************************************************** TIMER 2 ***********************************************************************/
void TIMER2_VidNormalInit (void);

void TIMER2_VidCTCInit (void);

void TIMER2_VidFPWMInit (void);

void TIMER2_VidPhaseCorrectPWMInit (void);

void Timer2_VidSetDuty(u8 Copy_u8Duty);

/*TIMER2 Normal&CTC ISR*/
u8 TIMER2_Normal_u8SetCallBack (void (* Copy_pvCallBackFunc)(void));

u8 TIMER2_CTC_u8SetCallBack (void (* Copy_pvCallBackFunc)(void));



# endif
