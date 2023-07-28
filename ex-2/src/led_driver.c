#include "led_driver.h"

// Private variables for this file
static uint16_t* ledAddress = NULL;
static uint16_t ledsImage;
enum{
    ALL_LEDS_ON = ~0,
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};
enum {
    FIRST_LED = 1,
    LAST_LED = 16
};

// Private functions for this file

/*
* Returns the bit for the corresponding ledNumber.
* Note that one is subtracted from ledNumber to
* start from bit 0. 
*/
static uint16_t convert_ledNumber_to_bit(int ledNumber){
    return (1 << (ledNumber-1));
}

static void update_hardware() {
    *ledAddress = ledsImage;
}

static bool is_led_OutOfBounds(int ledNumber){
    return ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED));
}

static void set_ledsImage_bit(int ledNumber){
    ledsImage |= convert_ledNumber_to_bit(ledNumber);
}

static void clear_ledsImage_bit(int ledNumber){
    ledsImage &= ~(convert_ledNumber_to_bit(ledNumber));
}

// Implementation of various LED drivers
void LedDriver_Create(uint16_t* address){
    ledAddress = address;
    ledsImage = ALL_LEDS_OFF;
    update_hardware();
}

void LedDriver_TurnAllOn() {
    ledsImage = ALL_LEDS_ON;
    update_hardware();
}

void LedDriver_TurnAllOff() {
    ledsImage = ALL_LEDS_OFF;
    update_hardware();
}

void LedDriver_TurnOn(int ledNumber) {
    if(is_led_OutOfBounds(ledNumber)){
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", 1);
        return;
    }

    set_ledsImage_bit(ledNumber);
    update_hardware();
}

void LedDriver_TurnOff(int ledNumber) {
    if(is_led_OutOfBounds(ledNumber)){
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", 1);
        return;
    }

    clear_ledsImage_bit(ledNumber);
    update_hardware();
}

bool LedDriver_IsOn(int ledNumber){
    if(is_led_OutOfBounds(ledNumber)){
        return false;
    }
    return (ledsImage & convert_ledNumber_to_bit(ledNumber));
}

bool LedDriver_IsOff(int ledNumber){
    // Going by the "Don't Repeat Yourself (DRY)" principle,
    // and not repeating ledsImage & convert_ledNumber_to_bit(ledNumber)
    return !LedDriver_IsOn(ledNumber);
}

void LedDriver_Destroy(void) {
    
}