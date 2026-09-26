
#include <stdio.h>
#include <unistd.h>
#include <mraa.h>
#define PWM_PIN 72 
#define PWM_PERIOD 20 
int main() {
mraa_pwm_context pwm;
float output;
pwm = mraa_pwm_init(PWM_PIN);
if (pwm == NULL) {
printf("Failed to initialize PWM\n");
return 1;
}

mraa_pwm_period_ms(pwm, PWM_PERIOD);
mraa_pwm_enable(pwm, 1);
float value = 1.0;
while (1) {

mraa_pwm_write(pwm, value);
usleep(70000);
value -= 0.01;
if (value <= 0.0)
value = 1;

output = mraa_pwm_read(pwm);
printf("PWM value : %f\n", output);
}
mraa_pwm_enable(pwm, 0);
mraa_pwm_close(pwm);
return 0;
}
