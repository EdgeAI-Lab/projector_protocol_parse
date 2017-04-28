#include "stm32f10x_conf.h"
#include "queue.h"
#include <stdio.h>
#include "data_handle.h"
#include "delay.h"

void uart_init(void);

CycQueue *q = NULL;

int main(void)
{
	q = CycQueueInit(255);
	if( q == NULL )
	{
		return -1;
	}
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(72);
	uart_init();
	
	while(1)
	{
		
		frame_data_prase();
		
	}
	
}

