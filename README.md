First Read Me; Still Working on it, but heres the jist of it. Also, need to reorganize the folders. 

# Gardenpi
Raspberry Pi with an IR Pi Camera installed
Arduino Uno R3; Soil Moisture Sensor, DHT22 Humidity Sensor, Water Level Sensor, 5v Water Pump to mix the water bucket, 5v Water Pump to water plant.

The contents of the html folder are placed in the Raspberry pi (./var/www/html)
Raspberry pi runs the stream.py file, which runs a local Apache website
The website casts the Pi Camera, and runs a serial monitor connnected to the Arduino via USB (ttyACM0)
Garden_V3.ino is uploaded to the Arduino Uno, which controls and monitors the hardware. 

I also made the python script into a service to run when the pi boots. (Deets soon to come)

In the website, you can view the plant via the webcast and you can send commands via
