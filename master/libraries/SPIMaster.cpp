#include "SPIMaster.h"

SPIMaster::SPIMaster(spi_inst_t *spi, uint TXPin, uint RXPin, uint SCKPin, uint CSNPin)
{
    this->spi = spi;
    this->TXPin = TXPin;
    this->RXPin = RXPin;
    this->SCKPin = SCKPin;
    this->CSNPin = CSNPin;
}

void SPIMaster::MasterInit()
{
    
    spi_init(spi, BAUD_RATE);
    //spi_set_slave(spi1, false);
    spi_set_format(spi, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST);

    // Initalize GPIO
    gpio_set_function(TXPin, GPIO_FUNC_SPI);
    gpio_set_function(RXPin, GPIO_FUNC_SPI);
    gpio_set_function(SCKPin, GPIO_FUNC_SPI);
    gpio_set_function(CSNPin, GPIO_FUNC_SPI); // Comment? May not need decoder w/ with CHPA=1 (for prototype)
}

void SPIMaster::MasterRead(uint8_t *out_buf, uint8_t *in_buf, size_t len)
{
    spi_write_read_blocking(spi, out_buf, in_buf, len);
}

void SPIMaster::SlaveSelect(uint8_t CSN)
{
    // Place each bit of CSN on the appropriate pins to send to decoder
    // This assumes the start pin is the little-end
    for(uint8_t i = CSN_START_PIN; i <= CSN_END_PIN; i++)
    {
        gpio_put(i, 0xFE & (CSN >> (i - CSN_START_PIN)));
    }
}




