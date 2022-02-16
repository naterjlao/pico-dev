

#include "pico/stdlib.h"
#include "segments_decoder.h"

static void display_init(void)
{
    // ----- SOURCE ------ //
    gpio_init(LED_PIN_A );
    gpio_init(LED_PIN_B );
    gpio_init(LED_PIN_C );
    gpio_init(LED_PIN_D );
    gpio_init(LED_PIN_E );
    gpio_init(LED_PIN_F );
    gpio_init(LED_PIN_G );
    gpio_init(LED_PIN_DP);
    gpio_init(LED_PIN_COLON);

    // ----- SINK ----- //
    for (uint digit = 0; digit < DIGIT_SOURCE_LEN; digit++)
    {
        gpio_init(DIGIT_SOURCE[digit]);
    }
    gpio_init(COLON_SOURCE);
}

static void gpio_pull_up_down(uint gpio, bool state)
{
    if (state)
    {
        gpio_pull_up(gpio);
    }
    else
    {
        gpio_pull_down(gpio);
    }
}

static void display_clear(bool on)
{
    gpio_pull_up_down(LED_PIN_A    , on);
    gpio_pull_up_down(LED_PIN_B    , on);
    gpio_pull_up_down(LED_PIN_C    , on);
    gpio_pull_up_down(LED_PIN_D    , on);
    gpio_pull_up_down(LED_PIN_E    , on);
    gpio_pull_up_down(LED_PIN_F    , on);
    gpio_pull_up_down(LED_PIN_G    , on);
    gpio_pull_up_down(LED_PIN_DP   , on);
    gpio_pull_up_down(LED_PIN_COLON, on);
    for (uint digit = 0; digit < DIGIT_SOURCE_LEN; digit++)
    {
        gpio_pull_up_down(DIGIT_SOURCE[digit], (!on));
    }
    gpio_pull_up_down(COLON_SOURCE, (!on));
}

static void display_digit(unsigned char digit, unsigned char idx)
{
    unsigned char hex = HEX_SEGMENT_LOOKUP[digit % HEX_SEGMENT_LOOKUP_LEN];

    gpio_pull_up_down(LED_PIN_A , (hex & LED_PIN_A_MASK ));
    gpio_pull_up_down(LED_PIN_B , (hex & LED_PIN_B_MASK ));
    gpio_pull_up_down(LED_PIN_C , (hex & LED_PIN_C_MASK ));
    gpio_pull_up_down(LED_PIN_D , (hex & LED_PIN_D_MASK ));
    gpio_pull_up_down(LED_PIN_E , (hex & LED_PIN_E_MASK ));
    gpio_pull_up_down(LED_PIN_F , (hex & LED_PIN_F_MASK ));
    gpio_pull_up_down(LED_PIN_G , (hex & LED_PIN_G_MASK ));
    gpio_pull_up_down(LED_PIN_DP, (hex & LED_PIN_DP_MASK));

    for (uint digit_idx = 0; digit_idx < DIGIT_SOURCE_LEN; digit_idx++)
    {
        gpio_pull_up_down(DIGIT_SOURCE[digit_idx], (!(digit_idx == idx)));
        //gpio_pull_up_down(DIGIT_SOURCE[digit_idx], (!(digit_idx == idx)));
    }
}

int main() {

    display_init();
    display_clear(true);

    uint counter = 0;
    uint tick = 0;

    while (true)
    {   
        display_digit(((counter/1000) % 10) ,0);
        sleep_ms(1);
        display_digit(((counter/100) % 10),1);
        sleep_ms(1);
        display_digit(((counter/10) % 10),2);
        sleep_ms(1);
        display_digit(((counter/1) % 10),3);
        sleep_ms(1);

        /// @todo use interrupt instead
        if (tick > 100)
        {
            tick = 0;
            counter++;
            if (counter > 9999)
            {
                counter = 0;
            }
        } else
        {
            tick++;
        }
        
    }
}
