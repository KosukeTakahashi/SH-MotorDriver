#ifndef CPWM_H
#define CPWM_H

void init_cpwm_handler(const int carrier_cycle, const int deadtime);
void prohibit_cpwm_output(void);
void allow_cpwm_output(void);
void start_cpwm_output(void);
void stop_cpwm_output(void);
void update_cpwm_duty(const int tgr_u, const int tgr_v, const int tgr_w);

#endif
