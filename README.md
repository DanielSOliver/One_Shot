# One_Shot

README - Controle de LEDs com Botão no Raspberry Pi Pico

Este projeto implementa um sistema de controle de LEDs utilizando um botão no Raspberry Pi Pico. Quando o botão é pressionado, todos os LEDs (azul, vermelho e verde) são ligados e, em seguida, desligados sequencialmente a cada 3 segundos. O código foi desenvolvido em C e utiliza a SDK do Pico para manipulação de GPIO e temporizadores.

Descrição do Código
Estrutura do Código
Inclusão de Bibliotecas:

stdio.h: Para funções de entrada e saída padrão.

pico/stdlib.h: Para funções específicas do Raspberry Pi Pico, como manipulação de GPIO e temporizadores.

hardware/gpio.h: Para manipulação de GPIO.

hardware/timer.h: Para manipulação de temporizadores de hardware.

Definição dos Pinos:

LED_AZUL: Pino GPIO 11.

LED_VERMELHO: Pino GPIO 12.

LED_VERDE: Pino GPIO 13.

BOTAO: Pino GPIO 5.

Variáveis Globais:

estado_leds: Controla o estado atual dos LEDs (0: todos ligados, 1: azul desligado, 2: vermelho desligado, 3: verde desligado).

botao_pressionado: Indica se o botão foi pressionado.

Função de Callback para Desligar LEDs:

desligar_led_callback: Função chamada pelo temporizador para desligar os LEDs sequencialmente a cada 3 segundos.

Função de Interrupção para o Botão:

botao_irq_handler: Função chamada quando o botão é pressionado. Liga todos os LEDs e inicia o temporizador para desligá-los sequencialmente.

Função Principal:

main: Inicializa os pinos dos LEDs como saída e o pino do botão como entrada com pull-up. Configura a interrupção para o botão e entra em um loop infinito que aguarda o acionamento do botão.

Funcionamento
Inicialização:

Os pinos dos LEDs são configurados como saída.

O pino do botão é configurado como entrada com resistor pull-up interno.

A interrupção para o botão é configurada para detectar a borda de descida (quando o botão é pressionado).

Acionamento do Botão:

Quando o botão é pressionado, a função botao_irq_handler é chamada.

Todos os LEDs são ligados.

O temporizador é configurado para chamar a função desligar_led_callback após 3 segundos.

Desligamento Sequencial dos LEDs:

A cada 3 segundos, a função desligar_led_callback é chamada, desligando os LEDs sequencialmente (azul, vermelho, verde).

Após o desligamento do último LED, o sistema permite que o botão seja pressionado novamente.

Loop Principal:

O programa entra em um loop infinito, onde aguarda o acionamento do botão.

Uma mensagem é exibida no console a cada 9 segundos indicando que o sistema está aguardando o acionamento do botão.

Diagrama de Conexões

Pino do Pico	Componente

GPIO 11	LED Azul

GPIO 12	LED Vermelho

GPIO 13	LED Verde

GPIO 5	Botão

Considerações Finais

Este projeto é um exemplo simples de como controlar LEDs com um botão utilizando interrupções e temporizadores no Raspberry Pi Pico. Ele pode ser expandido para incluir mais funcionalidades, como diferentes padrões de piscar os LEDs ou a inclusão de mais botões para controle adicional.
