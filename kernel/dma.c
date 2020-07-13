#include "kernel.h"

void Dmach_En(uchar ch , uchar en)
{
	switch (ch){
		case 1:
			if(en==1){
				DMA1_Channel1->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel1->CPAR &= ~(1<<0);
			}break;
			case 2:
			if(en==1){
				DMA1_Channel2->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel2->CPAR &= ~(1<<0);
			}break;
			case 3:
			if(en==1){
				DMA1_Channel3->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel3->CPAR &= ~(1<<0);
			}break;
			case 4:
			if(en==1){
				DMA1_Channel4->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel4->CPAR &= ~(1<<0);
			}break;
			case 5:
			if(en==1){
				DMA1_Channel5->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel5->CPAR &= ~(1<<0);
			}break;
			case 6:
			if(en==1){
				DMA1_Channel6->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel6->CPAR &= ~(1<<0);
			}break;
			case 7:
			if(en==1){
				DMA1_Channel7->CPAR |= 1<<0;
			}
			else{
				DMA1_Channel7->CPAR &= ~(1<<0);
			}break;
		}	
}
