# 🚀 Destapador de Medicinas Inteligente V1

Dispositivo inteligente basado en **ESP32** para la gestión y dispensación automatizada de medicamentos, controlado mediante pantalla LCD I2C, potenciómetro, pulsador y servomotores.

---

## 📋 Instrucciones para compilar y probar en tu PC

### 1️⃣ Descargar el proyecto
* Haz clic en el botón verde **`<> Code`** en la parte superior del repositorio y selecciona **`Download ZIP`**.
* Descomprime la carpeta en tu computadora.

### 2️⃣ Instalar Arduino IDE
* Descarga e instala [Arduino IDE](https://www.arduino.cc/en/software) (versión 1.8.x o superior).

### 3️⃣ Configurar el soporte para ESP32
* En Arduino IDE, ve a **Archivo > Preferencias**.
* En *Gestor de URLs Adicionales de Tarjetas*, agrega la siguiente URL:  
  `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
* Ve a **Herramientas > Tarjeta > Gestor de Tarjetas**, busca **esp32** e instálalo.

### 4️⃣ Instalar Librerías Requeridas
* Ve a **Programa > Incluir Librería > Administrar Bibliotecas**.
* Busca e instala:
  - **`LiquidCrystal_I2C`** (por Frank de Brabander)
  - **`ESP32Servo`** (por Kevin Harrington)

### 5️⃣ Cargar el Proyecto
* Abre el archivo `.ino` dentro de la carpeta descargada con el Arduino IDE.
* Conecta tu ESP32 por USB.
* Ve a **Herramientas > Placa** y selecciona **ESP32 Dev Module**.
* Selecciona el puerto COM correcto en **Herramientas > Puerto**.
* Haz clic en el botón **Subir** (si es necesario, mantén presionado el botón **BOOT** de la placa durante la conexión).


**Nota de solución de problemas (Upload):** Si surge algún error al realizar el Upload del código, abre el Administrador de dispositivos en Windows para verificar que los controladores estén actualizados (comúnmente el controlador del chip CP210x requiere actualización). Si es necesario, descarga el instalador para Windows (versión x64) desde la página oficial de Silicon Labs, descomprímelo e instálalo para restablecer la comunicación correcta con la placa.

**URL Driver:** https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads
