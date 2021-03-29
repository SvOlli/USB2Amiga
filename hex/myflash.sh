#!/bin/sh

DEVICE="/dev/ttyUSB0"
HEXFILE=""

usage()
{
   cat <<EOF
usage: $0 (<device>) <hexfile>

Will try to use avrdude to flash the specified hexfile into the Arduino.
The following configuration is assumed:
- ATmega328p @ 3.3V
- Arduino bootloader @ 57600 Baud
- Serial interface @ ${DEVICE} (can be changed by parameter)

(This script is called "myflash.sh" because it might not work for you!)
EOF
}

for i; do
case "${i}" in
/dev/*) DEVICE="${i}" ;;
*) if [ -n "${HEXFILE}" ]; then usage; exit 1; else HEXFILE="${i}"; fi ;;
esac
done

if [ -z "${HEXFILE}" -o ! -f "${HEXFILE}" ]; then
   usage
   if [ -n "${HEXFILE}" ]; then
      echo "ERROR: hexfile '${HEXFILE}' does not exist"
   fi
   exit 1
fi

if [ ! -c "${DEVICE}" ]; then
   usage
   echo "ERROR: device '${DEVICE}' does not exist or is not a character device"
   exit 1
fi

exec avrdude -v -patmega328p -carduino -P"${DEVICE}" -b57600 -D -Uflash:w:"${HEXFILE}":i
