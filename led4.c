#include <stdio.h>
#include <mraa/gpio.h>
#include <unistd.h>

int main()
{
    mraa_gpio_context led;
    mraa_gpio_context button;

    int press_count = 0;
    int previous_state = 1;
    int button_state;

    /* Initialize onboard LED and switch */
    led = mraa_gpio_init(61);       // Onboard LED - change if your board mapping differs
    button = mraa_gpio_init(35);    // Onboard switch - use correct MRAA mapping

    if (led == NULL || button == NULL)
    {
        printf("GPIO initialization failed\n");
        return 1;
    }

    mraa_gpio_dir(led, MRAA_GPIO_OUT);
    mraa_gpio_dir(button, MRAA_GPIO_IN);

    /* LED initially OFF */
    mraa_gpio_write(led, 0);

    printf("LED Switch Program Started\n");

    while (1)
    {
        button_state = mraa_gpio_read(button);

        /* Detect button press */
        if (button_state == 0 && previous_state == 1)
        {
            press_count++;

            printf("Switch pressed: %d time(s)\n", press_count);

            /*
             * 1st press  -> toggle 1 time
             * 2nd press -> toggle 2 times
             * 3rd press -> toggle 3 times
             * ...
             */
            for (int i = 0; i < press_count; i++)
            {
                int current = mraa_gpio_read(led);
                mraa_gpio_write(led, !current);

                usleep(200000);
            }

            printf("LED toggled %d time(s)\n", press_count);

            /* Wait until button is released */
            while (mraa_gpio_read(button) == 0)
            {
                usleep(10000);
            }
        }

        previous_state = button_state;

        usleep(10000);
    }

    mraa_gpio_close(led);
    mraa_gpio_close(button);

    return 0;
}
