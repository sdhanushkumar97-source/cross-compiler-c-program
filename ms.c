#include <stdio.h>
#include <unistd.h>
#include <mraa/i2c.h>

#define BUS 0
#define ADDR 0x68

int main()
{
    mraa_i2c_context i2c;
    unsigned char cmd[2];
    unsigned char data[6];
    short ax, ay, az;

    i2c = mraa_i2c_init(BUS);

    if (i2c == NULL)
        return 1;

    mraa_i2c_address(i2c, ADDR);

    /* Wake up MPU6050 */
    cmd[0] = 0x6B;
    cmd[1] = 0x00;

    if (mraa_i2c_write(i2c, cmd, 2) != MRAA_SUCCESS)
    {
        printf("I2C write failed\n");
        return 1;
    }

    while (1)
    {
        /* Start reading accelerometer */
        cmd[0] = 0x3B;

        mraa_i2c_write(i2c, cmd, 1);
        mraa_i2c_read(i2c, data, 6);

        ax = (data[0] << 8) | data[1];
        ay = (data[2] << 8) | data[3];
        az = (data[4] << 8) | data[5];

        printf("X: %d  Y: %d  Z: %d\n", ax, ay, az);

        sleep(1);
    }

    mraa_i2c_stop(i2c);

    return 0;
}
