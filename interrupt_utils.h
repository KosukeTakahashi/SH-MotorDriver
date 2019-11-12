#ifndef INTERRUPT_UTILS_H
#define INTERRUPT_UTILS_H

void setup_interrupts(const int intr_cycle_calc_ang_velocity,
                      const int intr_cycle_read_sensors,
                      const int intr_cycle_control,
                      const int intr_cycle_communicate);
void start_interrupts(void);
void stop_interrupts(void);

#endif
