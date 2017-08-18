#ifndef SPI_H
#define SPI_H

#include "system.h"
#include "gpio.h"

class SPI
{
public:
  enum
  {
    INITIALIZATION = 256,
    SLOW           = 128, //00.65625 MHz
    STANDARD       = 8,   //10.50000 MHz
    FAST           = 4,   //21.00000 MHz
    ULTRAFAST      = 2    //42.00000 MHz
  };
  SPI(spi_configuration_t config);
  void init();

  bool transfer(uint8_t* out, uint32_t len, uint8_t* in);
  bool is_busy();

  uint32_t get_error_count();
  void set_divisor(uint16_t divisor);
  void set_ss_low();
  void set_ss_high();
  void send(uint8_t address, uint8_t data);
  void receive(uint8_t start_address, uint8_t length, uint8_t *data_out);

private:
  GPIO nss_;

  SPI_TypeDef* dev;

  bool leading_edge;
  bool using_nss;
  uint32_t error_count;
};

#endif // SPI_H