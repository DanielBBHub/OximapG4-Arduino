# PROYECTO DE BIOMETRIA

# Repositorio arduino

# En este repositorio se encuentran los códigos correspondientes al microcontrolador y el sensor.


Para subir el programa es necesario poner el puerto COM que corresponda a la entrada USB con la que se desea transmitir al microcontrolador (Sparkfun Pro nRF82540 mini) y asegurarse de tener bien instalada la placa.

Si la placa dejase de recibir los programas de arduino sera necesario forzar el bootloader, puedes pulsar dos veces el botón de reset (RST) o bien pulsar el botón 13 y el reset al mismo tiempo.

El programa utilizado recibe datos del sensor DGS-NO2 968-043 y realiza una media con ellos. Esto ocurre cada segundo y cada vez que recibe el dato del gas y el de la media lo guarda en el minor y el manor del iBeacon. Una vez hecho esto, envia el iBeacon que recibirá la app.



