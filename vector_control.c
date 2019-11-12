#include "iodefine.h"
#include "mathf.h"
#include "vector_control.h"

#define PI 3.141592653589

int sin1000[360];
int cos1000[360];
int sqrt3_1000;

int _integral_d_delta_ang_vel = 0; // 速度I制御計算用; ∫d(Δω)
int _integral_d_delta_i_d = 0;     // トルクI制御計算用; ∫d(ΔId)
int _integral_d_delta_i_q = 0;     // トルクI制御計算用; ∫d(ΔIq)

void init_vector_controller(void)
{
    int d;
    float t;
    for (d = 0; d < 360; d++)
    {
        t = d * PI / 180.0f;
        sin1000[d] = 1000 * sinf(t);
        cos1000[d] = 1000 * cosf(t);
    }

    sqrt3_1000 = 1000 * sqrtf(3.0f);
}

int vector_control(const int current_u,
                   const int current_v,
                   const int current_w,
                   const int current_dc,
                   const int accel,
                   const int theta,
                   const int ang_velocity,
                   const int torque_p_gain_100,
                   const int torque_i_gain_100,
                   const int speed_p_gain_100,
                   const int speed_i_gain_100,
                   int *voltage_u,
                   int *voltage_v,
                   int *voltage_w)
{
    /* ベクトル制御 トルク制御 PI制御 */
    int i_a = (current_u) - (current_v / 2) - (current_w / 2);
    int i_b = ((current_v * sqrt3_1000 / 2) - (current_w * sqrt3_1000 / 2)) / 1000;
    int i_d = ((i_a * cos1000[theta]) + (i_b * sin1000[theta])) / 1000;
    int i_q = ((-i_a * sin1000[theta]) + (i_b * cos1000[theta])) / 1000;

    int i_d_ref = 0;
    int i_q_ref = accel;

    int delta_i_d = i_d_ref - i_d;
    int delta_i_q = i_q_ref - i_q;

    int v_d = (torque_p_gain_100 * delta_i_d + torque_i_gain_100 * _integral_d_delta_i_d) / 100;
    int v_q = (torque_p_gain_100 * delta_i_q + torque_i_gain_100 * _integral_d_delta_i_q) / 100;
    int v_a = (v_d * cos1000[theta] - v_q * sin1000[theta]) / 1000;
    int v_b = (v_d * sin1000[theta] + v_q * cos1000[theta]) / 1000;

    *voltage_u = (v_a * 2 / 3);
    *voltage_v = -(v_a / 3) + (v_b * sqrt3_1000 / 3 / 1000);
    *voltage_w = -(v_a / 3) - (v_b * sqrt3_1000 / 3 / 1000);

    return i_q;
}
