#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ADC_CHANNEL 0
#define THRESHOLD   2000

#define LED_PATH "/sys/class/leds/led0/brightness"

int read_adc(int channel)
{
    char path[128];
    char value_str[32];
    int fd;
    int len;

    snprintf(path, sizeof(path),
             "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",
             channel);

    fd = open(path, O_RDONLY);

    if (fd < 0) {
        perror("ADC open failed");
        return -1;
    }

    len = read(fd, value_str, sizeof(value_str) - 1);

    close(fd);

    if (len <= 0) {
        perror("ADC read failed");
        return -1;
    }

    value_str[len] = '\0';

    return atoi(value_str);
}

void led_on(void)
{
    int fd;

    fd = open(LED_PATH, O_WRONLY);

    if (fd < 0) {
        perror("LED open failed");
        return;
    }

    write(fd, "1", 1);

    close(fd);
}

void led_off(void)
{
    int fd;

    fd = open(LED_PATH, O_WRONLY);

    if (fd < 0) {
        perror("LED open failed");
        return;
    }

    write(fd, "0", 1);

    close(fd);
}

int main(void)
{
    int adc_value;

    printf("ADC LED program started\n");

    while (1)
    {
        adc_value = read_adc(ADC_CHANNEL);

        if (adc_value < 0)
            continue;

        printf("ADC = %d ", adc_value);

        if (adc_value >= THRESHOLD)
        {
            printf("LED ON\n");

            led_on();

            sleep(1);

            printf("LED OFF\n");

            led_off();

            sleep(1);
        }
        else
        {
            printf("LED OFF\n");

            led_off();

            usleep(500000);
        }
    }

    return 0;
}
