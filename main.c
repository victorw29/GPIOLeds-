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

   int (*animation[])[5][3] = {frame0, frame1, frame2, frame3, frame4, frame5, frame6};

  for (int i = 0; i < 7; i++) {
    for (int linha = 0; linha < 5; linha++) {
      for (int coluna = 0; coluna < 5; coluna++) {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, animation[i][linha][coluna][0], animation[i][linha][coluna][1], animation[i][linha][coluna][2]);
      }
    }
    npWrite(); 
    sleep_ms(500); 
    Clear_ws2818
(); 
  }
}

void mostrarAnimacaoT2( void ){

  //Definicao dos frames da animacao
  int frame0[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame1[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame2[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame3[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame4[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}}
  };
  int frame5[5][5][3] ={
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame6[5][5][3] ={
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
  };
  int frame7[5][5][3] ={
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}}
  };
  int frame8[5][5][3] ={
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}}
  };
  int frame9[5][5][3] ={
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}}
  };
  int frame10[5][5][3] ={
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}}
  };
  int frame11[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  };
  
  int (*animation[])[5][3] = {
    frame0,frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8,frame9,frame10,frame11,
  };
  


  for (int i = 0; i < 12; i++){
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
void mostrarAnimacaoT3() {
  int frame0[5][5][3] ={
           {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
            {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
            {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}}
         };
           int frame1[5][5][3] ={

           {{255, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 255}},
            {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
            {{255, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 255}}
         };
           int frame2[5][5][3] ={

           {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {255, 0, 255}, {0, 0, 0}, {255, 0, 255}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {255, 0, 255}, {0, 0, 0}, {255, 0, 255}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
         };
           int frame3[5][5][3] ={

          {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {255, 0, 255}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
         };
           int frame4[5][5][3] ={

          {{255, 0, 255}, {255, 0, 255}, {255, 0, 255}, {255, 0, 255}, {255, 0, 255}},
            {{255, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 255}},
            {{255, 0, 255}, {0, 0, 0}, {255, 0, 255}, {0, 0, 0}, {255, 0, 255}},
            {{255, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 255}},
            {{255, 0, 255}, {255, 0, 255}, {255, 0, 255}, {255, 0, 255}, {255, 0, 255}}
        };
        
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
void mostrarAnimacaoT4(void) {
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

void mostrarAnimacaoT5(void) {
    int frame0[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
    };

    int frame1[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
    };

    int frame2[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
    };

    int frame3[5][5][3] = {
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}
    };

    int frame4[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
    };



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
}

void keypad_init() {
    for (int i = 14; i < 22; i++) {
        gpio_init( i );
        if (i < 18)
            gpio_set_dir(i, GPIO_OUT);  //Inicializa as portas 1 a 4 como saida
        else
            gpio_set_dir(i, GPIO_IN);   //Inicializa as portas 5 a 8 como entrada
    }
}

// Função para obter a tecla pressionada do keypad
char get_keypad_key() {
    char tecla = 'X';
    char keypadKeys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    for (int i = 0; i < 4; i++) {
        gpio_put( i + 14, true);  // Coloca as linhas em nível alto
        for (int j = 0; j < 4; j++) {
            if (gpio_get(18 + j)) {  // Verifica se a coluna está em nível alto
                tecla = keypadKeys[i][j];  // A tecla pressionada
            }
        }
        gpio_put(14 + i, false);  // Reseta as linhas
    }
    
    return tecla;
}

// função para configurar a cor dos LEDs com brilho ajustável
void set_led_color(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
    uint color[3] = {r * brightness / 100, g * brightness / 100, b * brightness / 100}; 
    for (int i = 0; i < LED_COUNT; i++) {
        npSetLED(i, color[0], color[1], color[2]);
    }
    npWrite(); // Atualiza os LEDs após configurar as cores
}


// animação da tecla 2 - alteração gradual de cores
void play_animation_2() {
    const int delay_ms = 100; // Delay entre frames (10 FPS)
    const int brightness = 80; // Brilho de 80%

    for (int frame = 0; frame < 5; frame++) {
        switch (frame) {
            case 0:
                set_led_color(255, 0, 0, brightness); // Vermelho
                break;
            case 1:
                set_led_color(0, 255, 0, brightness); // Verde
                break;
            case 2:
                set_led_color(0, 0, 255, brightness); // Azul
                break;
            case 3:
                set_led_color(255, 255, 0, brightness); // Amarelo
                break;
            case 4:
                set_led_color(255, 0, 255, brightness); // Magenta
                break;
        }
        sleep_ms(delay_ms); // Aguarda o próximo frame
    }

    // clear dos leds
    Clear_ws2818
();
}
int main() {
    stdio_init_all();
    init_ws2818(LED_PIN);  // Inicializa os LEDs
    Clear_ws2818();        // Limpa os LEDs
    keypad_init();         // Inicializa o teclado

    // Loop infinito para exibir a animação continuamente.
    while (true) {
        char tecla = get_keypad_key();  // Obtém a tecla pressionada

        npWrite();       // Atualiza os LEDs

        // Verifica qual tecla foi pressionada e executa a animação correspondente
        if (tecla == '1'){
            mostrarAnimacaoT1();  // Exibe os frames do coração pulsante
        } else if (tecla == '2'){
            mostrarAnimacaoT2();
        } else if (tecla == '3'){
            mostrarAnimacaoT3();
        } else if (tecla == '4'){
            mostrarAnimacaoT4();
        } else if (tecla == '5'){
            mostrarAnimacaoT5();
        } else if (tecla == '6'){
            mostrarAnimacaoT6();
        }

        // Implementação das novas teclas
        if (tecla == 'A') {
          Clear_ws2818();  // Desliga todos os LEDs
          npWrite();  // Atualiza os LEDs
        }
        else if (tecla == 'B') {
          set_led_color(0, 0, 255, 100);  // Liga os LEDs na cor azul com 100% de brilho
        }
        else if (tecla == 'C') {
          set_led_color(255, 0, 0, 80);   // Liga os LEDs na cor vermelha com 80% de brilho
        }
        else if (tecla == 'D') {
          set_led_color(0, 255, 0, 50);   // Liga os LEDs na cor verde com 50% de brilho
        }
        else if (tecla == '#') {
          set_led_color(255, 255, 255, 20);  // Liga os LEDs na cor branca com 20% de brilho
        }


        // Adicione mais animações se necessário, conforme os outros números ou teclas especiais.

        sleep_ms(100);  // Pausa de 100 ms após a animação completa
    }
    
  return 0;
}
