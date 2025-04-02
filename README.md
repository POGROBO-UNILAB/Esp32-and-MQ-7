![BannerProject](https://raw.githubusercontent.com/POGROBO-UNILAB/Esp32-and-MQ-7/refs/heads/main/img/BannerAruanaUpdate.jpg)

---

Este projeto demonstra a leitura da concentração de Monóxido de Carbono (CO) de um sensor MQ-7 usando um microcontrolador ESP32. O código utiliza a biblioteca MQUnifiedsensor para interação simplificada com o sensor.

> [!CAUTION]
> CO é um poluente atmosférico significativo liberado pela queima incompleta de combustíveis fósseis (carros, indústrias, etc.). A poluição por CO contribui para problemas respiratórios e doenças cardíacas. 

## 🪛 Esquemático

![BannerProject](https://raw.githubusercontent.com/POGROBO-UNILAB/Esp32-and-MQ-7/refs/heads/main/img/esquematico.jpg)

## Ambiente de Desenvolvimento e Bibliotecas

| Componente  |  Versão      |
|-------------|--------------|
| Arduino IDE | 2.3.4v       |
| MQUnifiedsensor | V3.0.0   | 

## 🖥️ Código completo

```cpp
// Inclui a biblioteca necessária para o sensor MQ-7.
#include <MQUnifiedsensor.h>

// Define o tipo de placa, resolução de tensão, pino, tipo de sensor e resolução de bits do ADC.
#define Board "ESP32"
#define Voltage_Resolution 3.3
#define Pin 34
#define Type "MQ-7"
#define ADC_Bit_Resolution 12

// Define a razão da resistência do sensor em ar limpo.
#define RatioMQ7CleanAir 27.5

// Cria uma instância da classe MQUnifiedsensor.
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

// Função de configuração.
void setup() {
  // Inicializa a comunicação serial.
  Serial.begin(9600);

  // Define o método de regressão. (1 é o padrão, polinomial)
  MQ7.setRegressionMethod(1);

  // Define os parâmetros de calibração A e B do sensor. Estes são específicos do sensor.
  MQ7.setA(99.042);
  MQ7.setB(-1.518);

  // Informa ao usuário que o sensor está sendo calibrado.
  Serial.println("Calibrando... Aguarde em ar limpo.");

  // Atualiza as leituras do sensor.
  MQ7.update();

  // Calibra o sensor usando o valor RatioMQ7CleanAir e armazena o valor R0.
  float r0 = MQ7.calibrate(RatioMQ7CleanAir);
  MQ7.setR0(r0);

  // Verifica erros durante a calibração.
  if (isinf(r0)) {
    Serial.println("Erro: R0 infinito (circuito aberto). Verifique a fiação.");
    while (1); // Para a execução se R0 for infinito.
  }
  if (r0 == 0) {
    Serial.println("Erro: R0 zero (curto-circuito). Verifique a fiação.");
    while (1); // Para a execução se R0 for zero.
  }

  // Indica que a calibração está completa.
  Serial.println("Calibração completa.");

  // Habilita a depuração serial.
  MQ7.serialDebug(true);
}

// Função do loop principal.
void loop() {
  // Atualiza as leituras do sensor.
  MQ7.update();

  // Lê os valores do sensor.
  MQ7.readSensor();

  // Imprime os dados do sensor via serial.
  MQ7.serialDebug();

  // Introduz um pequeno atraso.
  delay(500);
}
```
---

## 📄 Licença

   >GNU GENERAL PUBLIC LICENSE Version 3

## 🚀 Agradecimentos

  >Este projeto foi baseado na iniciativa Ribbit Network!

## Citação

>Projeto de extensão Ensino de Programação e Robótica nas Escolas Públicas (PROGROBÔ)/UNILAB. (2025). Esp32-and-MQ-7 (v1.0.0.0). Zenodo. https://doi.org/10.5281/zenodo.15126879
