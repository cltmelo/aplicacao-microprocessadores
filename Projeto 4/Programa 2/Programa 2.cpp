#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_PIN_R 15  
#define LED_PIN_G 16  
#define LED_PIN_B 17  

#define LEDC_TIMER           LEDC_TIMER_0
#define LEDC_MODE            LEDC_LOW_SPEED_MODE
#define LEDC_FREQUENCY      5000  
#define LEDC_RESOLUTION      LEDC_TIMER_8_BIT  
#define LEDC_CHANNEL_R       LEDC_CHANNEL_0
#define LEDC_CHANNEL_G       LEDC_CHANNEL_1
#define LEDC_CHANNEL_B       LEDC_CHANNEL_2

void app_main() {
    gpio_set_direction(LED_PIN_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_G, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_B, GPIO_MODE_OUTPUT);

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_RESOLUTION,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_USE_PLL
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel_r = {
        .gpio_num = LED_PIN_R,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_R,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel_r);

    ledc_channel_config_t ledc_channel_g = {
        .gpio_num = LED_PIN_G,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_G,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel_g);

    ledc_channel_config_t ledc_channel_b = {
        .gpio_num = LED_PIN_B,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_B,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel_b);

    uint8_t incremento = 0;
    while (1) {
        uint32_t duty_r = incremento * 2;
        uint32_t duty_g = incremento;
        uint32_t duty_b = incremento * 3;

        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_R, duty_r);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_G, duty_g);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, duty_b);

        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_R);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_G);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);

        ESP_LOGI("PWM", "Incremento: %d", incremento);
        ESP_LOGI("PWM", "Duty cycle - R: %d%%, G: %d%%, B: %d%%", duty_r * 100 / 255, duty_g * 100 / 255, duty_b * 100 / 255);

        incremento += 5;
        if (incremento > 255) {
            incremento = 0;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}