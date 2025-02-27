#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"  // Biblioteca do Pico SDK
#include "hardware/i2c.h"
#include "hardware/adc.h" // Biblioteca para ADC
#include "lib/ssd1306.h"
#include <string.h>

// Definição dos pinos
#define LED_REFRIGERACAO 12  // LED que indica refrigeração ativa
#define LED_AQUECIMENTO 13  // LED que indica aquecimento ativo
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define I2C_ADDR 0x3C

// Definição dos limites de temperatura
#define PINO_ADC_TEMP 26 // Pino ADC onde o sensor está conectado
#define TEMP_MIN 18 // Temperatura mínima desejada (simulada)
#define TEMP_MAX 25 // Temperatura máxima desejada (simulada)

// Variáveis globais
int temperatura = 0;
ssd1306_t display;
uint16_t leitura_adc;
float tensao;

void setup() {
    adc_init();
    adc_gpio_init(PINO_ADC_TEMP); // Configura o ADC para ler temperatura
    
    gpio_init(LED_REFRIGERACAO);
    gpio_set_dir(LED_REFRIGERACAO, GPIO_OUT);
    gpio_init(LED_AQUECIMENTO);
    gpio_set_dir(LED_AQUECIMENTO, GPIO_OUT);
    stdio_init_all();

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&display, 128, 64, false, I2C_ADDR, I2C_PORT);
    ssd1306_config(&display);
    
    ssd1306_send_data(&display);
    ssd1306_draw_string(&display, "Sistema Iniciado", 0, 0);
    ssd1306_send_data(&display);

    // Leitura inicial do ADC para definir a temperatura ambiente
    adc_select_input(4);
    leitura_adc = adc_read();
    tensao = (leitura_adc * 3.3) / 4095.0;
    temperatura = (int)(27 - (tensao - 0.706)/0.001721); // Exemplo para TMP36
}

void atualizar_display(const char *mensagem, int temp) {
    ssd1306_fill(&display, false);
    ssd1306_rect(&display, 0, 0, 127, 63, true, false);
    ssd1306_draw_string(&display, mensagem, 25, 20);
    char temp_str[16];
    snprintf(temp_str, sizeof(temp_str), "Temp: %d C", temp);
    ssd1306_draw_string(&display, temp_str, 25, 36);
    
    ssd1306_send_data(&display);
}

void ajustar_temperatura() {
    if (temperatura >= TEMP_MAX + 20) { // Se a temperatura estiver 20°C acima do máximo, ajuste mais rápido
        if (gpio_get(LED_REFRIGERACAO)) {
            temperatura -= 2;
        }
    } else if (temperatura <= TEMP_MIN - 20) { // Se a temperatura estiver 20°C abaixo do mínimo, aquece mais rápido
        if (gpio_get(LED_AQUECIMENTO)) {
            temperatura += 2;
        }
    } else { // Ajuste normal
        if (gpio_get(LED_REFRIGERACAO)) {
            temperatura -= 1;
        } else if (gpio_get(LED_AQUECIMENTO)) {
            temperatura += 1;
        }
    }
} 

void variar_temperatura_estavel() {
    if (rand() % 2 == 0) {
        temperatura += 1;
    } else {
        temperatura -= 1;
    }
}

void loop() {
    printf("Temperatura atual: %d °C\n", temperatura);

    // Controle de temperatura
    if (temperatura >= TEMP_MAX) {
        gpio_put(LED_REFRIGERACAO, 1);
        gpio_put(LED_AQUECIMENTO, 0);
        printf("Refrigeração ativada!\n");
        atualizar_display("Refrigerando", temperatura);
        ajustar_temperatura();
    } else if (temperatura <= TEMP_MIN) {
        gpio_put(LED_AQUECIMENTO, 1);
        gpio_put(LED_REFRIGERACAO, 0);
        printf("Aquecimento ativado!\n");
        atualizar_display("Aquecendo", temperatura);
        ajustar_temperatura();
    } else {
        gpio_put(LED_REFRIGERACAO, 0);
        gpio_put(LED_AQUECIMENTO, 0);
        printf("Temperatura estável. \n");
        atualizar_display("Estavel", temperatura);
        variar_temperatura_estavel();
    }
    
    sleep_ms(2000);
}

int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}