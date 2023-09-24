/* Grupo 
    Ester Rodrigues Vieira
    Gabriel da Silva Carvalho
    Manoel Elias de Araujo Neto
 */


#include "mbed.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

Timer timer;

/* Definição da variável global 
tendo em vista uma senha de 4 digitos
e a necessidade da variavel ser unsigned int
atribuo isso como um array para facilitar 
o acesso aos números
*/ 
unsigned int password[4] = {2, 7, 6, 0};

// variavel global de senha correta
bool isPasswordRight = false;

// typed password 
int *typedPassword= new int[4];

// Definição dos leds
DigitalOut led_1(PA_10); // Led 1 (D2)
DigitalOut led_2(PB_3); // led 2 (D3)
DigitalOut led_3(PB_5); // led 3 (D4)
DigitalOut led_4(PB_4); // led 4 (D5)

// Definição dos leds de saída para informar estado da senha
DigitalOut led_right(PB_10); // led correto (D6)
DigitalOut led_wrong(PA_8); // led errado (D7)

// Definição dos botões (0-9)
BusIn buttons(PA_9, PC_7, PB_6, PA_7, PA_6, PA_5, PB_11, PB_12, PA_11, PA_12);

// Botões de ação
InterruptIn button_ok(PB_2); // Botão ok
InterruptIn button_clear(PB_1); // Botão limpar

// Função para desligar todos os leds
void turnOffLeds() {
    led_1 = !led_1;
    led_2 = !led_2;
    led_3 = !led_3;
    led_4 = !led_4;
    led_right = !led_right;
    led_wrong = !led_wrong;
}

// Função para verificar se a senha digitada é equivalente a pre-definida
 void checkPassCorrect(int* typedPassword){
     // percorre a senha digitada para checar se é igual a senha pre-definida
     for(int i=0; i<4; i++){
         // se o dígito não é correto
         if (typedPassword[i] != password[i]) {
             // atribui true a variável global de verificação de senha
            return;
        }
     }
     isPasswordRight = true;
}

// Função de chamada para verificar a senha inserida quando o botão 'ok' é pressionado
void checkPasswordCaller() {
    checkPassCorrect(typedPassword);
}

/* Função getPassword pega os dados digitados pelo o usuário
e armazena em um array do tipo *int (pois não é possível retornar um array
normal em c++) 
*/
void getPassword() {
    int index = 0;
    bool typed = false;

    for(int i = 0; i < 10 && index < 4; i++) {
        // lógica para verificar se o botão clear foi pressionado e remover o último dígito
        if(button_clear && index > 0){
            typedPassword[index - 1] = -1;
            index--;
        // lógica para verificar se o botão ok foi pressionado e parar o loop
        }else if (button_ok) {
            typed = true;
            checkPasswordCaller();
            break;
        // lógica pra verifcar quando e qual botão foi pressionando
        }else if(buttons[i]) {
            typedPassword[index] = i;
            index++;
        }
    }

    if(typed == false){
        //ao pressionar o botão ok irá verificar se as senhas coincidem
        button_ok.rise(&checkPasswordCaller);
    }
}

//Função para ligar o led ao terminar de digitar a senha, irá receber um led e ligá-lo
void turnOnLedPass(DigitalOut& led){
    // contador iniciado ao chamar a função
    timer.start();
    // enquanto não dá o tempo, o led permanece aceso
    while(timer.read()<5.0){
        led = !led;
    }
    // o timer para e é resetado
    timer.stop();
    timer.reset();
}

void resetSystem(){
    // apaga todos os leds
    turnOffLeds();
    typedPassword = NULL;
    isPasswordRight = false;
}

int main(){
    // desligar todos os leds
    turnOffLeds();
    while (true) {
        // pegar valor digitado para cada led
        getPassword();
        if(isPasswordRight) {
            turnOnLedPass(led_right);

        } else {
            turnOnLedPass(led_wrong);
        }

        ThisThread::sleep_for(5000);
        // o sistema é resetado para o estado inicial
        resetSystem();
    }
}