# Projeto-final-Embarcatech
# Controle de Temperatura com Raspberry Pi Pico

[Link do vídeo](https://drive.google.com/drive/u/2/folders/1spYYSiR94fhC-RV3um1hSqotiMEX4bOS)

## 📌 **Objetivo**
Este projeto implementa um sistema de monitoramento e controle de temperatura utilizando o Raspberry Pi Pico. O sistema usa um sensor de temperatura conectado ao ADC do microcontrolador, LEDs indicativos para refrigeração e aquecimento, e um display OLED SSD1306 para exibir informações.

## 🛠️ **Componentes Utilizados**
- **Microcontrolador**: Raspberry Pi Pico
- **Sensor de Temperatura**: Leitura via ADC
- **Display OLED**: SSD1306 via I2C
- **LEDs Indicadores**:
  - LED de refrigeração
  - LED de aquecimento
- **Outros**: Resistores, jumpers, protoboard

## 🔧 **Funcionalidades**
- Monitoramento da temperatura ambiente em tempo real.
- Exibição da temperatura no display OLED SSD1306.
- Controle automático de aquecimento e refrigeração baseado em limites pré-definidos.
- Variação simulada da temperatura para testes. 

## ⚙️ **Estrutura do Código**
O código está organizado da seguinte forma:

- **setup()**: Inicializa o ADC, GPIOs, comunicação I2C e display OLED.
- **loop()**: Verifica a temperatura, ativa os LEDs conforme necessário e atualiza o display.
- **atualizar_display()**: Atualiza a informação no display OLED.
- **ajustar_temperatura()**: Simula um ajuste mais rápido quando a temperatura está muito acima/abaixo dos limites.
- **variar_temperatura_estavel()**: Simula variação aleatória da temperatura quando dentro dos limites.

## 🔧 **Estrutura do Código**
O código está organizado da seguinte forma:

- **setup()**: Inicializa o ADC, GPIOs, comunicação I2C e display OLED.
- **loop()**: Verifica a temperatura, ativa os LEDs conforme necessário e atualiza o display.
- **atualizar_display()**: Atualiza a informação no display OLED.
- **ajustar_temperatura()**: Simula um ajuste mais rápido quando a temperatura está muito acima/abaixo dos limites.
- **variar_temperatura_estavel()**: Simula variação aleatória da temperatura quando dentro dos limites.

### 📥 Clonando o Repositório
```bash
  git clone https://github.com/EA-Igor/Projeto-final-Embarcatech.git
```

### 🔧 Compilação e Upload
1. **Compile o código** usando o **Pico SDK**.
2. **Faça o upload do firmware** para o **RP2040**.
3. **Conecte os componentes** de acordo com o diagrama fornecido.
4. **Abra o monitor serial** para visualizar os avisos e o display OLED.

## 📹 Entrega e Demonstração

### Requisitos da Entrega
- **Código-fonte**: O código será avaliado quanto à organização, funcionamento e clareza.
- **Vídeo de demonstração**: Um vídeo de até **5 minutos**, contendo:
  - Demonstração do funcionamento do projeto.
  - Explicação das funcionalidades implementadas.
  - Execução na placa **RP2040**.

- [Link do vídeo](https://drive.google.com/drive/u/2/folders/1spYYSiR94fhC-RV3um1hSqotiMEX4bOS)

---
### 📌 Observações Finais
Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou contribuir com melhorias no repositório. 🚀
