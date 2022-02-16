

#include "pico/stdlib.h"
#include "segment_decoder.h"

static void display_init(void)
{
    gpio_init(LED_PIN_A );
    gpio_init(LED_PIN_B );
    gpio_init(LED_PIN_C );
    gpio_init(LED_PIN_D );
    gpio_init(LED_PIN_E );
    gpio_init(LED_PIN_F );
    gpio_init(LED_PIN_G );
    gpio_init(LED_PIN_DP);
}

static void display_clear(void)
{
    gpio_pull_up(LED_PIN_A );
    gpio_pull_up(LED_PIN_B );
    gpio_pull_up(LED_PIN_C );
    gpio_pull_up(LED_PIN_D );
    gpio_pull_up(LED_PIN_E );
    gpio_pull_up(LED_PIN_F );
    gpio_pull_up(LED_PIN_G );
    gpio_pull_up(LED_PIN_DP);
}

static void display_digit(unsigned char digit)
{
    unsigned char hex = HEX_SEGMENT_LOOKUP[digit];

    if (hex & LED_PIN_A_MASK) { gpio_pull_down(LED_PIN_A); } else { gpio_pull_up(LED_PIN_A); }
    if (hex & LED_PIN_B_MASK) { gpio_pull_down(LED_PIN_B); } else { gpio_pull_up(LED_PIN_B); }
    if (hex & LED_PIN_C_MASK) { gpio_pull_down(LED_PIN_C); } else { gpio_pull_up(LED_PIN_C); }
    if (hex & LED_PIN_D_MASK) { gpio_pull_down(LED_PIN_D); } else { gpio_pull_up(LED_PIN_D); }
    if (hex & LED_PIN_E_MASK) { gpio_pull_down(LED_PIN_E); } else { gpio_pull_up(LED_PIN_E); }
    if (hex & LED_PIN_F_MASK) { gpio_pull_down(LED_PIN_F); } else { gpio_pull_up(LED_PIN_F); }
    if (hex & LED_PIN_G_MASK) { gpio_pull_down(LED_PIN_G); } else { gpio_pull_up(LED_PIN_G); }
    if (hex & LED_PIN_DP_MASK) { gpio_pull_down(LED_PIN_DP); } else { gpio_pull_up(LED_PIN_DP); }
}

int main() {

    display_init();
    display_clear();

    unsigned char digit = 0;

    while (true)
    {
        display_digit(digit);
        sleep_ms(1000);
        digit++;
        digit=digit % 10;
    }
}
