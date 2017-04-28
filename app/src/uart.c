#include "stm32f10x.h"
#include <stdio.h>


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	



void uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef Usart_InitStr;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// configure clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
	USART_DeInit(USART2);
	
	
	/* Configure USART2 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// uart configure
	Usart_InitStr.USART_BaudRate			     	= 115200;
	Usart_InitStr.USART_WordLength					= USART_WordLength_8b;
	Usart_InitStr.USART_StopBits						= USART_StopBits_1;
	Usart_InitStr.USART_Parity							= USART_Parity_No;
	Usart_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	Usart_InitStr.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &Usart_InitStr);
	
	NVIC_InitStructure.NVIC_IRQChannel					          = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0x00;	
	NVIC_InitStructure.NVIC_IRQChannelCmd					        = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART2, ENABLE);
}

	/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
  {}

  return ch;
}

