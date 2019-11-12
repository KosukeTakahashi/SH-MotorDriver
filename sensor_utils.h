#ifndef SENSOR_UTILS_H
#define SENSOR_UTILS

void get_uvw_dc_current_ad(int *u, int *v, int *w, int *dc);
void get_accel(int *accel_ad);
void get_resolver(int *resolver);
void get_resolver_err_state(int *reserr);

#endif
