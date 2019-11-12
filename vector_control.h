#ifndef VECTOR_CONTROL_H
#define VECTOR_CONTROL_H

void init_vector_controller(void);
int vector_control(const int current_u,
                   const int current_v,
                   const int current_w,
                   const int current_dc,
                   const int accel,
                   const int theta,
                   const int ang_velocity,
                   const int torque_p_gain,
                   const int torque_i_gain,
                   const int speed_p_gain,
                   const int speed_i_gain,
                   int *voltage_u,
                   int *voltage_v,
                   int *voltage_w);

#endif
