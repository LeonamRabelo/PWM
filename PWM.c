#include <stdio.h> //Biblioteca padrão da linguagem C
#include "pico/stdlib.h" //Biblioteca do SDK Pico
#include "pico/time.h" //Biblioteca para gerenciamento de tempo
#include "hardware/irq.h" //Biblioteca para gerenciamento de interrupções
#include "hardware/pwm.h" //Biblioteca para controle de PWM

        /*Para teste na BitDogLab, apenas alterar o valor do GPIO do 
        Servo para 12, representando o led azul da placa*/

#define SERVO_PIN 22 //Pino do Servo (GPIO 22)
#define PWM_FREQ 50  //Frequência do PWM (50Hz → 20ms de período)
#define CLOCK_DIV 64.0 //Divisor de clock para ajuste fino do PWM
#define WRAP_VALUE 39063 //Valor de wrap calculado para 50Hz

uint volatile slice_numero;

//Função para calcular o duty cycle com base no tempo do pulso (µs)
uint16_t calculate_duty_cycle(float pulse_us){
    return (uint16_t)((pulse_us / 20000.0) * WRAP_VALUE); //20ms = período do PWM
}

//Define o ângulo do servomotor via PWM
void servo_angulo(uint slice, float pulse_us){
    uint16_t duty = calculate_duty_cycle(pulse_us);
    pwm_set_chan_level(slice, PWM_CHAN_A, duty);
}

//Inicializa os GPIOs e configura PWM
void inicializarGPIOS(){
    stdio_init_all(); //Inicializa entrada e saída padrão

    //Configuração do Servo como PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    slice_numero = pwm_gpio_to_slice_num(SERVO_PIN); //Obtém o slice PWM do servo

    //Configuração do PWM com período de 20ms (50Hz)
    pwm_set_clkdiv(slice_numero, CLOCK_DIV);
    pwm_set_wrap(slice_numero, WRAP_VALUE);
    pwm_set_enabled(slice_numero, true);
}

int main(){
    inicializarGPIOS(); //Inicializa os GPIOs e PWM antes do loop
        
    //Movimentação do servo entre ângulos fixos no inicio do programa
    //180 graus
    printf("Movendo para 180 graus\n");
    servo_angulo(slice_numero, 2400); //180° -> 2400µs
    sleep_ms(5000);
    //90 graus
    printf("Movendo para 90 graus\n");
    servo_angulo(slice_numero, 1470); //90° -> 1470µs
    sleep_ms(5000);
    //0 graus
    printf("Movendo para 0 graus\n");
    servo_angulo(slice_numero, 500); //0° -> 500µs
    sleep_ms(5000);

    while(1){

    //Rotina de movimentação constante entre 0° e 180° com incrementos de 5µs a cada 10ms
    printf("Movimentação suave iniciada\n");

        //Movendo de 0° para 180° (+5µs a cada 10ms)
        for(float pulse = 500; pulse <= 2400; pulse += 5){
            servo_angulo(slice_numero, pulse);
            sleep_ms(10);
        }

        //Movendo de 180° para 0° (-5µs a cada 10ms)
        for(float pulse = 2400; pulse >= 500; pulse -= 5){
            servo_angulo(slice_numero, pulse);
            sleep_ms(10);
        }
    }
}

//180 graus a luz do led fica mais intensa, chegando a 0 graus sua luz fica menos intensa. Fica ainda mais
//visível quando o a movimentação constante de 0 a 180 graus, e vice versa, acontece de maneira que a intensidade
//do led vai aumentando ou diminuindo gradativamente