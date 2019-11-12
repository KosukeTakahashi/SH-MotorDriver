#include "iodefine.h"
#include "interrupt_utils.h"

void setup_interrupts(const int intr_cycle_calc_ang_velocity,
                      const int intr_cycle_read_sensors,
                      const int intr_cycle_control,
                      const int intr_cycle_communicate)
{
    /***************************************
     * 割り込み優先順位設定                    *
     ***************************************/
    INTC.IPRD.WORD = 0x1040; // interrupt_read_sensors
    INTC.IPRE.WORD = 0x3000; // interrupt_control
    INTC.IPRJ.WORD = 0x2000; // interrupt_communicate

    /***************************************
     * 割り込み設定                           *
     ***************************************/
    // MTU2 Ch.0
    // interrupt_calc_ang_velocity
    MTU2.TSTR.BIT.CST0 = 0;                        // カウンタ停止
    MTU20.TCNT = 0;                                // カウンタリセット
    MTU20.TCR.BIT.CCLR = 1;                        // TGRA_0 コンペアマッチ/インプットキャプチャでTCNTクリア
    MTU20.TCR.BIT.CKEG = 0;                        // クロック立ち上がりエッジでカウント
    MTU20.TCR.BIT.TPSC = 1;                        // クロック：MPφ/4 でカウント
    MTU20.TMDR.BIT.MD = 2;                         // MTU2 Ch.0 は PWMモード1
    MTU20.TIOR.BIT.IOA = 0x1;                      // 初期出力 0; TGRAコンペアマッチで 0
    MTU20.TIOR.BIT.IOB = 0x2;                      // 初期出力 0; TGRBコンペアマッチで 1
    MTU20.TIER.BYTE = 0x01;                        // TGRAコンペアマッチで割り込み許可; それ以外は禁止
    MTU20.TGRA = intr_cycle_calc_ang_velocity;     // 割り込み周期設定
    MTU20.TGRB = intr_cycle_calc_ang_velocity / 2; // ← いる？

    // MTU2 Ch.1
    // interrupt_read_sensors
    MTU2.TSTR.BIT.CST1 = 0;                   // カウンタ停止
    MTU21.TCNT = 0;                           // カウンタリセット
    MTU21.TCR.BIT.CCLR = 1;                   // TGRA_1 コンペアマッチ/インプットキャプチャでTCNTクリア
    MTU21.TCR.BIT.CKEG = 0;                   // クロック立ち上がりエッジでカウント
    MTU21.TCR.BIT.TPSC = 0;                   // クロック: MPφ/1 = 25 [MHz] = 40 [ns/count]
    MTU21.TMDR.BIT.MD = 2;                    // MTU2 Ch.1 は PWMモード1
    MTU21.TIOR.BIT.IOA = 0x1;                 // 初期出力 0; TGRAコンペアマッチで 0
    MTU21.TIOR.BIT.IOB = 0x2;                 // 初期出力 0; TGRBコンペアマッチで 1
    MTU21.TIER.BYTE = 0x01;                   // TGRAコンペアマッチで割り込み許可; それ以外は禁止
    MTU21.TGRA = intr_cycle_read_sensors;     // 割り込み周期設定
    MTU21.TGRB = intr_cycle_read_sensors / 2; // ← いる？

    // MTU2 Ch.2
    // interrupt_control
    MTU2.TSTR.BIT.CST2 = 0;              // カウンタ停止
    MTU22.TCNT = 0;                      // カウンタリセット
    MTU22.TCR.BIT.CCLR = 1;              // TGRA_2 コンペアマッチ/インプットキャプチャでTCNTクリア
    MTU22.TCR.BIT.CKEG = 0;              // クロック立ち上がりエッジでカウント
    MTU22.TCR.BIT.TPSC = 0;              // クロック: MPφ/1 = 25 [MHz] = 40 [ns/count]
    MTU22.TMDR.BIT.MD = 2;               // MTU2 Ch.2 は PWMモード1
    MTU22.TIOR.BIT.IOA = 0x1;            // 初期出力 0; TGRAコンペアマッチで 0
    MTU22.TIOR.BIT.IOB = 0x2;            // 初期出力 0; TGRBコンペアマッチで 1
    MTU22.TIER.BYTE = 0x01;              // TGRAコンペアマッチで割り込み許可; それ以外は禁止
    MTU22.TGRA = intr_cycle_control;     // 割り込み周期設定
    MTU22.TGRB = intr_cycle_control / 2; // ← いる？

    // CMT0
    // interrupt_communicate
    CMT.CMSTR.BIT.STR0 = 0;              // カウンタ停止
    CMT0.CMCSR.BIT.CKS = 0;              // クロック: Pφ/8 = 3.125 [MHz] = 320 [ns/count]
    CMT0.CMCSR.BIT.CMIE = 1;             // コンペアマッチ割り込み許可
    CMT0.CMCNT = 0;                      // カウンタ値を0に
    CMT0.CMCOR = intr_cycle_communicate; // 割り込み周期設定
}

void start_interrupts(void)
{
    /*
     * MTU2
     *   Ch.0 角速度計算
     *   Ch.1 センサ値読み込み
     *   Ch.2 制御計算
     *   Ch.3 相補PWM
     *   Ch.4 相補PWM
     * CMT
     *   0 DA コンバータ制御
     */
    MTU2.TSTR.BIT.CST0 = 1; // MTU2 Ch.0 カウンタスタート
    MTU2.TSTR.BIT.CST1 = 1; // MTU2 Ch.1 カウンタスタート
    MTU2.TSTR.BIT.CST2 = 1; // MTU2 Ch.2 カウンタスタート
    CMT.CMSTR.BIT.STR0 = 1; // CMT0 カウンタスタート
}

void stop_interrupts(void)
{
    /*
     * MTU2
     *   Ch.0 角速度計算
     *   Ch.1 センサ値読み込み
     *   Ch.2 制御計算
     *   Ch.3 相補PWM
     *   Ch.4 相補PWM
     * CMT
     *   0 DA コンバータ制御
     */
    MTU2.TSTR.BIT.CST0 = 0; // MTU2 Ch.0 カウンタストップ
    MTU2.TSTR.BIT.CST1 = 0; // MTU2 Ch.1 カウンタストップ
    MTU2.TSTR.BIT.CST2 = 0; // MTU2 Ch.2 カウンタストップ
    CMT.CMSTR.BIT.STR0 = 0; // CMT0 カウンタストップ
}
