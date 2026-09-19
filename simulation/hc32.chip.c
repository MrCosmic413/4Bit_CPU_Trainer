#include "wokwi-api.h"
#include <stdlib.h>
#include <stdint.h>
typedef struct { pin_t a1,b1,y1,a2,b2,y2,a3,b3,y3,a4,b4,y4; } chip_state_t;
static uint32_t logic_op(uint32_t a,uint32_t b){ return (a||b)?HIGH:LOW; }
static void update(void *u,pin_t p,uint32_t v){
  chip_state_t*c=(chip_state_t*)u;
  pin_write(c->y1,logic_op(pin_read(c->a1),pin_read(c->b1)));
  pin_write(c->y2,logic_op(pin_read(c->a2),pin_read(c->b2)));
  pin_write(c->y3,logic_op(pin_read(c->a3),pin_read(c->b3)));
  pin_write(c->y4,logic_op(pin_read(c->a4),pin_read(c->b4)));
}
void chip_init(void){
  chip_state_t*c=malloc(sizeof(chip_state_t));
  c->a1=pin_init("1A",INPUT); c->b1=pin_init("1B",INPUT); c->y1=pin_init("1Y",OUTPUT_LOW);
  c->a2=pin_init("2A",INPUT); c->b2=pin_init("2B",INPUT); c->y2=pin_init("2Y",OUTPUT_LOW);
  c->a3=pin_init("3A",INPUT); c->b3=pin_init("3B",INPUT); c->y3=pin_init("3Y",OUTPUT_LOW);
  c->a4=pin_init("4A",INPUT); c->b4=pin_init("4B",INPUT); c->y4=pin_init("4Y",OUTPUT_LOW);
  const pin_watch_config_t cfg={.edge=BOTH,.pin_change=update,.user_data=c};
  pin_watch(c->a1,&cfg); pin_watch(c->b1,&cfg); pin_watch(c->a2,&cfg); pin_watch(c->b2,&cfg);
  pin_watch(c->a3,&cfg); pin_watch(c->b3,&cfg); pin_watch(c->a4,&cfg); pin_watch(c->b4,&cfg);
  update(c,0,0);
}
