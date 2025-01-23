# Tarefa MICROCONTROLADORES - MATRIZ DE LEDS 5X5

## Descrição

Este projeto implementa um sistema de teclado matricial 4x4 em um Raspberry Pi Pico, controlando uma matriz de LEDs RGB e um buzzer. Cada tecla pressionada aciona uma animação no display LED e ativa um buzzer para fornecer feedback visual e sonoro, utilizando a linguagem C e a biblioteca Pico SDK.

### Funcionalidades

- **Teclado Matricial 4x4**: O projeto utiliza um teclado matricial de 4 linhas e 4 colunas, permitindo a interação com 16 teclas.
- **Display de LEDs RGB**: Ao pressionar teclas especificas aciona animações no dsplay de LED RGB (composto por 5 pinos de cor - R, G, B) específico, para indicar visualmente a interação.
- **Buzzer**: Um buzzer é acionado sempre que uma tecla é pressionada, fornecendo um feedback sonoro.
- **Debounce**: A funcionalidade de debounce foi implementada para evitar múltiplas leituras rápidas da mesma tecla pressionada.
