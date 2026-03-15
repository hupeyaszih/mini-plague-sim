#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"

static inline void do_nothing(const Simulation* restrict simulation, const int day) { 
}

static inline void log_message(const Simulation* restrict simulation, const int day) {
    printf("\nDay: %d\n", day);
    printf("Total Healthy Count: %d\n", simulation->counts[0]);
    printf("Total Sick Count: %d\n", simulation->counts[1]);
    printf("Total Dead Count: %d\n", simulation->counts[2]);
    printf("Total Cured Count: %d\n", simulation->counts[3]);
}

int main() {
    printf("Hello from Plague-Simulation (C)!\n");
    srand(time(NULL));
    Simulation* simulation = create_simulation(32443);
    static void (*const log_handlers[2]) (const Simulation* restrict simulation, const int day) = {
        do_nothing, 
        log_message
    };

    for(int t = 0; t < 10000; t++) {
        log_handlers[t % 1000 == 0](simulation, t);
        simulation_update(simulation, t, 17);
    }

    delete_simulation(simulation);
    simulation = NULL;
    return 0;
}
