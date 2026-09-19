#include "wokwi-api.h"
#include <stdlib.h>
#include <stdint.h>
typedef struct{pin_t oe1,oe2,q0,q1,q2,q3,cp,e1,e2,d3,d2,d1,d0,mr;uint32_t q;} chip_state_t;
static void drive(chip_state_t*c){
 if(pin_read(c->oe1)||pin_read(c->oe2)){pin_mode(c->q0,INPUT);pin_mode(c->q1,INPUT);pin_mode(c->q2,INPUT);pin_mode(c->q3,INPUT);return;}
 pin_mode(c->q0,OUTPUT);pin_mode(c->q1,OUTPUT);pin_mode(c->q2,OUTPUT);pin_mode(c->q3,OUTPUT);
 pin_write(c->q0,(c->q>>0)&1);pin_write(c->q1,(c->q>>1)&1);pin_write(c->q2,(c->q>>2)&1);pin_write(c->q3,(c->q>>3)&1);
}
static void ctrl(void*u,pin_t p,uint32_t v){chip_state_t*c=(chip_state_t*)u;if(pin_read(c->mr))c->q=0;drive(c);}
static void clk(void*u,pin_t p,uint32_t v){
 chip_state_t*c=(chip_state_t*)u;
 if(pin_read(c->mr))c->q=0;
 else if(!pin_read(c->e1)&&!pin_read(c->e2))c->q=(pin_read(c->d0)?1:0)|(pin_read(c->d1)?2:0)|(pin_read(c->d2)?4:0)|(pin_read(c->d3)?8:0);
 drive(c);
}
void chip_init(void){
 chip_state_t*c=malloc(sizeof(chip_state_t));c->q=0;
 c->oe1=pin_init("OE1",INPUT);c->oe2=pin_init("OE2",INPUT);c->q0=pin_init("Q0",OUTPUT_LOW);c->q1=pin_init("Q1",OUTPUT_LOW);
 c->q2=pin_init("Q2",OUTPUT_LOW);c->q3=pin_init("Q3",OUTPUT_LOW);c->cp=pin_init("CP",INPUT);c->e1=pin_init("E1",INPUT);
 c->e2=pin_init("E2",INPUT);c->d3=pin_init("D3",INPUT);c->d2=pin_init("D2",INPUT);c->d1=pin_init("D1",INPUT);c->d0=pin_init("D0",INPUT);c->mr=pin_init("MR",INPUT);
 const pin_watch_config_t cc={.edge=BOTH,.pin_change=ctrl,.user_data=c}; const pin_watch_config_t ck={.edge=RISING,.pin_change=clk,.user_data=c};
 pin_watch(c->oe1,&cc);pin_watch(c->oe2,&cc);pin_watch(c->mr,&cc);pin_watch(c->cp,&ck);drive(c);
}
