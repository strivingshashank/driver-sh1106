#include "onboard_led.h"

#include <pico/cyw43_arch.h>

#define ONBOARD_LED_PIN CYW43_WL_GPIO_LED_PIN

bool onboard_led_toggle(void) {
        bool led_is_on = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        
        if (led_is_on) {
                cyw43_arch_gpio_put(ONBOARD_LED_PIN, 0);
        } else {
                cyw43_arch_gpio_put(ONBOARD_LED_PIN, 1);
        }

        return led_is_on;
}

void onboard_led_on(void) {
        cyw43_arch_gpio_put(ONBOARD_LED_PIN, 1);
}

void onboard_led_off(void) {
        cyw43_arch_gpio_put(ONBOARD_LED_PIN, 0);
}