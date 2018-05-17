#include "stm32f4xx_hal.h"
#include <stdbool.h>

void _Error_Handler( char* file, int line );
void system_clock_config( void );


int main( void )
{
	system_clock_config();
	
	return 0;
}




void system_clock_config( void )
{
	__HAL_RCC_GPIOH_CLK_ENABLE();
	
	RCC_OscInitTypeDef osc_config;
	osc_config.LSIState = RCC_LSI_OFF;
	osc_config.LSEState = RCC_LSE_OFF;
	osc_config.HSIState = RCC_HSI_OFF;
	osc_config.HSEState = RCC_HSE_ON;
	osc_config.HSICalibrationValue = 0x00;
	osc_config.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_config.PLL.PLLM = 4;
	osc_config.PLL.PLLN = 168;
	osc_config.PLL.PLLP = 2;
	osc_config.PLL.PLLQ = 7;
	osc_config.PLL.PLLState = RCC_PLL_ON;
	osc_config.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	if( HAL_RCC_OscConfig( &osc_config ) != HAL_OK )
		_Error_Handler( __FILE__, __LINE__ );
	
	RCC_ClkInitTypeDef clk_config;
	clk_config.ClockType = RCC_CLOCKTYPE_SYSCLK |
													RCC_CLOCKTYPE_HCLK |
													RCC_CLOCKTYPE_PCLK1 |
													RCC_CLOCKTYPE_PCLK2;
	clk_config.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_config.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_config.APB1CLKDivider = RCC_HCLK_DIV4;
	clk_config.APB2CLKDivider = RCC_HCLK_DIV2;
	if( HAL_RCC_ClockConfig( &clk_config, FLASH_LATENCY_5 ) )
		_Error_Handler( __FILE__, __LINE__ );
	
	return;
}


HAL_StatusTypeDef HAL_InitTick( uint32_t TickPriority )
{
	return HAL_OK;
}




void _Error_Handler( char* file, int line )
{
	//volatile char* _file = file;
	//volatile int _line = line;
	while( true ) ;
}


void vApplicationStackOverflowHook( void )
{
	_Error_Handler( __FILE__, __LINE__ );
}

void vApplicationMallocFailedHook( void )
{
	_Error_Handler( __FILE__, __LINE__ );
}
