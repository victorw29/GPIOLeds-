# Projeto de Teclado Matricial 4x4 com Matriz de LEDs RGB e Buzzer

## Descrição

Este projeto implementa um sistema de teclado matricial 4x4 em um **Raspberry Pi Pico**, controlando uma **matriz de LEDs RGB** e um **buzzer**. Cada tecla pressionada aciona uma animação no display LED e ativa um buzzer para fornecer feedback visual e sonoro, utilizando a linguagem **C** e a biblioteca **Pico SDK**.

## Funcionalidades

- **Teclado Matricial 4x4**: O projeto utiliza um teclado matricial de 4 linhas e 4 colunas, permitindo a interação com 16 teclas.
- **Display de LEDs RGB**: Ao pressionar teclas específicas, aciona animações no display de LED RGB (composto por 5 pinos de cor - R, G, B), para indicar visualmente a interação.
- **Buzzer**: Um buzzer é acionado sempre que uma tecla é pressionada, fornecendo um feedback sonoro.
- **Debounce**: A funcionalidade de debounce foi implementada para evitar múltiplas leituras rápidas da mesma tecla pressionada.

## Diagrama de Pinagem

| Componente               | GPIO/Pino |
|--------------------------|-----------|
| LED Vermelho (RED)        | GPIO 13   |
| LED Verde (GREEN)         | GPIO 11   |
| LED Azul (BLUE)           | GPIO 12   |
| Buzzer                    | GPIO 21   |
| Teclado Linha 1           | GPIO 1    |
| Teclado Linha 2           | GPIO 2    |
| Teclado Linha 3           | GPIO 3    |
| Teclado Linha 4           | GPIO 4    |
| Teclado Coluna 1          | GPIO 5    |
| Teclado Coluna 2          | GPIO 6    |
| Teclado Coluna 3          | GPIO 7    |
| Teclado Coluna 4          | GPIO 8    |

## Requisitos

- **Hardware**:
  - Raspberry Pi Pico
  - Teclado Matricial 4x4
  - 3 LEDs RGB (cada LED com 3 pinos: R, G, B)
  - Buzzer
- **Biblioteca**: Pico SDK

## Como Funciona

1. **Inicialização dos Pinos GPIO**: 
   - Os pinos GPIO do Raspberry Pi Pico são configurados para o teclado, LEDs e buzzer.
   - O teclado matricial é escaneado através de pinos de linha e coluna, enquanto os LEDs RGB e o buzzer são configurados como saídas.

2. **Escaneamento do Teclado**: 
   - A função `KeyPressed` escaneia o teclado matricial 4x4. Cada linha do teclado é ativada sequencialmente, e as colunas são verificadas para identificar a tecla pressionada.

3. **Acionamento dos LEDs e Buzzer**: 
   - Quando uma tecla é pressionada, os LEDs RGB exibem a cor e a intensidade correspondente, e o buzzer é ativado por 300 ms.

4. **Debounce**: 
   - Para evitar leituras múltiplas da mesma tecla devido a oscilações do sinal no teclado, foi implementada uma função de debounce que realiza uma pausa de 300 ms após cada leitura de tecla, garantindo que cada pressionamento seja registrado apenas uma vez.

## Estrutura do Código

O código principal está dividido em várias funções para modularizar o processo e facilitar a manutenção:

### Inicialização de Pinos

- `iniciar_leds()`: Inicializa os pinos GPIO para os LEDs RGB. Cada LED (vermelho, verde, azul) é configurado como saída e desligado por padrão.
- `inicializar_buzzer()`: Inicializa o pino do buzzer como saída e o mantém desligado por padrão.

### Teclado Matricial

- Os pinos do teclado matricial (linhas e colunas) são configurados no loop principal para permitir a detecção da tecla pressionada.

### Controle dos LEDs RGB

- `acionar_led(int cor, int intensidade)`: Acende todos os LEDs na cor e intensidade especificada (vermelho, verde, azul ou branco). Cada cor é controlada pelos pinos GPIO correspondentes a R, G e B.
- `desligar_leds()`: Desliga todos os LEDs.

### Controle do Buzzer

- `acionar_buzzer()`: Liga o buzzer, se ele estiver desligado.
- `desligar_buzzer()`: Desliga o buzzer, se ele estiver ligado.
- `tocar_musica(char tecla)`: Toca uma música com base na tecla pressionada.

### Lógica Principal

A lógica do programa detecta as teclas pressionadas no teclado matricial e realiza as seguintes ações:

- **Tecla 'A'**: Desliga todos os LEDs. 
  - **Buzzer**: Não emite som.
  
- **Tecla 'B'**: Liga todos os LEDs na cor azul com 100% de intensidade. 
  - **Buzzer**: Não emite som.

- **Tecla 'C'**: Liga todos os LEDs na cor vermelha com 80% de intensidade. 
  - **Buzzer**: Não emite som.

- **Tecla 'D'**: Liga todos os LEDs na cor verde com 50% de intensidade. 
  - **Buzzer**: Não emite som.

- **Tecla '#'**: Liga todos os LEDs na cor branca com 20% de intensidade. 
  - **Buzzer**: Não emite som.

## Exemplo de Comportamento

- Se você pressionar a tecla **'A'**, todos os LEDs serão desligados.
- Se pressionar a tecla **'B'**, todos os LEDs serão acesos na cor azul com 100% de intensidade.
- Se pressionar a tecla **'C'**, todos os LEDs serão acesos na cor vermelha com 80% de intensidade.
- Se pressionar a tecla **'D'**, todos os LEDs serão acesos na cor verde com 50% de intensidade.
- Se pressionar a tecla **'#'**, todos os LEDs serão acesos na cor branca com 20% de intensidade.

## Configurações de Hardware

### Definição dos Pinos

| Componente   | GPIO/Pino |
|--------------|-----------|
| LED Vermelho | GPIO 13   |
| LED Verde    | GPIO 11   |
| LED Azul     | GPIO 12   |
| Buzzer       | GPIO 21   |

### Mapeamento do Teclado Matricial

| Linha/Coluna | 1  | 2  | 3  | A  |
|--------------|----|----|----|----|
| 1            | 1  | 2  | 3  | A  |
| 2            | 4  | 5  | 6  | B  |
| 3            | 7  | 8  | 9  | C  |
| 4            | *  | 0  | #  | D  |

---

## Como Usar

1. Conecte os componentes ao Raspberry Pi Pico conforme os pinos definidos na tabela acima.
2. Compile o código utilizando o **Pico SDK**.
3. Carregue o firmware gerado para o Raspberry Pi Pico.
4. Pressione as teclas do teclado matricial para interagir com os LEDs e o buzzer.

### Exemplo de Comportamento

| Tecla Pressionada | Ação                                |
|-------------------|-------------------------------------|
| 'A'               | Acende o LED vermelho e toca uma nota. |
| 'B'               | Acende o LED verde e toca outra nota. |
| 'C'               | Acende o LED azul e toca uma nota diferente. |
| '#'               | Liga o buzzer e apaga todos os LEDs. |

---

## Estrutura do Código

O código está dividido em funções modulares para facilitar a manutenção:

### Inicialização de Pinos

- **`iniciar_leds()`**: Configura os pinos GPIO para os LEDs RGB.
- **`inicializar_buzzer()`**: Configura o pino do buzzer.
- **Teclado Matricial**: Configura as linhas e colunas do teclado matricial.

### Controle de LEDs RGB

- **`acionar_led(int cor)`**: Acende o LED da cor especificada (vermelho, verde ou azul).
- **`desligar_led(int cor)`**: Desliga o LED especificado.

### Controle do Buzzer

- **`acionar_buzzer()`**: Liga o buzzer.
- **`desligar_buzzer()`**: Desliga o buzzer.
- **`tocar_musica(char tecla)`**: Toca uma música correspondente à tecla pressionada.

### Implementação do Debounce

O debounce evita múltiplas leituras indesejadas ao pressionar uma tecla. Um tempo de espera de 300 ms é aplicado após a leitura de cada tecla.

---

## Utilizando o Wokwi Simulator

### No Site do Wokwi

1. Acesse [Wokwi Simulator](https://wokwi.com/).
2. Crie um novo projeto e selecione a placa **Raspberry Pi Pico**.
3. Importe o código para a área de edição.
4. Adicione os componentes ao circuito e conecte-os aos pinos correspondentes.
5. Inicie a simulação para verificar o funcionamento.

### No VSCode

1. Instale a extensão **Wokwi Simulator**.
2. Abra o repositório no VSCode.
3. Configure os arquivos `diagram.json` e `wokwi.toml` para o projeto.
4. Execute a simulação diretamente no editor.

---

## Configurações para Compilação

### Alterando o Caminho do `pico-sdk`

1. Localize o diretório onde o `pico-sdk` está instalado.
2. No arquivo `CMakeLists.txt`, altere o caminho do `pico-sdk`:

```cmake
set(PICO_SDK_PATH "/caminho/para/o/seu/pico-sdk" CACHE STRING "Pico SDK directory")
```
3. Salve e execute o CMake para compilar o projeto.

---

## Como Contribuir

1. Clone o repositório:

```bash
git clone https://github.com/victorw29/Microcontroladores-GPIO
```

2. Faça suas alterações e envie um **pull request**.
3. Siga as boas práticas de desenvolvimento e documentação.

---

## Links Úteis

- [Vídeo no YouTube](https://youtu.be/xHChZULWF2c)
- [Projeto no Wokwi Simulator](https://wokwi.com/projects/420526874831393793)

---

## Colaboradores

- [Victor](https://github.com/victorw29)  
- [Ana Beatriz](https://github.com/anabeatrizsse1)
- 
