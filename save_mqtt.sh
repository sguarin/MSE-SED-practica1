#!/bin/bash
# Con openwrt debemos cambiar lo anterior por #!/bin/sh
# Configuración del broker y topic a escuchar.
# Cambiar por valores propios las siguientes variables:
broker="192.168.12.2"
port="1883"
topic2="prueba/topic2"
topic3="prueba/topic3"
archivo="reporte.txt"
#------------------------------------
#Ponemos el cliente de mosquitto escuchando
mosquitto_sub -t $topic2 -t $topic3 -h $broker -p $port | while read value; do
ts=$(date "+%Y-%m-%d %H:%M:%S") # Guardamos la fecha y hora actual en una variable.
# Guardamos valores uno detrás de otro:
echo "$ts $value" >> $archivo # guardamos datos en archivo
echo " $value" # sacamos el resultado por consola
done
