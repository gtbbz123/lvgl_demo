#ifndef __LED_H
#define __LED_H


#define LED0(x)   do{ x ? \
                      GPIO_SetBits(GPIOA, GPIO_Pin_1) : \
                      GPIO_ResetBits(GPIOA, GPIO_Pin_1); \
                  }while(0)      /* LED0·­×ª */
#define LED1(x)   do{ x ? \
                      GPIO_SetBits(GPIOA, GPIO_Pin_2) : \
                      GPIO_ResetBits(GPIOA, GPIO_Pin_2); \
                  }while(0)      /* LED0·­×ª */

									
void LED_Init(void);

#endif





