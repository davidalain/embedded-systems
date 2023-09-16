/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <chrono>

using namespace std::chrono;

// // Blinking rate in milliseconds
#define BLINKING_RATE     500ms


// int main()
// {
//     // Initialise the digital pin LED1 as an output
//     DigitalOut led(LED1);

//     DigitalIn botao(BUTTON1);
//     int botaoAntes = botao;
//     int botaoAtual = botao;
//     while (true) {
//         ThisThread::sleep_for(BLINKING_RATE);
    
//         if(botaoAtual == 0 && botaoAntes == 1) {
//             led = !led;
//         }    
//         botaoAntes = botaoAtual;
//         botaoAtual = botao;
//         // printf("Hello world! %i\n", led.read());
//         printf("botao: %d\n", botao.read());
//     }
// }


/*InterruptIn button(BUTTON1);
Timer t;
int counter = 0;
int leds[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
BusOut display(PA_10, PC_7, PA_9, PA_8, PB_10, PB_4, PB_5, PB_3);

void botao_solto() {
    //printf("click!");
    static unsigned long long timeBefore = 0;
    unsigned long long timeNow = duration_cast<milliseconds>(t.elapsed_time()).count();
    if(timeNow - timeBefore >= 20){
        //printf("vai incrementar");
        display = leds[counter++ % 10];
    }
    //printf("%i", counter);
    timeBefore = timeNow;
}

int main(){
    t.start();
    button.rise(&botao_solto); // attach the address of the flip function to the rising edge

    while (true) {          // wait around, interrupts will interrupt this!
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/

// Teste Joystick
int main(){
    AnalogIn x(PA_1);
    AnalogIn y(PA_4);

    DigitalIn sw(PA_15);
    DigitalOut led(LED1);

    while (1) {
        if(x.read() <= 0.33) {
            led = 0;
        } else if(x.read() >= 0.66) {
            led = 1;
        } else {
            led = !led;
            ThisThread::sleep_for(BLINKING_RATE);                      
        }
        printf("%u\n", x.read_u16());
    }
}