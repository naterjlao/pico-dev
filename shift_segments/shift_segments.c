
#include <string.h>
//#include "stdio.h"
#include "pico/stdlib.h"
#include "shift_segments.h"

const unsigned int COLON_PIN = 18;

const unsigned int D1_PIN = 16;
const unsigned int D2_PIN = 12;
const unsigned int D3_PIN = 11;
const unsigned int D4_PIN = 17;

const unsigned int CLOCK_PIN = 13;
const unsigned int LATCH_PIN = 14;
const unsigned int DATA_PIN = 15;

/// This gets updated in runtime
static unsigned char SHIFT_REG_LOOKUP[10];
// ----------------------------------------------------------------------------
/// @brief Initializes the lookup table for the shift register.
///
/// @details The SHIFT_REG_MAPPING array contains the bit mask for each output 
/// pin of the shift register. This is ordered in respect to shift register
/// output index:
/// @code
/// SHIFT_REG_MAPPING = {OUT_0_MASK, OUT_1_MASK, ..., OUT_7_MASK}
/// @endcode
/// The HEX_SEGMENT_LOOKUP contains the LED configuration for the active
/// LED for each digit in the 7 segment display:
/// @code
/// 0x80 = DP
/// 0x40 = A
/// 0x20 = B
/// 0x10 = C
/// 0x08 = D
/// 0x04 = E
/// 0x02 = F
/// 0x01 = G
/// @endcode
/// This function converts the HEX_SEGMENT_LOOKUP and generates the
/// SHIFT_REG_LOOKUP table based on the SHIFT_REG_MAPPING table.
///
/// @todo add parameter input
// ----------------------------------------------------------------------------
void initialize_shift_reg_lookup(void)
{
    unsigned char buffer, bit;
    int digit_idx, map_idx;

    memset(SHIFT_REG_LOOKUP,0,sizeof(SHIFT_REG_LOOKUP));
    
    digit_idx = 0;
    while (digit_idx < 10)
    {
        buffer = 0;
        map_idx = 0;
        bit = 0x8;
        while (map_idx < 8)
        {
            if (HEX_SEGMENT_LOOKUP[digit_idx] & SHIFT_REG_MAPPING[map_idx])
                buffer |= bit;
            bit = bit >> 1;
            map_idx++;
        }
        SHIFT_REG_LOOKUP[digit_idx] = buffer;
        digit_idx++; 
    }
}

void initialize_gpio(void)
{
    gpio_init(CLOCK_PIN);
    gpio_init(LATCH_PIN);
    gpio_init(DATA_PIN);
    gpio_init(D1_PIN);
    gpio_init(D2_PIN);
    gpio_init(D3_PIN);
    gpio_init(D4_PIN);
}

/// @param digit number 0-9
void load_digit(const unsigned char digit)
{
    const unsigned char sr_hex = SHIFT_REG_LOOKUP[digit];
    unsigned char mask;

    /// Set Load Data - Set Latch Down
    gpio_pull_down(CLOCK_PIN);
    gpio_pull_down(LATCH_PIN);
    gpio_pull_up(CLOCK_PIN);

    /// Load Data - Set Data Pin HI or LO
    /// Order: OUT_0_BIT | OUT_2_BIT | ... | OUT_7_BIT
    mask = 0x8;
    while (mask > 0)
    {
        gpio_pull_up(CLOCK_PIN);
        if (sr_hex & mask)
            gpio_pull_up(DATA_PIN);
        else
            gpio_pull_down(DATA_PIN);
        gpio_pull_down(CLOCK_PIN);
        mask = mask >> 1;
    }

    // Output Enable - Set Latch Up
    gpio_pull_down(CLOCK_PIN);
    gpio_pull_up(LATCH_PIN);
    gpio_pull_up(CLOCK_PIN);
}

int main(void)
{
    initialize_shift_reg_lookup();
    initialize_gpio();

    

#if 1
    gpio_pull_down(D1_PIN);
    gpio_pull_up(D2_PIN);
    gpio_pull_up(D3_PIN);
    gpio_pull_up(D4_PIN);

    load_digit(0);

#if 0
    int idx = 0;
    while (true)
    {
        load_digit(idx++);
        idx = idx % 10;
        sleep_ms(250);
    }
#endif
#else
    gpio_init(COLON_PIN);
    gpio_init(CLOCK_PIN);
    gpio_init(LATCH_PIN);
    gpio_init(DATA_PIN);
    gpio_init(D1_PIN);
    gpio_init(D2_PIN);
    gpio_init(D3_PIN);
    gpio_init(D4_PIN);

    unsigned int random = 0;
    while (true)
    {

        gpio_pull_down(CLOCK_PIN);
        gpio_pull_down(LATCH_PIN);
        gpio_pull_up(CLOCK_PIN);

        for (int i = 0; i < 8; i++)
        {
            gpio_pull_up(CLOCK_PIN);
            if (random % 2)
                gpio_pull_up(DATA_PIN);
            else
                gpio_pull_down(DATA_PIN);
            gpio_pull_down(CLOCK_PIN);
        }

        gpio_pull_down(CLOCK_PIN);
        gpio_pull_up(LATCH_PIN);
        gpio_pull_up(CLOCK_PIN);

        // Cycle through digits

        gpio_pull_up(D1_PIN);
        gpio_pull_up(D2_PIN);
        gpio_pull_up(D3_PIN);
        gpio_pull_up(D4_PIN);
        switch (random)
        {
        case 1:
            gpio_pull_down(D1_PIN);
            break;
        case 2:
            gpio_pull_down(D2_PIN);
            break;
        case 3:
            gpio_pull_down(D3_PIN);
            break;
        case 4:
            gpio_pull_down(D4_PIN);
            break;
        }

        // Colon
        if (random % 2)
            gpio_pull_up(COLON_PIN);
        else
            gpio_pull_down(COLON_PIN);


        random = random % 4;
        random++;
        sleep_ms(250);
    }
    
#endif
    return 0;
}

#if 0
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
    for (unsigned int digit = 0; digit < DIGIT_SOURCE_LEN; digit++)
    {
        gpio_init(DIGIT_SOURCE[digit]);
    }
    gpio_init(COLON_SOURCE);
}

static void gpio_pull_up_down(unsigned int gpio, bool state)
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
    for (unsigned int digit = 0; digit < DIGIT_SOURCE_LEN; digit++)
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

    for (unsigned int digit_idx = 0; digit_idx < DIGIT_SOURCE_LEN; digit_idx++)
    {
        gpio_pull_up_down(DIGIT_SOURCE[digit_idx], (!(digit_idx == idx)));
        //gpio_pull_up_down(DIGIT_SOURCE[digit_idx], (!(digit_idx == idx)));
    }
}

int main() {

    display_init();
    display_clear(true);

    unsigned int counter = 0;
    unsigned int tick = 0;

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
#endif