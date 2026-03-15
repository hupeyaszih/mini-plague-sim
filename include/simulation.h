#ifndef SIMULATON_H
#define SIMULATON_H

#include <stdint.h>

typedef struct {
    uint8_t* people;
    uint8_t* people_buffer;
    uint16_t people_count;

    //[0] healthy, [1] Sick, [2] Dead, [3] Cured
    int counts[4];
} Simulation;


extern const char* status_table[];

Simulation* create_simulation(uint16_t people_size);
void delete_simulation(Simulation* simulation);
void simulation_update(Simulation* restrict simulation, int day, int plague_kills_after_day);

#endif
