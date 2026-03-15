#include "simulation.h"
#include "human.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* status_table[] = {
    "healthy",
    "sick",
    "dead",
    "cured"
};

Simulation* create_simulation(const uint16_t people_size){
    Simulation* simulation = malloc(sizeof(Simulation));
    if(!simulation) return NULL;
    simulation->people_count = people_size;

    memset(simulation->counts, 0, sizeof(simulation->counts));
    simulation->people = NULL;
    simulation->people_buffer = NULL;
    simulation->people = malloc(sizeof(uint8_t)*(people_size+2));
    if(!simulation->people) goto cleanup;
    memset(simulation->people, 0, sizeof(uint8_t)*(people_size+2));

    simulation->people_buffer = malloc(sizeof(uint8_t)*(people_size+2));
    if(!simulation->people_buffer) goto cleanup;
    memset(simulation->people_buffer, 0, sizeof(uint8_t)*(people_size+2));

    human_set_health_situation(&simulation->people[0], HEALTH_SITUATION_DEAD);
    human_set_health_situation(&simulation->people[people_size + 1], HEALTH_SITUATION_DEAD);
    human_set_health_situation(&simulation->people_buffer[0], HEALTH_SITUATION_DEAD);
    human_set_health_situation(&simulation->people_buffer[people_size + 1], HEALTH_SITUATION_DEAD);
 

    int sick_id = 1 + (rand() % people_size);
    human_set_health_situation(&simulation->people[sick_id], HEALTH_SITUATION_SICK);

    return simulation;

cleanup:
    delete_simulation(simulation);
    return NULL;

}

void delete_simulation(Simulation* simulation){
    if(!simulation) return;
    if(simulation->people_buffer) {free(simulation->people_buffer); simulation->people_buffer = NULL;}
    if(simulation->people) {free(simulation->people); simulation->people = NULL;}
    free(simulation); 
}

void simulation_update(Simulation* restrict simulation, int day, int plague_kills_after_day){
    memcpy(simulation->people_buffer, simulation->people, sizeof(uint8_t)*(simulation->people_count+2));

    for(int i = 1;i <= simulation->people_count; i++) {
        uint8_t* human = &simulation->people[i];
        uint8_t health_status = human_get_health_situation(human);

        {
            uint8_t* next_human = &simulation->people_buffer[i+1];
            uint8_t next_human_health_status = human_get_health_situation(next_human);
            uint8_t next_trigger = ((health_status == HEALTH_SITUATION_SICK) & (next_human_health_status == HEALTH_SITUATION_HEALTHY));
            human_set_health_situation(next_human, (next_trigger * HEALTH_SITUATION_SICK) + (!next_trigger * next_human_health_status));
        }

        {
            uint8_t* prev_human = &simulation->people_buffer[i-1];
            uint8_t prev_human_health_status = human_get_health_situation(prev_human);
            uint8_t prev_trigger = ((health_status == HEALTH_SITUATION_SICK) & (prev_human_health_status == HEALTH_SITUATION_HEALTHY));
            human_set_health_situation(prev_human, (prev_trigger * HEALTH_SITUATION_SICK) + (!prev_trigger * prev_human_health_status));
        }

        uint8_t* human_buff = &simulation->people_buffer[i];
        {
            uint8_t health_status_buff = human_get_health_situation(human_buff);
            uint8_t sick_for_days_buff = human_get_days_for_sick(human_buff); 
            uint8_t dead_trigger_buff = (health_status_buff == HEALTH_SITUATION_SICK) * (sick_for_days_buff >= plague_kills_after_day);
            human_set_health_situation(human_buff, (dead_trigger_buff * HEALTH_SITUATION_DEAD) + (!dead_trigger_buff * health_status_buff));

            uint8_t is_human_dead_buff = health_status_buff == HEALTH_SITUATION_DEAD;
            human_set_days_for_sick(human_buff, ((!is_human_dead_buff * 1) + sick_for_days_buff) * (health_status_buff == HEALTH_SITUATION_SICK));
        }

        health_status = human_get_health_situation(human_buff);
        simulation->counts[health_status]++;
    }
    memcpy(simulation->people, simulation->people_buffer, sizeof(uint8_t)*(simulation->people_count+2));
}
