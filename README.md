# caribdis-cluster
Caribdis is a tiny ARM cluster built with love.


## Caracterísiticas del Clúster

La primera versión del Clúster va a estar compuesta de 6 nodos, un maestro/manager y cinco esclavos/workers. Todos los workers son placas [Orange Pi PC](http://linux-sunxi.org/Xunlong_Orange_Pi_PC) que cuentan con 1Gb de RAM y un procesador H3 quad core ARM [Cortex-A7](http://linux-sunxi.org/H3) de 32 bits a 1.2Ghz. El manager es una [Raspberry Pi 3 B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/) con un 1Gb de RAM y un procesador Quad Core Broadcom BCM2837 de 64 bits a 1.2GHz. El nodo maestro tendrá conectado una memoria USB de 128Gb compartida mediante NFS.

Las placas se apilaran entre ellas usando standoffs M2.5, y serán colocadas en vertical para maximizar al máximo la disipación de calor.

Para alimentar todo el clúster se ha optado por un [cargador Anker de 70W y 10 puertos](https://www.anker.com/store/PowerPort-10-Ports/A2133111).El jack de alimentación de las OPis no es estándar así que las alimentaremos directamente a traveś de su GPIO. Para esto conectaremos los 5 voltios al pin 4 y la tierra al pin 6. La Raspberry Pi será alimentada de forma estándar mediante su microUSB.

![OrangePiGPIO](http://cs5-3.4pda.to/8498940.png)

El switch elegido es un básico [Zyxel de 8 puertos](https://www.zyxel.com/es/es/products_services/8-Port-Desktop-Gigabit-Ethernet-Switch-GS-108B-v3/). La configuración de red será la siguiente:

```
RPI     caribdis0.local     192.168.32.1
OPI     caribdis1.local     192.168.32.101
OPI     caribdis2.local     192.168.32.102
OPI     caribdis3.local     192.168.32.103
OPI     caribdis4.local     192.168.32.104
OPI     caribdis5.local     192.168.32.105
```

En ella, la Raspberry Pi actuará como NAT, proporcionando conexión a internet de los workers a través de su interfaz web. La idea tras esta configuración es permitir que el clúster sea lo más portable posible. De esta forma, con tan sólo conectar la alimentación nuestro clúster estará operativo en cualquier parte de la casa. Otra posible mejora es la de añadir otra interfaz inalámbrica a la Rasperrby Pi que actúe como punto de acceso wifi de tal forma que incluso en sitios dónde no tengamos cobertura con nuestro router aún podamos conectarnos al clúster mediante wifi y administrarlo.

