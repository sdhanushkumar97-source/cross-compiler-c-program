#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GPIO_EXPORT "/sys/class/gpio/export"
#define LED_DIR     "/sys/class/gpio/PC23/direction"
#define LED_VALUE   "/sys/class/gpio/PC23/value"

#define GPIO_NUM 87

int main()
{
    int fd;
    char gpio_buf[10];
    int count = 20;

    /* Export GPIO */
    fd = open(GPIO_EXPORT, O_WRONLY);
    if (fd < 0)
    {
        perror("Unable to open GPIO export");
        return 1;
    }

    sprintf(gpio_buf, "%d", GPIO_NUM);

    if (write(fd, gpio_buf, strlen(gpio_buf)) < 0)
    {
        perror("Unable to export GPIO");
        close(fd);
        return 1;
    }

    close(fd);

    /* Set GPIO direction as output */
    fd = open(LED_DIR, O_WRONLY);
    if (fd < 0)
    {
        perror("Unable to open GPIO direction");
        return 1;
    }

    if (write(fd, "out", 3) < 0)
    {
        perror("Unable to set GPIO direction");
        close(fd);
        return 1;
    }

    close(fd);

    /* Open GPIO value */
    fd = open(LED_VALUE, O_WRONLY);
    if (fd < 0)
    {
        perror("Unable to open GPIO value");
        return 1;
    }

    printf("LED blinking on PC13...\n");

    /* Blink LED 20 times */
    while (count--)
    {
        /* LED ON */
        write(fd, "1", 1);
        printf("LED ON\n");
        usleep(500000);

        /* LED OFF */
        write(fd, "0", 1);
        printf("LED OFF\n");
        usleep(500000);
    }

    /* Turn LED OFF before exit */
    write(fd, "0", 1);

    close(fd);

    printf("Blinking completed.\n");

    return 0;
}
