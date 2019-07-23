//Include
//------------------------------------------------------------------//
#include <M5Stack.h>
#include <NeoPixelBus.h>



//Define
//------------------------------------------------------------------//
#define colorSaturation 255
#define BUTTON1_PIN 21
#define BUTTON2_PIN 22
#define BUTTON3_PIN 23
#define BUTTON4_PIN 19

#define BUTTON_A_PIN 39
#define BUTTON_B_PIN 38
#define BUTTON_C_PIN 37

//Global
//------------------------------------------------------------------//


RgbColor red(colorSaturation, 0, 0);
RgbColor yellow(240, 255, 0);
RgbColor green(0, 255, 0);
RgbColor blue(0, 0, 255);
RgbColor aqua(0, 204, 255);
RgbColor white(colorSaturation);
RgbColor pink(255,0,153);
RgbColor black(0);


const uint16_t PixelCount = 16; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 18;  // make sure to set this to the correct pin, ignored for Esp8266
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

boolean button1_status = 1;
boolean button2_status = 1;
boolean button3_status = 1;
boolean button4_status = 1;

boolean buttonA_status = 1;
boolean buttonB_status = 1;
boolean buttonC_status = 1;

boolean ans_flag = 0;
boolean TF_flag = 0;

unsigned char pattern = 0;
unsigned char active_team = 0;


//Global
//------------------------------------------------------------------//



//Setup
//------------------------------------------------------------------//
void setup()
{

    //M5.begin();
    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();

    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);

    pinMode(BUTTON_A_PIN, INPUT);
    pinMode(BUTTON_B_PIN, INPUT);
    pinMode(BUTTON_C_PIN, INPUT);

}

//Main
//------------------------------------------------------------------//

void loop()
{

    switch ( pattern ) {
    case 0:
        button1_status = digitalRead( BUTTON1_PIN );
        button2_status = digitalRead( BUTTON2_PIN );
        button3_status = digitalRead( BUTTON3_PIN );
        button4_status = digitalRead( BUTTON4_PIN );
        if ( button1_status == 0 ) {
            pattern = 11;
        } else if ( button2_status == 0 ) {
            pattern = 21;
        } else if ( button3_status == 0 ) {
            pattern = 31;
        } else if ( button4_status == 0 ) {
            pattern = 41;
        }
        break;

    case 11:
        strip.ClearTo( pink, 0, 3);
        strip.Show();
        active_team = 1;
        pattern = 51;
        break;

    case 21:
        strip.ClearTo( aqua, 4, 7);
        strip.Show();
        active_team = 2;
        pattern = 51;
        break;

    case 31:
        strip.ClearTo( green, 8, 11);
        strip.Show();
        active_team = 3;
        pattern = 51;
        break;

    case 41:
        strip.ClearTo( yellow, 12, 15);
        strip.Show();
        active_team = 4;
        pattern = 51;
        break;

    case 51:
        buttonA_status = digitalRead( BUTTON_A_PIN );
        buttonB_status = digitalRead( BUTTON_B_PIN );
        buttonC_status = digitalRead( BUTTON_C_PIN );
        if ( buttonA_status == 0 ) {
            TF_flag = 1;
            pattern = 61;
            break;
        } else if ( buttonB_status == 0 ) {
            TF_flag = 0;
            pattern = 61;
            break;
        } else if ( buttonC_status == 0 ) {
            pattern = 71;
        }
        break;

    case 61:
        if( TF_flag ) {
            for(int i=0; i<=5; i++) {
                strip.ClearTo( blue, 4 * active_team - 4, 4 * active_team - 1);
                strip.Show();
                delay(100);
                strip.ClearTo( 0, 4 * active_team - 4, 4 * active_team - 1);
                strip.Show();
                delay(100);
            }
        } else {
            for(int i=0; i<=5; i++) {
                strip.ClearTo( red, 4 * active_team - 4, 4 * active_team - 1);
                strip.Show();
                delay(100);
                strip.ClearTo( 0, 4 * active_team - 4, 4 * active_team - 1);
                strip.Show();
                delay(100);
            }
        }
        pattern = 71;
        break;

    case 71:
        strip.ClearTo( 0, 0, 15);
        strip.Show();
        TF_flag = 0;
        active_team = 0;
        pattern = 0;
        break;

    }



}
