#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definindo os pinos dos LEDs e do botão
#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define BOTAO 5

// Variável para controlar o estado do sistema
volatile int estado_leds = 0;
volatile bool botao_pressionado = false;

// Função de callback para desligar os LEDs
int64_t desligar_led_callback(alarm_id_t id, void *user_data) {
    estado_leds++;

    if (estado_leds == 1) {
        gpio_put(LED_AZUL, 0);
    } else if (estado_leds == 2) {
        gpio_put(LED_VERMELHO, 0);
    } else if (estado_leds == 3) {
        gpio_put(LED_VERDE, 0);
        botao_pressionado = false; // Permite novo acionamento do botão
        return 0; // Finaliza o alarme
    }

    // Agenda o próximo desligamento após 3 segundos
    add_alarm_in_ms(3000, desligar_led_callback, NULL, false);
    return 0;
}

// Função de interrupção para o botão
void botao_irq_handler(uint gpio, uint32_t events) {
    if (!botao_pressionado) {
        sleep_ms(50);

         if (!botao_pressionado) {
            botao_pressionado = true;
          
            estado_leds = 0;

            // Liga todos os LEDs
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_VERDE, 1);

            // Inicia o temporizador para desligar os LEDs
            add_alarm_in_ms(3000, desligar_led_callback, NULL, false);
        }
        }
}

int main() {
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configura o pino do botão como entrada com pull-up
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    // Habilita o resistor pull-up interno para o pino do botão.
    gpio_pull_up(BOTAO);

    // Configura a interrupção para o botão
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_irq_handler);

    // Loop principal
    while (true) {
        printf("Aguardando acionamento do botão...\n");
        sleep_ms(9000);
    }

    return 0;
}
