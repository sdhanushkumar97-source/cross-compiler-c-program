#include <stdio.h>
#include <mraa.h>

#define I2C_BUS 1
#define DEVICE_ADDR 0x38

int main()
{
    mraa_i2c_context i2c;
    int data;

    // Initialize I2C bus
    i2c = mraa_i2c_init(I2C_BUS);

    if (i2c == NULL)
    {
        printf("Failed to initialize I2C\n");
        return 1;
    }

    // Set I2C device address
    if (mraa_i2c_address(i2c, DEVICE_ADDR) != MRAA_SUCCESS)
    {
        printf("Failed to set I2C address\n");
        mraa_i2c_stop(i2c);
        return 1;
    }

    // Try to communicate with the device
    data = mraa_i2c_read_byte(i2c);

    if (data < 0)
    {
        printf("Device Not Found\n");
    }
    else
    {
        printf("Device Found\n");
    }

    // Close I2C
    mraa_i2c_stop(i2c);

    return 0;
}
