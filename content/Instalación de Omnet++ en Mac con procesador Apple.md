---
modified: 2025-03-11T15:11:43-06:00
created: 2025-03-11T06:34:43-06:00
title: Instalación de Omnet++ en Mac con procesador Apple
---
# Guía para instalar Omnet++ en MacOS con procesador Apple (M1, M2)

Esta guía describe los pasos para instalar OMNeT++ 6.1.0 en una computadora con sistema operativo MacOs (15.3.1 -24D70 )  y procesador M2.

Esta basada en la [Guía de Instalación oficial](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)  de Omnet++

## Instrucciones Paso a Paso

1. Descargar el archivo .zip de la [pagina de descargas de Omnet++ ](https://omnetpp.org/download/), en mi caso descargué el archivo para **MAC OS (AARCH64)**

2. Mover el archivo .zip descargado en la siguiente ruta dentro de la computadora, donde `<usuario>` va ser el nombre del usuario que se esta utilizando.

```sh
/Users/<usuario>/
```

3. Descomprimir el archivo .zip  dentro dela ruta anterior

```
cd /Users/<usuario>
tar zxvf omnetpp-6.1-macos-aarch64.tgz
```

El paso anterior creó la carpeta `/Users/<usuario>/omnetpp-6.1`, esta es la ruta donde estará instalado Omnet++

4. Instalar las herramientas de línea de comandos de Xcode (Command Line Tools) en macOS, ejecutar el siguiente comando en la terminal:

```sh
xcode-select --install
```

En mi caso, el  **Command Line Tools** ya estaba instalada, por lo que me salté ese paso al principio, sin embargo cuando intenté compilar el programa me dió un error, lo resolví borrando la instalación anterior y volviendo a instalar la herramienta:

```bash
sudo rm -rf /Library/Developer/CommandLineTools
sudo xcode-select --reset
xcode-select --install
```

Al momento de instalarla nuevamente, se muestra una ventana emergente en la cual se debe continuar con la instalación.

5. Instalar dependencias adicionales con Homebrew, ejecutar en la terminal:

```bash
brew install bison flex perl python@3 make qt@5 pkg-config doxygen graphviz openscenegraph
```

6. Editar el archivo `.zhprofile` y agregar estas lineas al archivo, luego reiniciar la terminal:

```bash
nano ~/.zprofile
```

Agregar o confirmar que aparezcan esas instrucciones:

```sh
eval "$(/opt/homebrew/bin/brew shellenv)"
export PATH="$(brew --prefix qt@5)/bin:$PATH"
export PATH="$(brew --prefix bison)/bin:$PATH"
export PATH="$(brew --prefix flex)/bin:$PATH"
export PATH="$(brew --prefix doxygen)/bin:$PATH"
export PATH="$(brew --prefix graphviz)/bin:$PATH"
export PATH="$(brew --prefix pkg-config)/bin:$PATH"
export PATH="$(brew --prefix make)/libexec/gnubin:$PATH"
export LDFLAGS="-L$(brew --prefix)/lib $LDFLAGS"
export CFLAGS="-I$(brew --prefix)/include $CFLAGS"
```
7. Luego nos movemos a la ubicación creada en el paso  3, y ejecutar los siguientes comandos para instalar otros pre-requisitos necesarios.

```bash
cd /Users/<usuario>/omnetpp-6.1
python3 -m venv .venv && source .venv/bin/activate
python3 -m pip install -r python/requirements.txt
 ```

8. Ahora vamos a  Preferences -> Privacy & Security -> Developer Tools, y activamos la Terminal

	![[Pasted image 20250311070059.png|400]]

9. Desactivar la protección de Gatekeeper a nivel global en macOS. Ejecutar en la termial:
	`
```
sudo spctl --global-disable
```

10. Probamos la ejecución del script para establecer las variables de entorno `setenv`.
	
```
cd /Users/<usuario>/omnetpp-6.1
source setenv
```

Si se ejecuta correctamente debe salir un mensaje como este:

```sh
Activating python virtual environment in '/Users/carlos.ramirez/omnetpp-6.1/.venv'
HOMEBREW detected, activating dependencies (qt@5, bison, flex, pkg-config, make).
Environment for 'omnetpp-6.1' in directory '/Users/carlos.ramirez/omnetpp-6.1' is ready.

Type "./configure" and "make" to build the simulation libraries.
When done, type "omnetpp" to start the IDE.
```

11. Luego podemos agregar las variables de entorno de forma permanente, para eso editamos el archivo `.zprofile`y agregamos la siguiente linea:

	```text
	[ -f "$HOME/omnetpp-6.1/setenv" ] && source "$HOME/omnetpp-6.1/setenv"
	```

	Luego reiniciamos la terminal, y debería salir el mismo mensaje del paso anterior.

12. Preparar el entorno de compliación de Omnet++, ejecutar en la terminal:
	
	```sh
	./configure
	```

13. Compilar el software Omnet++

```
make -j4
```

14. Iniciamos el IDE de Omnet++ 

```
omnetpp
```

Seleccionar el directorio del espacio de trabajo por defecto, haciendo click en Launch:

![[Pasted image 20250311105641.png#center|400]]

Y debe abrir la pantalla de inicio del IDE de OMNeT++
![[Pasted image 20250311105946.png]]Con esto finaliza el proceso de instalación de OMNeT++

https://carloslramirez.com/DigitalJoungle

git remote set-url origin REMOTE-URL https://github.com/CarlosLRamirez/DigitalJungle.git