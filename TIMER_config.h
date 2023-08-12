/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : TIMER DRIVER  *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# ifndef TIMER_CONFIG_H
# define TIMER_CONFIG_H

/****************************************************** TIMER 0 ***********************************************************************/

// 1) NORMAL_MODE

#define TCNT0_PRELOAD_VALUE												247

/*TIMER0_NORMAL_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER0_NORMAL_MODE_PRESCALER								CLK_DIV_BY_1024
//---------------------------------------------------------------------------------------------------------------------------------------

// 2) CTC_MODE

#define OCR0_PRELOAD_VALUE												100

/*TIMER0_CTC_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER0_CTC_MODE_PRESCALER								CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------

// 3) FAST_PWM_MODE

/*COMPARE_MODE_FAST_PWM_MODE Options :
							1- NORMAL_PORT_OPERATION_OC0_DISCONNECTED_IN_FPWM
							2- CLEAR_OC0_ON_COMPARE_SET_OC0_ON_TOP
							3- SET_OC0_ON_COMPARE_CLEAR_OC0_ON_TOP             		*/

#define COMPARE_MODE_FAST_PWM_MODE							CLEAR_OC0_ON_COMPARE_SET_OC0_ON_TOP

/*TIMER0_FAST_PWM_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER0_FAST_PWM_MODE_PRESCALER								CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------

// 4) PHASE_CORRECT_PWM_MODE

/*COMPARE_MODE_PHASE_CORRECT_PWM_MODE Options :
							1- NORMAL_PORT_OPERATION_OC0_DISCONNECTED_IN_PASE_CORRECT
							2- CLEAR_OC0_ON_UPCOUNTING_SET_OC0_ON_DOWNCOUNTING
							3- SET_OC0_ON_UPCOUNTING_CLEAR_OC0_ON_DOWNCOUNTING 		 		*/

#define COMPARE_MODE_PHASE_CORRECT_PWM_MODE							CLEAR_OC0_ON_UPCOUNTING_SET_OC0_ON_DOWNCOUNTING

/*TIMER0_PHASE_CORRECT_PWM_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER0_PHASE_CORRECT_PWM_MODE_PRESCALER						CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------

/****************************************************** TIMER 1 ***********************************************************************/

// 1) NORMAL_MODE

/*TIMER1_NORMAL_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER1_NORMAL_MODE_PRESCALER								CLK_DIV_BY_8

// 2) FAST_PWM_MODE

#define ICR1_PRELOAD_VALUE											20000

/*TIMER1_FAST_PWM_MODE_PRESCALER Options :
							1- NO_CLOCK_SOURCE
							2- CLK_DIV_BY_1
							3- CLK_DIV_BY_8
                            4- CLK_DIV_BY_64
							5- CLK_DIV_BY_256
                            6- CLK_DIV_BY_1024
                            7- EXTERNAL_CLK_FALLING_EDGE
                            8- EXTERNAL_CLK_RISING_EDGE		*/

#define TIMER1_FAST_PWM_MODE_PRESCALER								CLK_DIV_BY_8


/****************************************************** TIMER 2 ***********************************************************************/

// 1) NORMAL_MODE

#define TCNT2_PRELOAD_VALUE												0

/*TIMER2_NORMAL_MODE_PRESCALER Options :
							1- T2_NO_CLOCK_SOURCE
							2- T2_CLK_DIV_BY_1
							3- T2_CLK_DIV_BY_8
                            4- T2_CLK_DIV_BY_32
							5- T2_CLK_DIV_BY_64
                            6- T2_CLK_DIV_BY_128
                            7- T2_CLK_DIV_BY_256
                            8- T2_CLK_DIV_BY_1024	*/

#define TIMER2_NORMAL_MODE_PRESCALER								T2_CLK_DIV_BY_1024
//---------------------------------------------------------------------------------------------------------------------------------------

// 2) CTC_MODE

#define OCR2_PRELOAD_VALUE												100

/*TIMER2_CTC_MODE_PRESCALER Options :
							1- T2_NO_CLOCK_SOURCE
							2- T2_CLK_DIV_BY_1
							3- T2_CLK_DIV_BY_8
                            4- T2_CLK_DIV_BY_32
							5- T2_CLK_DIV_BY_64
                            6- T2_CLK_DIV_BY_128
                            7- T2_CLK_DIV_BY_256
                            8- T2_CLK_DIV_BY_1024	*/

#define TIMER2_CTC_MODE_PRESCALER								T2_CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------

// 3) FAST_PWM_MODE

/*COMPARE_MODE_FAST_PWM_MODE Options :
							1- NORMAL_PORT_OPERATION_OC2_DISCONNECTED_IN_FPWM
							2- CLEAR_OC2_ON_COMPARE_SET_OC2_ON_TOP
							3- SET_OC2_ON_COMPARE_CLEAR_OC2_ON_TOP             		*/

#define COMPARE_MODE_FAST_PWM_MODE							CLEAR_OC2_ON_COMPARE_SET_OC2_ON_TOP

/*TIMER0_FAST_PWM_MODE_PRESCALER Options :
							1- T2_NO_CLOCK_SOURCE
							2- T2_CLK_DIV_BY_1
							3- T2_CLK_DIV_BY_8
                            4- T2_CLK_DIV_BY_32
							5- T2_CLK_DIV_BY_64
                            6- T2_CLK_DIV_BY_128
                            7- T2_CLK_DIV_BY_256
                            8- T2_CLK_DIV_BY_1024	*/

#define TIMER2_FAST_PWM_MODE_PRESCALER								T2_CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------

// 4) PHASE_CORRECT_PWM_MODE

/*COMPARE_MODE_PHASE_CORRECT_PWM_MODE Options :
							1- NORMAL_PORT_OPERATION_OC2_DISCONNECTED_IN_PASE_CORRECT
							2- CLEAR_OC2_ON_UPCOUNTING_SET_OC2_ON_DOWNCOUNTING
							3- SET_OC2_ON_UPCOUNTING_CLEAR_OC2_ON_DOWNCOUNTING 		 		*/

#define COMPARE_MODE_PHASE_CORRECT_PWM_MODE							CLEAR_OC2_ON_UPCOUNTING_SET_OC2_ON_DOWNCOUNTING

/*TIMER2_PHASE_CORRECT_PWM_MODE_PRESCALER Options :
							1- T2_NO_CLOCK_SOURCE
							2- T2_CLK_DIV_BY_1
							3- T2_CLK_DIV_BY_8
                            4- T2_CLK_DIV_BY_32
							5- T2_CLK_DIV_BY_64
                            6- T2_CLK_DIV_BY_128
                            7- T2_CLK_DIV_BY_256
                            8- T2_CLK_DIV_BY_1024	*/

#define TIMER2_PHASE_CORRECT_PWM_MODE_PRESCALER						T2_CLK_DIV_BY_8
//---------------------------------------------------------------------------------------------------------------------------------------



#endif

