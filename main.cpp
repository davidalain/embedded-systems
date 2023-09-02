/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <chrono>

using namespace std::chrono;

// // Blinking rate in milliseconds
#define BLINKING_RATE     250ms


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


InterruptIn button(BUTTON1);
DigitalOut led(LED1);
Timer t;

void botao_solto() {
    static unsigned long long timeBefore = 0;
    unsigned long long timeNow = duration_cast<milliseconds>(t.elapsed_time()).count();
    if(timeNow - timeBefore >= 20){
        led = !led;
    }
    timeBefore = timeNow;
}

int main(){
    t.start();
    button.rise(&botao_solto); // attach the address of the flip function to the rising edge
    t.stop();
    
    while (true) {          // wait around, interrupts will interrupt this!
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
