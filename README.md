This project aims to monitor a room's air, temperature, and humidity levels and warn the user of any dangerous substances or conditions in its surroundings. 

Before its proper user, the equipment needs to undergo a 24-hour calibration (to stabilize and preheat the components), so the MQ135's voltage is stable.
Calibration must occur outdoors with temperatures around 22c and 30-40% humidity levels.

Also, the DHT 22 sensor must be adjusted in the source code according to a precise thermometer (since its initial state can be off by + or - 2c)

This project uses the following components:
[DHT 22](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)
[MQ 135](https://www.electronicoscaldas.com/datasheet/MQ-135_Hanwei.pdf)
[Arduino UNO](https://store.arduino.cc/products/arduino-uno-rev3?selectedStore=eu)