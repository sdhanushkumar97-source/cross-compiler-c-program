#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int read_adc(int channel)
{
    char path[128];
    char value_str[32];
    int fd;
    ssize_t len;

    snprintf(path, sizeof(path),
             "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",
             channel);

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open ADC file");
        return -1;
    }

    len = read(fd, value_str, sizeof(value_str) - 1);

    if (len < 0) {
        perror("Failed to read ADC value");
        close(fd);
        return -1;
    }

    close(fd);

    value_str[len] = '\0';

    return atoi(value_str);
}

int main(int argc, char *argv[])
{
    int channel;
    int value;

    if (argc != 2) {
        printf("Usage: %s <adc_channel>\n", argv[0]);
        return 1;
    }

    channel = atoi(argv[1]);

    printf("Reading ADC Channel %d...\n", channel);

    while (1) {
        value = read_adc(channel);

        if (value >= 0) {
            printf("ADC Channel %d Value: %d\n",
                   channel, value);
        }

        usleep(500000);  // 500 ms
    }

    return 0;
}
