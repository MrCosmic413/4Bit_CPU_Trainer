#include "wokwi-api.h"
#include <stdlib.h>
#include <stdint.h>
typedef struct{pin_t a0,a1,a2,a3,b0,b1,b2,b3,cin,s0,s1,s2,s3,cout;} chip_state_t;
static void update(void*u,pin_t p,uint32_t v){
 chip_state_t*c=(chip_state_t*)u;
 uint32_t a=(pin_read(c->a0)?1:0)|(pin_read(c->a1)?2:0)|(pin_read(c->a2)?4:0)|(pin_read(c->a3)?8:0);
 uint32_t b=(pin_read(c->b0)?1:0)|(pin_read(c->b1)?2:0)|(pin_read(c->b2)?4:0)|(pin_read(c->b3)?8:0);
 uint32_t s=a+b+(pin_read(c->cin)?1:0);
 pin_write(c->s0,(s>>0)&1); pin_write(c->s1,(s>>1)&1); pin_write(c->s2,(s>>2)&1); pin_write(c->s3,(s>>3)&1); pin_write(c->cout,(s>>4)&1);
}
void chip_init(void){
 chip_state_t*c=malloc(sizeof(chip_state_t));
 c->s1=pin_init("S1",OUTPUT_LOW); c->b1=pin_init("B1",INPUT); c->a1=pin_init("A1",INPUT); c->s0=pin_init("S0",OUTPUT_LOW);
 c->a0=pin_init("A0",INPUT); c->b0=pin_init("B0",INPUT); c->cin=pin_init("CIN",INPUT); c->cout=pin_init("COUT",OUTPUT_LOW);
 c->s3=pin_init("S3",OUTPUT_LOW); c->b3=pin_init("B3",INPUT); c->a3=pin_init("A3",INPUT); c->s2=pin_init("S2",OUTPUT_LOW);
 c->a2=pin_init("A2",INPUT); c->b2=pin_init("B2",INPUT);
 const pin_watch_config_t cfg={.edge=BOTH,.pin_change=update,.user_data=c};
 pin_watch(c->a0,&cfg);pin_watch(c->a1,&cfg);pin_watch(c->a2,&cfg);pin_watch(c->a3,&cfg);
 pin_watch(c->b0,&cfg);pin_watch(c->b1,&cfg);pin_watch(c->b2,&cfg);pin_watch(c->b3,&cfg);pin_watch(c->cin,&cfg);
 update(c,0,0);
}
