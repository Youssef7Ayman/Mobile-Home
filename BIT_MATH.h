#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

		/* Set Bit */
#define SET_BIT(REG,BIT_NUM)  REG|=1<<BIT_NUM

		/* Clear Bit */
#define CLR_BIT(REG,BIT_NUM)  REG&=~(1<<BIT_NUM)

		/* Toggle Bit */
#define TOGGLE_BIT(REG,BIT_NUM)  REG^=(1<<BIT_NUM)

		/* Get Bit */
#define GET_BIT(REG,BIT_NUM)   ((REG>>BIT_NUM)&1)


#endif
