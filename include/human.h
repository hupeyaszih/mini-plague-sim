#ifndef HUMAN_H
#define HUMAN_H

#include <stdint.h>

#define HEALTH_MASK 0x03  // 00000011
#define DAYS_MASK   0xFC  // 11111100
#define DAYS_SHIFT  2

#define HEALTH_SITUATION_HEALTHY 0x00 // 00
#define HEALTH_SITUATION_SICK 0x01    // 01
#define HEALTH_SITUATION_DEAD 0x02    // 10
#define HEALTH_SITUATION_CURED 0x03   // 11

static inline void human_set_health_situation(uint8_t* restrict human, uint8_t status){
    *human = (*human & ~HEALTH_MASK) | (status & HEALTH_MASK);
}

static inline void human_set_days_for_sick(uint8_t* restrict human, uint8_t days){
    *human = (*human & ~DAYS_MASK) | ((days << DAYS_SHIFT) & DAYS_MASK);
}

static inline const uint8_t human_get_health_situation(const uint8_t* restrict human){
    return (*human & HEALTH_MASK);
}

static inline const uint8_t human_get_days_for_sick(const uint8_t* restrict human){
    return (*human & DAYS_MASK) >> DAYS_SHIFT;
}


#endif
