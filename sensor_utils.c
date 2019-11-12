#include "iodefine.h"
#include "sensor_utils.h"

void get_uvw_dc_current_ad(int *u, int *v, int *w, int *dc)
{
    // A/D 変換開始
    AD0.ADCR.BIT.ADST = 1;

    // A/D 変換終了まで待機
    while (!AD0.ADCSR.BIT.ADF)
        ;

    *u = AD0.ADDR0 >> 6;
    *v = AD0.ADDR1 >> 6;
    *w = AD0.ADDR2 >> 6;
    *dc = AD0.ADDR3 >> 6;
}

void get_accel(int *accel_ad)
{
    AD1.ADCR.BIT.ADST = 1;

    while (!AD1.ADCSR.BIT.ADF)
        ;

    *accel_ad = AD1.ADDR4 >> 6;
}

void get_resolver(int *resolver)
{
    *resolver = (PA.PRL.WORD >> 5) & 0x3FF;
}

void get_resolver_err_state(int *reserr)
{
    *reserr = PE.PRL.BIT.B15;
}
