
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "gpio_irq_handler.h"
#include "hardware/irq.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 28

struct pixel_t {
  uint8_t G, R, B; 
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; 
npLED_t leds[LED_COUNT];

PIO np_pio;
uint sm;
void ws2812_set_pixel(int i, uint32_t color){

}

void init_ws2818(uint pin) {
  uint offset = pio_add_program(pio0, &ws2812_program);
  np_pio = pio0;

  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); 
  }

  ws2812_program_init(np_pio, sm, offset, pin, 800000.f);

  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}


void Clear_ws2818() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}
void Clear_Leds() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(0, 0, 0, 0);
}

void npWrite() {
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
}

int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24 - (y * 5 + x); 
    } else {
        return 24 - (y * 5 + (4 - x)); 
    }
}

void mostrarFrame(uint8_t frame[5][5]) {
    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int posicao = getIndex(linha, coluna);
            
            // Verifique se o valor do "frame" é 1 (LED aceso), e defina a cor do LED.
            if (frame[linha][coluna] == 1) {
                npSetLED(posicao, 255, 0, 0); // Cor vermelha para o coração (255, 0, 0)
            } else {
                npSetLED(posicao, 0, 0, 0); // Desliga o LED (0, 0, 0)
            }
        }
    }
}

void mostrarAnimacaoT1() {
  // Definindo os frames para a animação de coração pulsante (expansão e contração).
  int frame0[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame1[5][5][3] = {
   {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame2[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame3[5][5][3] = {
     {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame4[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame5[5][5][3] = {
   {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame6[5][5][3] = {
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}}
  };

  // Array com todos os frames da animação.
   int (*animation[])[5][3] = {frame0, frame1, frame2, frame3, frame4, frame5, frame6};

  void mostrarAnimacaoT4(void) {
    // Frames da animação (exemplo: ondas de cor se movendo)
    int frame0[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
    };

    int frame1[5][5][3] = {
        {{0, 0, 0},   {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}
    };

    int frame2[5][5][3] = {
        {{0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {0, 0, 0},   {0, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {0, 0, 0},   {0, 0, 0}}
    };

    int frame3[5][5][3] = {
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
        {{255, 0, 0}, {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}}
    };

    int frame4[5][5][3] = {
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
    };

    // Exemplo de iteração para processar os frames
    // (adicione sua lógica de exibição aqui)

 int (*animation[])[5][3] = {
    frame0,
    frame1,
    frame2,
    frame3,
    frame4,
  };

  for (int i = 0; i < 5; i++){
    for(int linha = 0; linha < 5; linha++)
    {
    for(int coluna = 0; coluna < 5; coluna++)
    {
      int posicao = getIndex(linha, coluna);
      npSetLED(posicao, animation[i][coluna][linha][0], animation[i][coluna][linha][1], animation[i][coluna][linha][2]);
    }
    }
    npWrite();
    sleep_ms(500);
    Clear_ws2818
();
  }
   
}
  // Loop para exibir cada frame num intervalo de 500 milissegundos.
  for (int i = 0; i < 7; i++) {
    for (int linha = 0; linha < 5; linha++) {
      for (int coluna = 0; coluna < 5; coluna++) {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, animation[i][linha][coluna][0], animation[i][linha][coluna][1], animation[i][linha][coluna][2]);
      }
    }
    npWrite(); // Escreve os dados nos LEDs.
    sleep_ms(500); // Pausa de 500 ms entre os frames.
    Clear_ws2818
(); // Limpa os LEDs.
  }
}

// Animação feita por Davi
void mostrarAnimacaoT6() {
    int frame0[5][5][3] = {
  
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
      int frame1[5][5][3] = {

    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {120, 120, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {255, 0, 0}}
  };
      int frame2[5][5][3] = {

    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame3[5][5][3] = {

    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame4[5][5][3] = {

    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame5[5][5][3] = {

    {{255, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 0, 0}, {255, 0, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame6[5][5][3] = {

    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {120, 120, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{255, 0, 0}, {255, 0, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0},{120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame7[5][5][3] = {

    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {120, 120, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{255, 255, 0}, {120, 120, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0},{120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
  };
      int frame8[5][5][3] = {

    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {120, 120, 0}, {120, 120, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 255, 0}, {120, 120, 0}, {0, 0, 255}, {120, 120, 0}, {0, 255, 0}},
    {{0, 255, 0}, {120, 120, 0},{255, 0, 0}, {120, 120, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}}
  };
  

 int (*animation[])[5][3] = {
    frame0,
    frame1,
    frame2,
    frame3,
    frame4,
    frame5,
    frame6,
    frame7,
    frame8,

  };

  for (int i = 0; i < 8; i++){
    for(int linha = 0; linha < 5; linha++)
    {
    for(int coluna = 0; coluna < 5; coluna++)
    {
      int posicao = getIndex(linha, coluna);
      npSetLED(posicao, animation[i][coluna][linha][0], animation[i][coluna][linha][1], animation[i][coluna][linha][2]);
    }
    }
    npWrite();
    sleep_ms(500);
    Clear_ws2818();
  }
// Função para a animação de estrela
void mostrarAnimacaoT2(PIO pio, uint sm) {
    // Frames da animação (estrela se formando)
    Color frames[5][NUM_LEDS] = {
        // Frame 1: Apenas o centro acende
        {{0, 0, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {0, 0, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {0, 0, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        // Frame 2: Acendem os braços principais
        {{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {255, 255, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {255, 255, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}},
        // Frame 3: Acendem os braços diagonais
        {{255, 255, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {255, 255, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {255, 255, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {255, 255, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {255, 255, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {255, 255, 0}},
        // Frame 4: Estrela completa
        {{255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {255, 255, 0}, {0, 0, 0}, {255, 255, 0}, {0, 0, 0}, {255, 255, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}},
        // Frame 5: Estrela pisca
        {{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0},
         {0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}}
    };

    // Exibe os frames sequencialmente
    for (int i = 0; i < 5; i++) {
        display_frame(pio, sm, frames[i]);
        sleep_ms(300);  // Atraso de 300ms entre frames
    }
}
