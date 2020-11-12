# Instalacion

## Instalar PIP en caso de ser necesario 

Para debian/ubuntu ejecutar:

  ```
  apt-get install python-pip
  ```
Para fedora/centos/redhat ejecutar:

  ```
  dnf install python-pip
  ```
## Instalar Platformio

  ```
  pip install --user platformio
  ```
## Instalar plataforma ESP32 en caso de ser necesario
  ```
  platformio platform install espressif32
  ```
## Instalar plataforma para ESP8266 (ESP12 o superior) en caso de ser necesario
  ```
  platformio platform install espressif8266
  ```
# Como empezar un desarrollo de cero

## Inicializar proyecto para ESP12
Ademas de la plataforma existe soporte y mapeo de pines para varias placas. Por ej para ESP12E dentro de la plataforma espressiff8266 se utiliza el id nodemcuv2. Para ESP32 esp32dev. Para ESP01 esp01 (512k) o esp01_1m (1M), 

  ```
  mkdir -p MSE-SED-prueba
  platformio init --board nodemcuv2 --ide vscode --project-dir MSE-SED-prueba
  cd MSE-SED-prueba
  ```
  Nota: Tiene soporte para otras ide.

## Instalar PubSubClient

  ```
  platformio lib install knolleary/PubSubClient
  platformio run
  cp .pio/libdeps/nodemcuv2/PubSubClient/examples/mqtt_esp8266/mqtt_esp8266.ino src/main.cpp
  platformio run
  ```
## Flashear y escuchar serie
  ```
  platformio run --target upload --upload-port /dev/ttyUSB0
  platformio device monitor --port /dev/ttyUSB0 --baud 115200
  ```

# Sobre este repositorio

## Configuracion

Editar upload_port en platformio.ini de acuerdo al FTDI utilizado y placa utilizada

## Compilar firmware

  ```
  platformio run
  ```

## Flash firmware

  ```
  platformio run  --environment esp8266_development --upload_port /dev/ttyUSB0
  ```

o

  ```
  platformio run  --environment esp32_development --upload_port /dev/ttyUSB0
  ```

## Chequear sanidad de codigo
  ```
  platformio check
  ```

## Para ejecutar en un dispositivo test unitarios
  
  ```
  platformio test --environment esp32_development
  ```

## Para ejecutar un test unitario en particular

  ```
  platformio test -f test_MQTT --environment esp32_development
  ```

