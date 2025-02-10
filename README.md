# Controle de Servo Motor com Raspberry Pi Pico

Este projeto demonstra como controlar um servo motor utilizando PWM na Raspberry Pi Pico. O código configura um sinal PWM de 50Hz e ajusta o duty cycle para movimentar o servo entre 0° e 180° de forma gradual.

## 🛠 Requisitos
- Raspberry Pi Pico W
- Servo motor
- SDK do Raspberry Pi Pico configurado
- LED RGB (Simulando teste na BitDogLab)

## 📜 Funcionamento
1. Inicializa o GPIO configurado para PWM (GPIO 22 por padrão).
2. Define um período de 20ms (50Hz) e ajusta o duty cycle para diferentes ângulos.
3. Move o servo para 0°, 90° e 180° no início.
4. Inicia um loop onde o servo se movimenta suavemente entre 0° e 180° e vice-versa.
5. Se testado na placa BitDogLab, o LED azul do GPIO 12 pode ser usado para visualizar a intensidade do PWM.

## 🔧 Configuração do PWM
- **Frequência:** 50Hz (período de 20ms)
- **Divisor de clock:** 64
- **Valor de Wrap:** 39063
- **Pulso para ângulos comuns:**
  - 0°: 500µs
  - 90°: 1470µs
  - 180°: 2400µs

## 🚀 Como Executar

**Requisitos**
- SDK do Raspberry Pi Pico instalado e configurado
- VS Code com as extensões:
Raspberry Pi Pico Project
Wokwi Simulator
CMake configurado

## Passos
**Simulação no Wokwi (VS Code):**
- Importe o projeto (pasta) utilizando a extensão Raspberry Pi Pico Project.
- Compile o projeto pela extensão.
No Wokwi, abra o arquivo diagram.json e execute (Play).

**Execução na Placa BitDogLab:**
- Compile o projeto para gerar o arquivo .uf2.
- Envie o arquivo .uf2 para a placa Raspberry Pi Pico.

## 📌 Notas
- Para testar na **BitDog Lab**, altere `#define SERVO_PIN 22` para `#define SERVO_PIN 12`.
- Este projeto requer a biblioteca pico-sdk, que deve estar corretamente configurada no ambiente de desenvolvimento.

## Análise do teste com a BitDogLab, utilizando o LED azul
Em 180 graus a luz do led fica mais intensa, em 90 graus menos intensa, e chegando a 0 graus sua luz fica ainda menos intensa. Fica ainda mais visível quando o a movimentação constante de 0 a 180 graus, e vice versa, acontece de maneira que a intensidade do led vai aumentando ou diminuindo gradativamente.

## Demonstração

Assista uma breve apresentação do código acessando o link: 

**Autor:** *Leonam S. Rabelo*