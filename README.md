
# 2048 Game

## Introduction  
* This project implements the popular game "2048," commonly found on smartphones and computers, now brought to life on a microcontroller.  
* The purpose of this game is simple yet engaging: the player slides numbered tiles across a grid, merging them to reach the desired 2048 tile.  
* The idea behind this project was to create an interactive and engaging experience for my robotics course, and what could be more interactive than a game? Over the years, one game that has always stood out to me and kept me entertained on my phone is 2048. So I decided to take on the challenge of implementing a new version of this game using a microcontroller.  
* The main utility of this game is mainly for learning. It offers a practical insight into how both software and hardware components communicate in order to create a fully functional project.   
## Project Description 

   A 4x4 game board is displayed on an LCD screen. The player interacts with the game using a joystick. There are four possible directions in which the tiles can move using the joystick: N(up), S(down), E(left) and W(right). By pressing the joystick button, the player can return to the previous game state, effectively undoing the last action (the last move will be reversed). The joystick is also used for starting the game. The player wins when they reach the 2048 tile. The game continues until the board is full, and no further moves or merges are possible. A leaderboard keeps track of every player's name and their highest achieved score.  
   
   ### Block diagram  
![image](https://github.com/user-attachments/assets/8d8c14bb-bbcc-4d6f-80ce-eb6894100840)  

### Components description  

#### Microcontroller  
            The project is based on the ESP32 microcontroller, using the NodeMCU ESP32 development board that integrates the ESP32-WROOM-32 module (processor). The ESP32 is ideal for handling complex tasks, including high-resolution graphics, making it perfect for controlling a high-resolution LCD.    

* Power Supply: The development board is powered via a USB-C connector, which provides 5V. However, the ESP32 itself operates at 3.3 V for proper functioning.  

* Interfaces: In this project the ESP32 is going to communicate with the components using the next communication interfaces: SPI, ADC, and GPIO. These interfaces are used to connect various external modules like the LCD and the joystick.

### Flash memory
            In order to store the leaderboard, I decided to use the internal memory (Flash) of the ESP32. The Flash memory will be managed using the Non-Volatile Storage (NVS) system, which allows the leaderboard data (player names and scores) to persist even after the device is powered off. The library that implements it is [Preferences.h](https://components101.com/modules/joystick-module). 

* Communication: The communication interface is QSPI and is managed by the hardware.  

#### LCD Display (TFT 3.5” ILI9488 SPI)  
            Because I choose to recreate the popular 2048 game, of course I need a screen to display the grid and the blocks. I chose a 3.5-inch TFT LCD with a resolution of 480x320 pixels, driven by an ILI9488 controller. The display communicates with the microcontroller via the SPI interface, which allows for fast data transfer required for rendering complex images in real-time. To use the LCD screen I included the [TFT_eSPI.h library](https://github.com/Bodmer/TFT_eSPI).

* Power supply: The LCD display requires a 3.3V power supply.  

* Communication: The communication interface is a 4-wire SPI interface, which is going to be used for receiving data from the microcontroller at every correct move from the joystick.  

#### Joystick  
            The main action of the game is moving the components (the blocks) on the display. But how to move them? I choose a joystick to take care of this task.  

            The joystick is used to allow the player to control the movement of the blocks on the screen. The joystick has two axes (X and Y) for directional control, along with a button for additional functionality (start game, return to the last block configuration).  

* Power supply: The joystick requires 5V to operate.  

* Communication: The joystick communicates with the ESP32 via ADC (Analog-to-Digital Converter) for the X and Y axes (it’s needed for the up, down, left, and right movements). The button of the joystick is connected to a GPIO pin (software: it triggers an interrupt each time it is pressed).  


#### ESP32 and communication  
            Starting with the core of the project, the ESP32 microcontroller is connected to both the LCD display and the joystick. It receives data from the joystick and transmits data to the LCD display. The data that the microcontroller receives from the joystick comes from the ADC (for the joystick's X and Y axis movement) or from a GPIO pin (for the button press). The ADC provides the coordinates of the joystick (representing movement along the X and Y axes), or the GPIO pin reads the low-level signal from the button when pressed, so the microcontroller can interpret these inputs and transmit the appropriate changes to the LCD.  

            The LCD receives data via the SPI interface, specifically through the MOSI (Master Out Slave In) line. This transmission happens after the SCK (Serial Clock) is set to the correct frequency, and the LCD is selected using the CS (Chip Select) pin. The SPI protocol ensures fast data transfer, which is ideal for real-time updates of the game state on the LCD display. At the end of the game the player's name and score are going to be saved in the Flash memory.

## Hardware Design  
### Electrical diagram
<img src="https://github.com/user-attachments/assets/9011578e-7e49-4d31-9a70-444d3515cf47" width="600" height="400" />

### Bill of materials
| Component  | Image | Model    | Number| More information |
| ------------- | ------------- | -------------| -------------| -------------|
| Breadboard  |<img src="https://github.com/user-attachments/assets/55cbcf73-1f63-4177-8bd7-0ffa49542146" width="200" height="150" />|Full-sized | 1 | |
| ESP32  | <img src="https://github.com/user-attachments/assets/026a77de-8c00-4a6d-8f2f-649a00fe299f" width="200" height="150" />  | NodeMCU ESP32-WROOM-32 | 1 |[Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)|
| LCD display| <img src="https://github.com/user-attachments/assets/7055b37e-b3f8-48d7-8d5b-3e9809a03cc5" width="200" height="150" /> |ILI9488 | 1 |[Store](https://www.aliexpress.com/item/1005004804238339.html?srcSns=sns_WhatsApp&spreadType=socialShare&bizType=ProductDetail&social_params=60906366425&aff_fcid=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&tt=MG&aff_fsk=_EHL67gs&aff_platform=default&sk=_EHL67gs&aff_trace_key=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&shareId=60906366425&businessType=ProductDetail&platform=AE&terminal_id=c35ec2ea804245d1a09f2fcf4cb090a3&afSmartRedirect=y)|
|Joystick|<img src="https://github.com/user-attachments/assets/0b548984-f1c7-4462-a541-aa6dd952a5d7" width="200" height="150" />  | PS2| 1 | [Web page](https://components101.com/modules/joystick-module)|
|USB cable| <img src="https://github.com/user-attachments/assets/0eaf8059-35f7-44d0-9889-27fa78e2b5ef" width="200" height="150" />|Type C| 1 | 
| Jumper wires|<img src="https://github.com/user-attachments/assets/13757708-58f6-4406-9dc5-f7975762d86a" width="200" height="150" /> | Male-Male, Male-Female | many |  

### ESP32 pins  
<img src="https://github.com/user-attachments/assets/1107771c-000d-4476-985c-88bf267c6cad" width="600" height="400" />


| Pin | Functionality | Use|
| ------------- | ------------- | -------------|
| 3.3V | 3.3V power supply | Provides a 3.3V power supply to components in the circuit|
|GND| ground | Ground is the reference point for all voltages in the circuit, ensuring that the components operate correctly|
|GPIO34| ADC| Reads the VRx analog voltage from the joystick|
|GPIO35| ADC| Reads the VRx analog voltage from the joystick|
|GPIO25| Digital Input/Output (I/O)| Connected to the joystick's button, reads the button state|
|GPIO19| SPI MISO| Connected to the LCD, receives data from the LCD|
|GPIO23| SPI MOSI| Connected to the LCD, transmits data to the LCD|
|GPIO18| SPI SCLK| Connected to the LCD, generates the clock signal to synchronize data transfer between the controller and the peripheral|
|GPIO15| SPI CS| Connected to the LCD, used to enable or disable communication with the specific SPI peripheral|
|GPIO2| Data Command control pin (DC)| Connected to the LCD, Used to control whether the data sent to the display is interpreted as data or command|
|GPIO4| RST| Connected to the LCD, used to reset the peripheral|

### LCD display pins  

| Pin | Pin label  | Description| Use|
| ------------- | ------------- | ------------- | ------------- |
|1| VCC|3.3V power input| Powers the LCD|
|2| GND| Ground|Common ground for the circuit|
|3| CS| LCD chip select signal, low level enable| SPI communication with the ESP|
|4| RST| LCD reset signal, low level reset| Resets the LCD|
|5| D/C|LCD register / data selection signal, high level: register, low level: data| Selects whether data or a command is sent to the LCD|
|6| SDI(MOSI)| SPI bus write data signal| SPI communication, receives data from the controller|
|7| SCK| SPI bus clock signal| SPI communication, used for timing and synchronization|
|8| BL| Backlight |Backlight control, high level lighting, if not controlled, connect 3.3V always bright|
|9|SDO(MISO)| SPI communication, transmits data to the controller|

### Joystick pins  

| Pin | Pin label | Use|
| ------------- | ------------- | -------------|
|1| GND|Ground connection|
|2| VCC| Provides power to the joystick(3.3V)|
|3|VRx |Analog input pin for horizontal movement (X-axis)|
|4|VRy|Analog input pin for vertical movement (Y-axis)|
|5|SW|Digital input pin for the joystick button (used to detect button presses)|

### Hardware image  
 
<img src="https://github.com/user-attachments/assets/d70ff279-6f3f-4aad-9ca6-879dea33a8e6" width="600" height="1000" />

### LCD Functionality Verification
            In order to verify if the LCD screen is functioning properly, I uploaded a test code. After compiling and uploading the code, the LCD screen displays the '2048' text. This confirms that the LCD is properly connected and the SPI protocol is working correctly.  
            
<img src="https://github.com/user-attachments/assets/0b2ececa-e535-41be-a3f6-5aeb313a654b" width="600" height="400" />

### Joystick Functionality Verification
            In order to verify if the LCD screen is functioning properly, I uploaded a test code. After compiling and uploading the code, I used the Serial Monitor to check if the X and Y coordinates change based on the joystick movement (N, W, S, E). The X, Y coordinate pair changes correctly according to the movement, indicating that the joystick is working properly. In the image, the first value represents the coordinates when the joystick is not being moved, while the subsequent values correspond to the N, W, S, E movements.  
         
![image](https://github.com/user-attachments/assets/09ffd25b-4785-43ac-8fe6-49471e51d729)


## Software Design  

## Final Results  

## Conclusions  

## Source Code  

## Journal  
* 26.11.2024 Project decision  
*  1.12.2024 Creating a repository for the project on GitHub
*  9.12.2024 Finished the hardware part of the project
*  14.12.2024 Started writing the code for the game.
*  16.12.2024 Update the GitHub repository with all the hardware information.
  
## Bibliography  
[Preferences.h](https://components101.com/modules/joystick-module)  
[TFT_eSPI.h library](https://github.com/Bodmer/TFT_eSPI)  
[LCD information](http://www.lcdwiki.com/3.5inch_SPI_Module_ILI9488_SKU:MSP3520)  
[ESP32 information](https://www.sudo.is/docs/esphome/boards/esp32nodemcu/)  
[Joystick and esp32](https://esp32io.com/tutorials/esp32-joystick)  
