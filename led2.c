
#include <unistd.h>
#include <stdio.h>
#include <mraa/gpio.h>
int main()
{
mraa_gpio_context led;

led = mraa_gpio_init(45);
if (led == NULL)
{
printf("Failed to initialize GPIO 61\n");
return 1;
}

if (mraa_gpio_dir(led, MRAA_GPIO_OUT) != MRAA_SUCCESS)
{
printf("Failed to set GPIO direction\n");
mraa_gpio_close(led);
return 1;
}
printf("LED blinking on GPIO 61...\n");

while (1)
{

mraa_gpio_write(led, 0);
usleep(500000); 
mraa_gpio_write(led, 1);
usleep(500000); 
}

mraa_gpio_close(led);
return 0;
}
