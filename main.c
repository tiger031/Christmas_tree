/**
 ******************************************************************************
 * @file    src\main.c
 * @author  Taras Shelest
 * @version V1.0
 * @date    2023-02-18
 * @brief   This file contains the main function for Christmas tree project.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "I2C.h"
#include "delay.h"
#include "stm8s.h"
#include "stm8s_gpio.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */

void ct_mcu_Leds_Write();


void main(void) {
	/* System Init */
	CLK_SYSCLKConfig (CLK_PRESCALER_HSIDIV1);
        /* GPIO Init */
	GPIO_Init(GPIOA, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_Init(GPIOC, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);

	/* Close All Peripheral Clock */
	CLK->PCKENR1 = 0x00;
	CLK->PCKENR2 = 0x00;

	Delay_Config();

	I2C_Config_Poll(100000);
        
        I2C_Multiple_Write_Poll(0x20, 0x06, 0x00, 0x00, 1);


	while (TRUE) {
          
          for(uint8_t k = 0; k < 255 ; k++)
          {
           I2C_Multiple_Write_Poll(0x20, 0x02, 0x00, k, 1);
           Delay_ms(50);
           ct_mcu_Leds_Write();
          }
	}
}
/**
  * @brief  Flashing lights from pins MCU 
  * @note    - 
  * @param  GPIOx : Select the GPIO peripheral number (x = A to I).
  * @param  GPIO_PortVal : Specifies the value to be written to the port output
  *         data register.
  * @retval None
  */
void ct_mcu_Leds_Write()
{
            for(uint8_t k = 0; k < 50 ; k++)
          {
            GPIO_Write(GPIOA, k);
            Delay_ms(50);
            GPIO_Write(GPIOC, k);
            Delay_ms(50);
            GPIO_Write(GPIOD, k);
            Delay_ms(50);
            GPIO_Write(GPIOA, 0x00);
            Delay_ms(50);
            GPIO_Write(GPIOC, 0x00);
            Delay_ms(50);
            GPIO_Write(GPIOD, 0x00);
          }
}
#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (TRUE)
	{
		printf("Wrong parameters value: file %s on line %lu\r\n", file, line);
	}
}
#endif

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
