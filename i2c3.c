#include <stdio.h>
#include <unistd.h>
#include <mraa/i2c.h>

#define BUS 0
#define ADDR 0x38

int main()
{
    mraa_i2c_context i2c;
    unsigned char init_cmd[3] = {0xBE, 0x08, 0x00};
    unsigned char measure_cmd[3] = {0xAC, 0x33, 0x00};
    unsigned char data[6];
    int raw_temp;
    float temperature;

    i2c = mraa_i2c_init(BUS);

    if (i2c == NULL) {
        printf("I2C initialization failed\n");
        return 1;
    }

    mraa_i2c_address(i2c, ADDR);

    /* Initialize AHT25 */
    if (mraa_i2c_write(i2c, init_cmd, 3) != MRAA_SUCCESS) {
        printf("Initialization failed\n");
        mraa_i2c_stop(i2c);
        return 1;
    }

    usleep(10000);

    /* Start measurement */
    if (mraa_i2c_write(i2c, measure_cmd, 3) != MRAA_SUCCESS) {
        printf("Measurement command failed\n");
        mraa_i2c_stop(i2c);
        return 1;
    }

    usleep(80000);

    /* Read 6 bytes */
    if (mraa_i2c_read(i2c, data, 6) != 6) {
        printf("Sensor read failed\n");
        mraa_i2c_stop(i2c);
        return 1;
    }

    /* Temperature raw value */
    raw_temp = ((data[3] & 0x0F) << 16) |
               (data[4] << 8) |
                data[5];

    /* Convert to Celsius */
    temperature = ((float)raw_temp * 200.0 / 1048576.0) - 50.0;

    printf("Temperature: %.2f C\n", temperature);

    mraa_i2c_stop(i2c);

    return 0;
}
