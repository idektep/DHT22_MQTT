#ifndef LED_H
#define LED_H

class LED
{
public:
    void ledpinsetup();
    void led_on(int d);
    void led_off(int d);
    void led_blink(int d);
};
#endif





