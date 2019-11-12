#include "iodefine.h"
#include "da_handler.h"

#define SPI_CS PB.DR.BIT.B1
#define SPI_SCK PB.DR.BIT.B2
#define SPI_SDI1 PB.DR.BIT.B3
#define SPI_SDI2 PB.DR.BIT.B5

void init_da_handler(void)
{
    SPI_CS = 1;
    SPI_SCK = 0;
    SPI_SDI1 = 0;
    SPI_SDI2 = 0;
    PB.DR.BIT.B16 = 1; // LDAC HIGH
}

void send_da_data(const unsigned short data1,
                  const unsigned short data2,
                  const unsigned short data3,
                  const unsigned short data4)
{
    int bit; // データ転送処理用変数

    SPI_CS = 0;

    /**************************
     * Ch. A                  *
     **************************/

    // Config - A/B Select bit => A
    SPI_SCK = 0;
    SPI_SDI1 = 0;
    SPI_SDI2 = 0;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Vref Input Buffer Control bit => Buffered
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Output Gain Select bit => 1x
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Output Power Down Control bit => Output Enabled
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Data - 11, 10, ..., 0 bit
    for (bit = 11; 0 <= bit; bit--)
    {
        SPI_SCK = 0;
        SPI_SDI1 = (data1 >> bit) & 0x0001;
        SPI_SDI2 = (data3 >> bit) & 0x0001;
        SPI_SCK = 1;

        // MCP4922 Reads
    }

    /**************************
     * Ch. B                  *
     **************************/

    // Config - A/B Select bit => B
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Vref Input Buffer Control bit => Buffered
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Output Gain Select bit => 1x
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Config - Output Power Down Control bit => Output Enabled
    SPI_SCK = 0;
    SPI_SDI1 = 1;
    SPI_SDI2 = 1;
    SPI_SCK = 1;

    // MCP4922 Reads

    // Data - 11, 10, ..., 0 bit
    for (bit = 11; 0 <= bit; bit--)
    {
        SPI_SCK = 0;
        SPI_SDI1 = (data2 >> bit) & 0x0001;
        SPI_SDI2 = (data4 >> bit) & 0x0001;
        SPI_SCK = 1;

        // MCP4922 Reads
    }

    // Unselect MCP4922
    SPI_SCK = 0;
    SPI_CS = 1;
    SPI_SDI1 = 0;
    SPI_SDI2 = 0;

    // Command update output voltage
    PB.DR.BIT.B16 = 0;
    PB.DR.BIT.B16 = 1;
}
