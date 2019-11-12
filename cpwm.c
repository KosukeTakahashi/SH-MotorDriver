#include "iodefine.h"
#include "cpwm.h"

int _carrier_cycle;
int _deadtime;

void init_cpwm_handler(const int carrier_cycle, const int deadtime)
{
    _carrier_cycle = carrier_cycle;
    _deadtime = deadtime;
    /***************************************
     * 相補PWM 設定                          *
     ***************************************/
    // [1] カウンタ停止
    MTU2.TSTR.BIT.CST3 = 0;
    MTU2.TSTR.BIT.CST4 = 0;

    // [2] カウンタクロック・カウンタクリア要因選択
    //      → 立ち上がりエッジでカウント
    //      → クロック MPφ/1 = 25 [MHz] = 40 [ns/count]
    MTU23.TCR.BIT.CKEG = 0;
    MTU23.TCR.BIT.TPSC = 0;
    MTU24.TCR.BIT.CKEG = 0;
    MTU24.TCR.BIT.TPSC = 0;

    // [3] BLDC モータ制御設定
    //      デフォルト（設定なし）

    // [4] TCNT 設定
    MTU23.TCNT = deadtime;
    MTU24.TCNT = 0;

    // [5] チャネル間同期設定
    //      デフォルト

    // [6] TGR 初期設定
    MTU23.TGRB = 0;
    MTU24.TGRA = 0;
    MTU24.TGRB = 0;
    MTU23.TGRD = 0;
    MTU24.TGRC = 0;
    MTU24.TGRD = 0;

    // [7] デッドタイム生成の有無の設定
    //      デフォルト

    // [8] デッドタイム・キャリア周期設定
    MTU2.TDDR = deadtime;
    MTU2.TCDR = carrier_cycle / 2;
    MTU2.TCBR = carrier_cycle / 2;
    MTU23.TGRA = (carrier_cycle / 2) + deadtime;
    MTU23.TGRC = (carrier_cycle / 2) + deadtime;

    // [9] PWM 波形出力許可・PWM 出力レベル設定
    MTU2.TOCR1.BIT.PSYE = 0; // PWM キャリア周期に同期したトグル出力を禁止
    MTU2.TOCR1.BIT.OLSN = 0; // Active -> LOW
    MTU2.TOCR1.BIT.OLSP = 0; // Active -> LOW

    // [10] 相補PWM モード設定
    MTU23.TMDR.BIT.MD = 0xE; // 相補PWM モード（谷転送）
    MTU23.TMDR.BIT.BFA = 1;  // バッファ動作A; TGRA, TGRC はバッファ動作
    MTU23.TMDR.BIT.BFB = 1;  // バッファ動作B; TGRB, TGRD はバッファ動作

    // [11] 波形出力許可
    MTU2.TOER.BIT.OE3B = 1;
    MTU2.TOER.BIT.OE3D = 1;
    MTU2.TOER.BIT.OE4A = 1;
    MTU2.TOER.BIT.OE4C = 1;
    MTU2.TOER.BIT.OE4B = 1;
    MTU2.TOER.BIT.OE4D = 1;

    // [12] PFC 設定
    //      ポート E IO 設定へ
}

void prohibit_cpwm_output(void)
{
    POE.SPOER.BIT.MTU2CH34HIZ = 1;
}

void allow_cpwm_output(void)
{
    if (POE.SPOER.BIT.MTU2CH34HIZ == 1)
        POE.SPOER.BIT.MTU2CH34HIZ = 0;
}

void start_cpwm_output(void)
{
    allow_cpwm_output();
    MTU2.TSTR.BIT.CST3 = 1;
    MTU2.TSTR.BIT.CST4 = 1;
}

void stop_cpwm_output(void)
{
    MTU2.TSTR.BIT.CST3 = 0;
    MTU2.TSTR.BIT.CST4 = 0;
    prohibit_cpwm_output();
}

void update_cpwm_duty(const int tgr_u, const int tgr_v, const int tgr_w)
{
    int tgr_limit = _carrier_cycle / 2;
    int tgr_margin = _deadtime;
    int tgr_upper_limit = tgr_limit - tgr_margin;
    int tgr_lower_limit = tgr_margin;

    // TGR値の上限・下限を超える場合は切り捨て
    MTU23.TGRD = tgr_u < tgr_lower_limit
                     ? tgr_lower_limit
                     : (tgr_upper_limit < tgr_u
                            ? tgr_upper_limit
                            : tgr_u);
    MTU24.TGRC = tgr_v < tgr_lower_limit
                     ? tgr_lower_limit
                     : (tgr_upper_limit < tgr_v
                            ? tgr_upper_limit
                            : tgr_v);
    MTU24.TGRD = tgr_w < tgr_lower_limit
                     ? tgr_lower_limit
                     : (tgr_upper_limit < tgr_v
                            ? tgr_upper_limit
                            : tgr_w);
}
