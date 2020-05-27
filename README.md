# ESP32_Spiffy_Duotone
This is some fancy code for an ESP32 to turn it into a Bluetooth controlled watch/music player

Parts needed:
ESP32
15-led Neopixel Strip (a quick modification to the code can allow for different sizes)
Piezo Buzzer / Speaker / Headphones (really anything that can receive an audio signal)
A power supply of some sort I guess, maybe a battery?

How to wire: (I used transistors for the buzzers)
Buzzer1 -> 4
Buzzer2 -> 25
Neopixel -> 18

How to upload code to board:
Download the Arduino IDE and run it
You will want to change line 280, to choose the bluetooth device name
Go to "Arduino > Preferences", paste this into the "Additional Boards Manager URLs": https://dl.espressif.com/dl/package_esp32_index.json
Go to "Tools > Board > Board Manager", and install "esp32" (I have 1.0.4 installed, but use whatever works)
If you need more help with installation, go here: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
Go to "Tools", for the board, select "ESP32 Dev Module"
Stay in the "Tools" menue for the next few steps
For the Flash Size, select "4MB (32Mb)"            //This may be different if you are using a different kind of board
For the Partition Scheme, select "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)"   //This also may be different
For the Programmer, select "AVRISP mkII"
Select your port (should be something like usbserial-##### or wchusbserial-#####, numbers will vary)
If you can't find the port, then install some drivers: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
Click on "ESP32 Sketch Data Upload" (this will upload the spiffs, which is where all the music is stored)
Watch the consol text at the bottom
Once the sketch data upload is finished, click on the sideways arrow in the top left corner labeled "Upload" to upload the code
Once again, watch the consol text at the bottom
Once the upload is finished you should hear a little beep sequence and you are good to go!
