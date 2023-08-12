/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : TIMER DRIVER  *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "TIMER_private.h"
# include "TIMER_config.h"
# include "TIMER_interface.h"


static void (* TIMER0_Normal_pvCallBackFunc)(void)=NULL;
static void (* TIMER0_CTC_pvCallBackFunc)(void)=NULL;

static void (* TIMER2_Normal_pvCallBackFunc)(void)=NULL;
static void (* TIMER2_CTC_pvCallBackFunc)(void)=NULL;

static void (* ICU_pvCallBackFunc)(void)=NULL;



/****************************************************** TIMER 0 ***********************************************************************/

void TIMER0_VidNormalInit (void)
{
	/*Select Normal Mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

	/*Preload TCNT0 register*/
	TCNT0 =TCNT0_PRELOAD_VALUE;

	/*Enable one Type from the Compare Mode Interrupts*/
	SET_BIT(TIMSK,TIMSK_TOIE0);      //Enable Overflow Interrupt

	/*Select Prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_NORMAL_MODE_PRESCALER;

}

void TIMER0_VidCTCInit (void)
{
	/*Select CTC Mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Set a value in Output Compare Register to force the TCCR0 register to overflow at*/
	OCR0=OCR0_PRELOAD_VALUE;

	/*Enable one Type from the Compare Mode Interrupts*/
	SET_BIT(TIMSK,TIMSK_OCIE0);      //Enable CTC Interrupt

	/*Select Prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_CTC_MODE_PRESCALER;
}


void TIMER0_VidFPWMInit (void)
{
	/*Select Fast PWM Mode*/

	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Select set on top and clear on compare*/
	#if COMPARE_MODE_FAST_PWM_MODE==CLEAR_OC0_ON_COMPARE_SET_OC0_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	#elif COMPARE_MODE_FAST_PWM_MODE==SET_OC0_ON_COMPARE_CLEAR_OC0_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
	#elif COMPARE_MODE_FAST_PWM_MODE==NORMAL_PORT_OPERATION_OC0_DISCONNECTED_IN_FPWM
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	#endif

	/*Set OCR0 (On time)*/
	// it is done in the SET DUTY FUNCTION below

	/*Set Prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_FAST_PWM_MODE_PRESCALER;
}


void TIMER0_VidPhaseCorrectPWMInit (void)
{
	/*Select Phase correct Mode*/

	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

	/*Select set on Compare when downcounting and clear on Compare when upcounting*/
	#if COMPARE_MODE_PHASE_CORRECT_PWM_MODE==CLEAR_OC0_ON_UPCOUNTING_SET_OC0_ON_DOWNCOUNTING
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	#elif COMPARE_MODE_PHASE_CORRECT_PWM_MODE==SET_OC0_ON_UPCOUNTING_CLEAR_OC0_ON_DOWNCOUNTING
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
	#elif COMPARE_MODE_PHASE_CORRECT_PWM_MODE==NORMAL_PORT_OPERATION_OC0_DISCONNECTED_IN_PASE_CORRECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	#endif

	/*Set OCR0 (On time)*/
	// it is done in the function below

	/*Set Prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_PHASE_CORRECT_PWM_MODE_PRESCALER;
}

void Timer0_VidSetDuty(u8 Copy_u8Duty)    // Used with TIMER0_VidFPWMInit FUNCTION & TIMER0_VidPhaseCorrectPWMInit FUNCTION
{
	OCR0=(256*Copy_u8Duty)/100;
}

u8 TIMER0_Normal_u8SetCallBack (void (* Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if (Copy_pvCallBackFunc!=NULL)
	{
		TIMER0_Normal_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*TIMER0 Normal [Overflow] ISR*/
void __vector_11 (void)  __attribute__((signal));
void __vector_11 (void)
{
	if (TIMER0_Normal_pvCallBackFunc!=NULL)
	{
		TIMER0_Normal_pvCallBackFunc();
	}
}

u8 TIMER0_CTC_u8SetCallBack (void (* Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if (Copy_pvCallBackFunc!=NULL)
	{
		TIMER0_CTC_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*TIMER0 CTC ISR*/
void __vector_10 (void)  __attribute__((signal));
void __vector_10 (void)
{
	if (TIMER0_CTC_pvCallBackFunc!=NULL)
	{
		TIMER0_CTC_pvCallBackFunc();
	}
}


/****************************************************** TIMER 1 ***********************************************************************/

//------------------------------------------------------------------------------
/*Software Input Capture Unit*/
//------------------------------------------------------------------------------
void TIMER1_VidNormalInit (void)
{
	/*Select Normal Mode*/
	/*- By default it is in Normal mode {all bits are equal zero}*/

	/*TCNT1 register will be by default loaded by zero at the beginning*/

	/*Select Prescaler DIV_BY_8*/
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_NORMAL_MODE_PRESCALER;

}

void TIMER1_VidSetTimerValue (u16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}

u16 TIMER1_u16GetTimerValue (void)
{
	return TCNT1;
}

//------------------------------------------------------------------------------
/*Servo Motor Applications*/
//------------------------------------------------------------------------------

void TIMER1_VidFPWMInit (void)
{
	/*Select Fast PWM Mode*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Select Set on top Clear on compare*/
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);

	/*Set ICR value*/
	ICR1=ICR1_PRELOAD_VALUE;

	/*Set Prescaler*/
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_FAST_PWM_MODE_PRESCALER;

}

void Timer1_VidSetAngle(u8 Copy_u8Angle)       // Used in Servo Application with TIMER1_VidFPWMInit FUNCTION [450---->2400]
{
	OCR1A=(65*Copy_u8Angle)/6+450;
}

//------------------------------------------------------------------------------
/*Hardware Input Capture Unit*/
//------------------------------------------------------------------------------

/*Initiate ICU of Timer1*/
void ICU_VidInit (void)
{
	/*Set ICU Edge as Rising*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable ICU Inturrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

/*Set ICU Edge sense control [Rising - Falling]*/
void ICU_VidSetSenseControl (u8 Copy_u8ICUEdge)
{
	if (Copy_u8ICUEdge==ICU_HW_RISING)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if (Copy_u8ICUEdge==ICU_HW_FALLING)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}

}

/*ICU Inturrupt Enable & Disable*/
void ICU_VidInturruptControl (u8 Copy_u8InturruptStatus)
{
	if (Copy_u8InturruptStatus==ICU_HW_INT_ENABLE)
	{
		SET_BIT(TIMSK,TIMSK_TICIE1);
	}
	else if (Copy_u8InturruptStatus==ICU_HW_INT_DISABLE)
	{
		CLR_BIT(TIMSK,TIMSK_TICIE1);
	}

}

/*Get ICU Value inside the ICR1 register*/
u16 ICU_u16GetICUValue (void)
{
	return ICR1;
}

u8 ICU_u8SetCallBack (void (* Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if (Copy_pvCallBackFunc!=NULL)
	{
		ICU_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*ICU ISR*/
void __vector_6 (void)  __attribute__((signal));
void __vector_6 (void)
{
	if (ICU_pvCallBackFunc!=NULL)
	{
		ICU_pvCallBackFunc();
	}
}

/****************************************************** WATCHDOG TIMER ***************************************************************/

void WTD_VidSleep (u8 Copy_u8SleepTime)
{
	/*Clear the Prescaler Bits*/
	WDTCR&=0b11111000;

	/*Set the Required Prescaler*/
	WDTCR|=Copy_u8SleepTime;
}

void WTD_VidEnable (void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}

void WTD_VidDisable (void)
{
	WDTCR|=0b00011000;

	WDTCR=0b00000000;
}


/****************************************************** TIMER 2 ***********************************************************************/

void TIMER2_VidNormalInit (void)
{
	/*Select Normal Mode*/
	CLR_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);

	/*Preload TCNT0 register*/
	TCNT2 =TCNT2_PRELOAD_VALUE;

	/*Enable one Type from the Compare Mode Interrupts*/
	SET_BIT(TIMSK,TIMSK_TOIE2);      //Enable Overflow Interrupt

	/*Select Prescaler*/
	TCCR2 &= 0b11111000;
	TCCR2 |= TIMER2_NORMAL_MODE_PRESCALER;

}

void TIMER2_VidCTCInit (void)
{
	/*Select CTC Mode*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);

	/*Set a value in Output Compare Register to force the TCCR0 register to overflow at*/
	OCR2=OCR2_PRELOAD_VALUE;

	/*Enable one Type from the Compare Mode Interrupts*/
	SET_BIT(TIMSK,TIMSK_OCIE2);      //Enable CTC Interrupt

	/*Select Prescaler*/
	TCCR2 &= 0b11111000;
	TCCR2 |= TIMER2_CTC_MODE_PRESCALER;
}


void TIMER2_VidFPWMInit (void)
{
	/*Select Fast PWM Mode*/

	SET_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);

	/*Select set on top and clear on compare*/
	#if COMPARE_MODE_FAST_PWM_MODE==CLEAR_OC2_ON_COMPARE_SET_OC2_ON_TOP
	SET_BIT(TCCR2,TCCR2_COM21);
	CLR_BIT(TCCR2,TCCR2_COM20);
	#elif COMPARE_MODE_FAST_PWM_MODE==SET_OC2_ON_COMPARE_CLEAR_OC2_ON_TOP
	SET_BIT(TCCR2,TCCR02_COM21);
	SET_BIT(TCCR2,TCCR2_COM20);
	#elif COMPARE_MODE_FAST_PWM_MODE==NORMAL_PORT_OPERATION_OC2_DISCONNECTED_IN_FPWM
	CLR_BIT(TCCR2,TCCR2_COM21);
	CLR_BIT(TCCR2,TCCR2_COM20);
	#endif

	/*Set OCR0 (On time)*/
	// it is done in the SET DUTY FUNCTION below

	/*Set Prescaler*/
	TCCR2 &= 0b11111000;
	TCCR2 |= TIMER2_FAST_PWM_MODE_PRESCALER;
}


void TIMER2_VidPhaseCorrectPWMInit (void)
{
	/*Select Phase correct Mode*/

	SET_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);

	/*Select set on Compare when downcounting and clear on Compare when upcounting*/
	#if COMPARE_MODE_PHASE_CORRECT_PWM_MODE==CLEAR_OC2_ON_UPCOUNTING_SET_OC2_ON_DOWNCOUNTING
	SET_BIT(TCCR2,TCCR2_COM21);
	CLR_BIT(TCCR2,TCCR2_COM20);
	#elif COMPARE_MODE_PHASE_CORRECT_PWM_MODE==SET_OC2_ON_UPCOUNTING_CLEAR_OC2_ON_DOWNCOUNTING
	SET_BIT(TCCR2,TCCR2_COM21);
	SET_BIT(TCCR2,TCCR2_COM20);
	#elif COMPARE_MODE_PHASE_CORRECT_PWM_MODE==NORMAL_PORT_OPERATION_OC2_DISCONNECTED_IN_PASE_CORRECT
	CLR_BIT(TCCR2,TCCR2_COM21);
	CLR_BIT(TCCR2,TCCR2_COM20);
	#endif

	/*Set OCR2 (On time)*/
	// it is done in the function below

	/*Set Prescaler*/
	TCCR2 &= 0b11111000;
	TCCR2 |= TIMER2_PHASE_CORRECT_PWM_MODE_PRESCALER;
}

void Timer2_VidSetDuty(u8 Copy_u8Duty)    // Used with TIMER2_VidFPWMInit FUNCTION & TIMER0_VidPhaseCorrectPWMInit FUNCTION
{
	OCR2=(256*Copy_u8Duty)/100;
}

u8 TIMER2_Normal_u8SetCallBack (void (* Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if (Copy_pvCallBackFunc!=NULL)
	{
		TIMER2_Normal_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*TIMER2 Normal [Overflow] ISR*/
void __vector_5 (void)  __attribute__((signal));
void __vector_5 (void)
{
	if (TIMER2_Normal_pvCallBackFunc!=NULL)
	{
		TIMER2_Normal_pvCallBackFunc();
	}
}

u8 TIMER2_CTC_u8SetCallBack (void (* Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if (Copy_pvCallBackFunc!=NULL)
	{
		TIMER2_CTC_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*TIMER2 CTC ISR*/
void __vector_4 (void)  __attribute__((signal));
void __vector_4 (void)
{
	if (TIMER2_CTC_pvCallBackFunc!=NULL)
	{
		TIMER2_CTC_pvCallBackFunc();
	}
}






