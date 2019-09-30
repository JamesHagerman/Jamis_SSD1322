# yellow-tft-display

This is a port of the Adafruit_SSD1306 library to the SSD1322 TFT display chip using the hardware SPI library on the Particle Xenon and other Gen3 devices.

The intent is to allow the Adafruit_GFX library to be used to draw content on displays with this chip.

The SSD1322 supports 3SPI and 4SPI modes (along with 8080 and 6800 modes). This library was developed with a display configured in the 4SPI mode.

## Compiling

Particle Workbench was used to develop this library. Loading this project from Workbench and compiling either using the `>Particle: Cloud Compile` or `>Particle: Compile application (local)` option is likely the easiest approach.

This project was written using version `1.4.0` of the Particle Device OS.

Be aware of needing to run `>Particle: Clean application (local)` in some cases otherwise you may get unexpected results

## Hardware setup

This project was developed using a Particle Xenon. 7 pins on the display were connected back to the Xenon as follows.

*Note: The datahseet is more specific about what pins should be tied to GND than these wirings. It is suggested to follow the datasheet for projects with reliabiltiy concerns.*

```
,---------------------------------------------------------,
| Pin | Fn     | Notes                      | Xenon       |
|-----+--------+----------------------------+-------------+
|   1 | VSS    | Ground.                    | GND         |
|   2 | VBAT   | Power (3.3-5V).            | +3.3V       |
|   3 | NC     | Leave floating.            | -           |
|   4 | DB0    | SPI SCLK                   | SCK/13      |
|   5 | DB1    | SPI SDIN                   | MOSI/12     |
|   6 | DB2    | Leave floating.            | -           |
|   7 | DB3    | -                          | -           |
|   8 | DB4    | -                          | -           |
|   9 | DB5    | -                          | -           |
|  10 | DB6    | -                          | -           |
|  11 | DB7    | -                          | -           |
|  12 | /RD    | -                          | -           |
|  13 | /WR    | -                          | -           |
|  14 | /DC    | Data/Command for 4-wire.   | TX/9        |
|  15 | /RESET | Power Reset.               | RX/10       |
|  16 | /CS    | SPI Chip Select.           | SS/A5/14    |
'---------------------------------------------------------'
```

The `/DC`, `/RESET`, and `/CS` pins can likely be changed to other unused pin. This has not been tested.

The datasheet expects the SPI bus to be run at `10MHz`. The display seemed to work at `20MHz` but these speeds are misleading. The SPI bus on Particle Gen 3 devices only operate at certain clock divisions: 32, 16, 8, and so on. Configuring the bus to `10MHz` means it is falling back to `8MHz`.

It did not work at `32MHz` so `16MHz` is likely the fastest we can achieve with the Xenon.



