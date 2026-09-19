#include "wokwi-api.h"
#include <stdlib.h>
#include <stdint.h>
typedef struct{pin_t e1,s1,i13,i12,i11,i10,y1,y2,i20,i21,i22,i23,s0,e2;} chip_state_t;
static uint32_t pick(uint32_t s,pin_t i0,pin_t i1,pin_t i2,pin_t i3){return s==0?pin_read(i0):s==1?pin_read(i1):s==2?pin_read(i2):pin_read(i3);}
static void update(void*u,pin_t p,uint32_t v){
 chip_state_t*c=(chip_state_t*)u; uint32_t s=(pin_read(c->s1)?2:0)|(pin_read(c->s0)?1:0);
 pin_write(c->y1,pin_read(c->e1)?LOW:pick(s,c->i10,c->i11,c->i12,c->i13));
 pin_write(c->y2,pin_read(c->e2)?LOW:pick(s,c->i20,c->i21,c->i22,c->i23));
}
void chip_init(void){
 chip_state_t*c=malloc(sizeof(chip_state_t));
 c->e1=pin_init("1E",INPUT); c->s1=pin_init("S1",INPUT); c->i13=pin_init("1I3",INPUT); c->i12=pin_init("1I2",INPUT);
 c->i11=pin_init("1I1",INPUT); c->i10=pin_init("1I0",INPUT); c->y1=pin_init("1Y",OUTPUT_LOW); c->y2=pin_init("2Y",OUTPUT_LOW);
 c->i20=pin_init("2I0",INPUT); c->i21=pin_init("2I1",INPUT); c->i22=pin_init("2I2",INPUT); c->i23=pin_init("2I3",INPUT);
 c->s0=pin_init("S0",INPUT); c->e2=pin_init("2E",INPUT);
 const pin_watch_config_t cfg={.edge=BOTH,.pin_change=update,.user_data=c};
 pin_watch(c->e1,&cfg);pin_watch(c->e2,&cfg);pin_watch(c->s0,&cfg);pin_watch(c->s1,&cfg);
 pin_watch(c->i10,&cfg);pin_watch(c->i11,&cfg);pin_watch(c->i12,&cfg);pin_watch(c->i13,&cfg);
 pin_watch(c->i20,&cfg);pin_watch(c->i21,&cfg);pin_watch(c->i22,&cfg);pin_watch(c->i23,&cfg); update(c,0,0);
}
