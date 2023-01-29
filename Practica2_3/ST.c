#include "lib/include.h"

#define NVIC_ST_CTRL_R      (*((volatile uint32_t *)0xE000E010))

#define NVIC_ST_RELOAD_R    (*((volatile uint32_t *)0xE000E014))

#define NVIC_ST_CURRENT_R   (*((volatile uint32_t *)0xE000E018))

extern void SysTick_Init(void){

  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup

  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock

}

// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)

extern void SysTick_Wait(uint32_t delay){

  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait

  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears

  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag

  }

}

// 800000*12.5ns equals 10ms

extern void SysTick_Wait10ms(uint32_t delay){

  uint32_t i;

  for(i=0; i<delay; i++){

    SysTick_Wait(800000);  // wait 10ms

  }

}