# Tarefa MICROCONTROLADORES - MATRIZ DE LEDS 5X5

## Descrição

Este projeto implementa um sistema de teclado matricial 4x4 em um Raspberry Pi Pico, controlando uma matriz de LEDs RGB e um buzzer. Cada tecla pressionada aciona uma animação no display LED e ativa um buzzer para fornecer feedback visual e sonoro, utilizando a linguagem C e a biblioteca Pico SDK.

### Funcionalidades

- **Teclado Matricial 4x4**: O projeto utiliza um teclado matricial de 4 linhas e 4 colunas, permitindo a interação com 16 teclas.
- **Display de LEDs RGB**: Ao pressionar teclas especificas aciona animações no dsplay de LED RGB (composto por 5 pinos de cor - R, G, B) específico, para indicar visualmente a interação.
- **Buzzer**: Um buzzer é acionado sempre que uma tecla é pressionada, fornecendo um feedback sonoro.
- **Debounce**: A funcionalidade de debounce foi implementada para evitar múltiplas leituras rápidas da mesma tecla pressionada.

  
### Diagrama de Pinagem


| Componente              | GPIO/Pino |
|-------------------------|-----------|
| LED Vermelho (RED)      | GPIO 13   |
| LED Verde (GREEN)       | GPIO 11   |
| LED Azul (BLUE)         | GPIO 12   |
| Buzzer                  | GPIO 21   |
| Teclado Linha 1         | GPIO 1    |
| Teclado Linha 2         | GPIO 2    |
| Teclado Linha 3         | GPIO 3    |
| Teclado Linha 4         | GPIO 4    |
| Teclado Coluna 1        | GPIO 5    |
| Teclado Coluna 2        | GPIO 6    |
| Teclado Coluna 3        | GPIO 7    |
| Teclado Coluna 4        | GPIO 8    |


## Requisitos

- **Hardware**: Raspberry Pi Pico
- **Teclado Matricial 4x4**
- **3 LEDs RGB (cada LED com 3 pinos: R, G, B)**
- **Buzzer**
- **Biblioteca Pico SDK**

## Como Funciona

1. **Inicialização dos Pinos GPIO**: 
   Os pinos GPIO do Raspberry Pi Pico são configurados para o teclado, LEDs e buzzer. O teclado matricial é escaneado através de pinos de linha e coluna, enquanto os LEDs RGB e o buzzer são configurados como saídas.

2. **Escaneamento do Teclado**: 
   A função `KeyPressed` escaneia o teclado matricial de 4x4. Cada linha do teclado é ativada de forma sequencial, e as colunas são verificadas para identificar a tecla pressionada.

3. **Acionamento dos LEDs e Buzzer**: 
   Quando uma tecla é pressionada, o LED RGB correspondente à tecla é aceso e o buzzer é ativado por 300 ms. O LED permanece aceso enquanto a tecla estiver pressionada.

4. **Debounce**: 
   Para evitar leituras múltiplas da mesma tecla devido a oscilações do sinal no teclado, foi implementada uma função de debounce que realiza uma pausa de 300 ms após cada leitura de tecla, garantindo que cada pressionamento seja registrado apenas uma vez.

## Como Usar

1. Conecte o teclado matricial, os LEDs RGB e o buzzer ao Raspberry Pi Pico de acordo com os pinos definidos no código.
   
2. Compile o código utilizando o Pico SDK.
   
3. Carregue o código para o Raspberry Pi Pico.
   
4. Ao pressionar qualquer tecla do teclado, o sistema acenderá o LED RGB correspondente e ativará o buzzer.

# Estrutura do Código

O código principal está dividido em várias funções para modularizar o processo e facilitar a manutenção:

## Inicialização de Pinos
- **`iniciar_leds()`**: Inicializa os pinos GPIO para os LEDs RGB. Cada LED (vermelho, verde, azul) é configurado como saída e desligado por padrão.
- **`inicializar_buzzer()`**: Inicializa o pino do buzzer como saída e o mantém desligado por padrão.
- **Teclado Matricial**: Os pinos do teclado matricial (linhas e colunas) são configurados no loop principal para permitir a detecção da tecla pressionada.

## Controle dos LEDs RGB
- **`acionar_led(int cor)`**: Acende o LED da cor especificada (vermelho, verde ou azul). Cada cor é controlada pelos pinos GPIO correspondentes a R, G e B.
- **`desligar_led(int cor)`**: Desliga o LED especificado.

As cores são associadas da seguinte forma:
- **Vermelho**: GPIO 13
- **Verde**: GPIO 11
- **Azul**: GPIO 12

## Controle do Buzzer
- **`acionar_buzzer()`**: Liga o buzzer, se ele estiver desligado.
- **`desligar_buzzer()`**: Desliga o buzzer, se ele estiver ligado.
-  **`tocar_musica(char tecla)`**: Toca uma música com base na tecla pressionada.

## Lógica Principal

A lógica do programa detecta as teclas pressionadas no teclado matricial e realiza as seguintes ações:

- **Tecla 'A'**: 
  - Liga o LED vermelho.
  - Desliga os outros LEDs e o buzzer.
  - **Buzzer**: Toca a nota **C**.

- **Tecla 'B'**: 
  - Liga o LED verde.
  - Desliga os outros LEDs e o buzzer.
  - **Buzzer**: Toca a nota **D**.

- **Tecla 'C'**: 
  - Liga o LED azul.
  - Desliga os outros LEDs e o buzzer.
  - **Buzzer**: Toca a nota **E**.

- **Tecla '#'**: 
  - Liga o buzzer.
  - Desliga todos os LEDs.
  - **Buzzer**: Toca a nota **F**.

- **Tecla 'X' (nenhuma tecla pressionada)**: 
  - Desliga todos os LEDs e o buzzer.
  - **Buzzer**: Não toca nenhuma nota.

### Exemplo de Comportamento

- Se você pressionar a tecla 'A', o LED vermelho acende e o buzzer toca a nota **C**.
- Se pressionar a tecla 'B', o LED verde acende e o buzzer toca a nota **D**.
- Ao pressionar '#' o buzzer é ativado e toca a nota **F**, enquanto os LEDs são desligados.

## Definição dos Pinos
Os pinos utilizados no código são definidos da seguinte maneira:
- **LED Vermelho**: GPIO 13
- **LED Verde**: GPIO 11
- **LED Azul**: GPIO 12
- **Buzzer**: GPIO 21

### Mapeamento do Teclado Matricial

O teclado matricial 4x4 é mapeado para as seguintes teclas:

| Linha/Coluna | 1 | 2 | 3 | A |
|--------------|---|---|---|---|
| **1**        | 1 | 2 | 3 | A |
| **2**        | 4 | 5 | 6 | B |
| **3**        | 7 | 8 | 9 | C |
| **4**        | * | 0 | # | D |

A correspondência das teclas do teclado é feita com os pinos de linha (GPIO 1-4) e coluna (GPIO 5-8), com cada tecla sendo ativada ao pressionar uma linha e uma coluna simultaneamente.

## Implementação do Debounce

O debounce é um processo que evita múltiplas leituras do teclado quando uma tecla é pressionada rapidamente. Para garantir que o sistema detecte uma única pressão de tecla, foi adicionado um tempo de espera de 300 ms após a leitura de cada tecla pressionada. Isso impede a leitura repetida da tecla devido ao efeito de "bouncing" (quando o sinal elétrico oscila antes de se estabilizar).

### Arquivo `.gitignore`

Foi adicionado um arquivo `.gitignore` ao repositório. Esse arquivo é utilizado para ignorar certos arquivos e diretórios que não precisam ser versionados pelo Git, como arquivos temporários, diretórios de build e configurações específicas do ambiente de desenvolvimento. 

## Como Utilizar o Código no Wokwi Simulator

O **Wokwi Simulator** é uma plataforma online para simular circuitos e microcontroladores, como o Raspberry Pi Pico, sem precisar de hardware físico. Você pode usar este repositório tanto no site do Wokwi quanto no VSCode com a extensão **Wokwi Simulator**.

### Utilizando o Wokwi Simulator no Site

1. **Acesse o site do Wokwi:**
   - Vá para https://wokwi.com/

2. **Crie um novo projeto:**
   - Clique em "New Project" ou "Novo Projeto" e selecione a placa **Raspberry Pi Pico** ou qualquer outra placa que você estiver utilizando.

3. **Importe o código:**
   - Faça upload ou cole o código do repositório na área de código do Wokwi.

4. **Adicione os componentes:**
   - Na interface do Wokwi, adicione os componentes do seu circuito (teclado matricial, LEDs, buzzer, etc.) e conecte-os aos pinos correspondentes, conforme definido no código.

5. **Inicie a simulação:**
   - Clique em "Start Simulation" para iniciar a simulação e verificar o funcionamento do seu circuito.

### Utilizando o Wokwi Simulator no VSCode

1. **Instale a extensão Wokwi no VSCode:**
   - Abra o **VSCode** e vá até a aba de extensões (ícone de quadrado na barra lateral).
   - Busque por "Wokwi Simulator" e instale a extensão **Wokwi Simulator**.
   - Siga as instruções para utilização do Wokwi no vscode.

2. **Abra o código do repositório:**
   - Abra o diretório clonado do repositório no **VSCode**.

3. **Crie um arquivo .json:**
   - No VSCode, crie um novo arquivo com o nome `diagrama.json` como o presente neste repositório, e configure os parâmetros da sua simulação, como a placa utilizada (Raspberry Pi Pico), os pinos conectados aos componentes e outros detalhes.

4. **Crie um arquivo wokwi.toml:**
    - No VSCode, crie um novo arquivo com o nome `wokwi.toml` como o presente neste repositório, e configure os caminhos do firmware que será carregado na simulação e o arquivo .Elf com o código para a simulação, não esquecendo de especificar a versão do arquivo de configuração.
  
## Configurações a serem alteradas para compilar o projeto 

### Configurar o Caminho para o pico-sdk

Para garantir que o seu projeto esteja corretamente configurado, você precisará alterar o caminho para o `pico-sdk` no arquivo `CMakeLists.txt` para refletir o local em que o `pico-sdk` está instalado em seu computador. Siga os passos abaixo para configurar corretamente o caminho:

**Passo 1:** Encontre o Local do pico-sdk no Seu Computador

Primeiro, você precisa localizar onde o `pico-sdk` está instalado no seu computador. O `pico-sdk` pode ser obtido https://github.com/raspberrypi/pico-sdk ou já pode estar presente se você estiver usando a Raspberry Pi Pico com a configuração recomendada.

**Passo 2:** Alterar o Caminho no CMakeLists.txt

Abra o arquivo `CMakeLists.txt` do seu projeto e encontre a linha onde o caminho para o `pico-sdk` é especificado. O trecho relevante do arquivo se parece com o seguinte:

set(PICO_SDK_PATH "/caminho/para/o/seu/pico-sdk" CACHE STRING "Pico SDK directory")

**Substitua "/caminho/para/o/seu/pico-sdk" pelo caminho real do pico-sdk no seu sistema.** 

**Passo 3:** Salvar e Rodar o CMake

Após modificar o caminho do pico-sdk, salve o arquivo CMakeLists.txt. Em seguida, você pode rodar o CMake, configurar e compilar o projeto.

      
## Como clonar este repositório e contribuir com este software

**Passo 1:** Copie o link deste repositório: 
https://github.com/victorw29/Microcontroladores-GPIO

**Passo 2:** Abra o terminal ou prompt de comando

Abra o terminal (Linux/macOS) ou o Prompt de Comando/PowerShell (Windows).

**Passo 3:** Clonar o Repositório

No terminal ou prompt de comando, digite o seguinte comando para clonar o repositório:

**git clone** https://github.com/victorw29/Microcontroladores-GPIO


**Passo 4:** Acesse o diretório do repositório

Após clonar o repositório, um diretório será criado com o nome do repositório. Para acessar esse diretório, use o comando `cd`:

**cd** https://github.com/victorw29/Microcontroladores-GPIO

**Passo 5:** atualize a sua cópia local do Repositório: 

Depois de copiado para sua máquina o repositório, você pode baixar atualizações do repositório com o comando `pull`:

**git pull** https://github.com/victorw29/Microcontroladores-GPIO

**Passo 6:** enviando atualizações para o Repositório principal e o remoto:

**Para enviar as suas alterações para o repositório, basta utilizar o comando `add`:**

**git add** https://github.com/victorw29/Microcontroladores-GPIO

**Para commitar as alterações utilize o comanto `commit -m`:** 

**git commit -m** https://github.com/victorw29/Microcontroladores-GPIO "Descrição das Alterações"

**Para enviar as alterações para o Repositório remoto use o comando `push origin main`:**

**git push origin main** https://github.com/victorw29/Microcontroladores-GPIO

### Ajude-nos a melhorar esse software, contribuindo com seus conhecimentos!!

## Link para o video no youtube: https://youtu.be/xHChZULWF2c
## Link do projeto no site do Wokwi Simulator: https://wokwi.com/projects/420526874831393793

## Colaboradores

Segue abaixo os perfis colaboradores deste projeto:

- [AnaBeatriz](https://github.com/anabeatrizsse1) (Estrutura do código, definição das bibliotecas e inicialização);
- [JonathanMatos](https://github.com/JonathanMatos25) (Função do teclado);
- [PedroAlonso](https://github.com/pedroalonso19) (Função para ler as teclas);
- [Davi](https://github.com/Pr0wer) (Função para tocar notas);
- [ViniciusPaz](https://github.com/V1n1Paz) (Estrutura do código, função do buzzer);
- [VictorWeverthon](https://github.com/victorw29) (criação do repositório, int main, estrutura do código);
