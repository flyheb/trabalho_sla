# 🌱 Trabalho Sistemas Lógicos para Automação

Sistema de Monitoramento Agrícola com ESP32

---

## ✨ Descrição

Este projeto realiza o monitoramento de umidade do solo, umidade do ar e temperatura do ar utilizando um **ESP32**, sensor **DHT11** e um sensor de umidade do solo. Os dados são exibidos em tempo real via uma interface web responsiva hospedada pelo próprio ESP32.

---

## 🚀 Funcionalidades Principais

- 📊 **Leitura de sensores:**
  - Umidade do solo (sensor analógico)
  - Umidade do ar e temperatura (DHT11)
- 🌐 **Servidor Web Integrado:**
  - Interface web moderna e responsiva para visualização dos dados
  - Atualização automática dos dados a cada 4 segundos
  - Botão para atualização manual
  - Alertas visuais para valores fora do ideal
- 📡 **Wi-Fi Access Point:**
  - O ESP32 cria uma rede Wi-Fi própria para acesso à interface

---

## 📚 Bibliotecas Utilizadas

- [`ESPAsyncWebServer` by lacamera (v3.1.0)](https://github.com/me-no-dev/ESPAsyncWebServer)
- [`AsyncTCP` by dvarrel (v1.1.4)](https://github.com/dvarrel/AsyncTCP)
- [`DHT sensor library` by Adafruit (v1.4.6)](https://github.com/adafruit/DHT-sensor-library)

---

## 🖥️ Interface Web

A interface exibe:

- 🌱 Umidade do Solo (%)
- 💧 Umidade do Ar (%)
- 🌡️ Temperatura do Ar (°C)

**Alertas visuais são exibidos quando:**
- 🌱 Umidade do solo < 20% ou > 80%
- 💧 Umidade do ar < 30% ou > 70%
- 🌡️ Temperatura do ar < 15°C ou > 35°C

---

## 🛠️ Pinos Utilizados no ESP32

| Função                | Pino ESP32 |
|-----------------------|:----------:|
| Sensor DHT11 (dados)  |   GPIO 4   |
| Sensor Umidade Solo   |   GPIO 34  |

---

## 📋 Como Usar

1. **Alimente o ESP32 e conecte os sensores:**
   - DHT11: pino de dados no GPIO 4
   - Sensor de umidade do solo: saída analógica no GPIO 34

2. **O ESP32 cria uma rede Wi-Fi:**
   - SSID: `teste_esp`
   - Senha: `teste123`

3. **Conecte-se à rede Wi-Fi pelo seu dispositivo e acesse o IP exibido no monitor serial (geralmente `192.168.4.1`) pelo navegador.**

---

## 📁 Estrutura dos Arquivos

- `main.ino`: Código principal do ESP32 (leitura dos sensores, servidor web, lógica de cálculo)
- `pagina_html.h`: Interface web em HTML/CSS/JS embutida no firmware

---

## 👨‍💻 Créditos

Gustavo Oestreich - UFSM 
2025

---