🛠️ Guía de Desarrollo: VS Code + PlatformIO + Wokwi

Esta guía explica cómo configurar tu entorno de desarrollo profesional utilizando **Visual Studio Code**, **PlatformIO** y el simulador **Wokwi** (aprovechando su licencia gratuita de prueba de 30 días), adaptado específicamente para el **Destapador de Medicinas Inteligente V1** basado en ESP32.



 📋 Pasos de Configuración y Ejecución

 1️⃣ Instalación del Entorno en VS Code
1. Descarga e instala [Visual Studio Code](https://code.visualstudio.com/).
2. Abre VS Code, ve a la sección de **Extensiones** (`Ctrl + Shift + X` o icono de bloques a la izquierda) y busca e instala:
   - **PlatformIO IDE**
   - **Wokwi Simulator** (Wokwi for VS Code)

 2️⃣ Activación de la Licencia Gratuita de Wokwi (30 días)
1. Al instalar la extensión de Wokwi o abrir un archivo de simulación por primera vez, inicia sesión o regístrate en Wokwi.
2. Activa el periodo de prueba gratuito de **30 días** para habilitar las características avanzadas de simulación de ESP32 y periféricos.

3️⃣ Configuración del Archivo `platformio.ini`
Asegúrate de que tu archivo de configuración `platformio.ini` en la raíz del proyecto tenga la siguiente estructura para gestionar las librerías del LCD y los servomotores:

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps =
    marcoschwartz/LiquidCrystal_I2C
    madhephaestus/ESP32Servo

4️⃣ Creación del Archivo wokwi.toml
Crea un archivo llamado wokwi.toml en la raíz de tu proyecto con el siguiente contenido exacto para que el simulador reconozca los binarios compilados:

[wokwi]
version = 1
firmware = '.pio\build\esp32dev\firmware.bin'
elf = '.pio\build\esp32dev\firmware.elf'

🚀 Cómo Compilar y Subir el Proyecto
Paso A: Compilar el Código (Build)
Antes de subir el programa a la placa o probarlo en el simulador, debes compilar el código para verificar que no existan errores de sintaxis o dependencias faltantes.

-Desde la barra inferior de PlatformIO: Haz clic en el icono del check (✔) ubicado en la barra de estado azul en la parte inferior izquierda de VS Code.

-Resultado exitoso: La terminal mostrará el mensaje [SUCCESS] junto con el uso de memoria de programa y RAM.

Paso B: Simular en Wokwi (Opcional)
Si deseas verificar el funcionamiento con el archivo diagram.json antes de conectarlo físicamente:

1. Abre la paleta de comandos con Ctrl + Shift + P.

2. Escribe y selecciona: Wokwi: Start Simulator.

Paso C: Subir a la Placa Física (Upload)
Una vez que la compilación sea exitosa y tu ESP32 esté conectado por USB:

1. Conecta tu tarjeta ESP32 a un puerto USB de la computadora.

2. Haz clic en el botón de la flecha hacia la derecha (➡) en la barra inferior de PlatformIO para iniciar la subida.

3. Si la placa lo requiere, mantén presionado el botón BOOT físico de la tarjeta hasta que comience el proceso de escritura de la memoria.

4. Resultado exitoso: La terminal indicará Hard resetting via RTS pin... [SUCCESS] al finalizar la transferencia.

Nota de solución de problemas (Upload):
Si surge algún error al realizar el Upload del código, abre el Administrador de dispositivos en Windows para verificar que los controladores estén actualizados (comúnmente el controlador del chip CP210x requiere actualización).
Si es necesario, descarga el instalador para Windows (versión x64) desde la página oficial de Silicon Labs, descomprímelo e instálalo para restablecer la comunicación correcta con la placa.
URL Driver:https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads
