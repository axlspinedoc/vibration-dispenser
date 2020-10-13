<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>

<h3 align="center">Dispensador Vibratorio</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()


</div>

---

<p align="center"> Automatización de un equipo dispensador de alimentos a granel
    <br> 
</p>

# 🧐 Acerca del proyecto <a name = "about"></a>

Este repositorio contiene el código fuente del sistema operativo de una dispensador a granel utilizando un microcontrolador Amega2560

# 🏁 Preparación necesaria <a name = "getting_started"></a>

1. Instale la herramienta [VSCode](https://code.visualstudio.com)

2. Abra el programa y entre a _File_, _Preferences_, _Extensions_.

3. En el buscador, introduzca _C/C++_ e instale la extensión.

4. Nuevamente en el buscador, introduzca ahora _PlatformIO IDE_ e instale.

5. Una vez instalados correctamente, cada vez que abra VSCode aparecerá la pantalla de inicio con el anuncio "Welcome to PlatformIO"

6. Descargue una copia de este repositorio desde la opción _Code_, _Descargar Zip_. Descomprima en una ubicación conocida.

7. Desde la pestaña de _home_ de PlatformIO, seleccione _import Arduino project_

8. El programa cargara el proyecto y actualizará los documentos dependiendo la computadora donde se abra. *Espere 5 minutos*, esto permitirá que esté listo para programar

9. Para verificar que está listo busque el botón _Build_ en la barra inferior azul, marcado con el símbolo de palomilla

10. Si en el panel inferior aparece la instrucción [SUCCESS], está listo para programar. Conecte el Arduino a su computadora con el cable USB

11. Presione el botón _Upload_ en la barra inferior azul, marcado con una flecha hacia la derecha. Este botón está inmediatamente a la derecha del botón con la palomilla.

12. Pasados 15 segundos, el _Arduino_ se habrá reinicializado. ¡Ha actualizado exitosamente su microcontrolador!

# Para realizar Ajustes

Abra el archivo _utilities.h_ dentro de la carpeta _lib/inc_

Desde aquí puede editarse:

1. Producto a cargar al iniciar el equipo
2. Peso inicial default
3. Tiempo de espera cuando termina de vaciarse la Tolva
4. Selección del modo del relevador
5. Posiciones de la puerta en el estado ABIERTO y CERRADO
6. Sensibilidad de la báscula durante dispensado y vaciado
7. Calibración de báscula
8. Tiempo de señal de _Relay_
9. Tiempo de espera después de dispensar en tolva

Para editar la base de datos de productos abra el archivo _productos.h_ dentro de la carpeta _lib/inc_

Siga las indicaciones del archivo para agregar productos seleccionables desde la pantalla

# ⛏️ Built Using <a name = "built_using"></a>

- [Visual Studio Code](https://code.visualstudio.com) - IDE
- [PlatformIO](https://platformio.org) - Embedded development IDE
- [Arduino Mega](https://www.arduino.cc) - Prototyping

# ✍️ Authors <a name = "authors"></a>

- [@axlspinedoc](https://github.com/axlspinedoc) - Developer

# 🎉 Acknowledgements <a name = "acknowledgement"></a>

- Amber Macias
