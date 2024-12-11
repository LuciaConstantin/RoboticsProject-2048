
# 2048 Game - Arduino  

## Introduction  
* This project implements the popular game "2048," commonly found on smartphones and computers, now brought to life on a microcontroller.  
* The purpose of this game is simple yet engaging: the player slides numbered tiles across a grid, merging them to reach the desired 2048 tile.  
* The idea behind this project was to create an interactive and engaging experience for my robotics course, and what could be more interactive than a game? Over the years, one game that has always stood out to me and kept me entertained on my phone is 2048. So I decided to take on the challenge of implementing a new version of this game using a microcontroller.  
* The main utility of this game is mainly for learning. It offers a practical insight into how both software and hardware components communicate in order to create a fully functional project.   
## Project Description 

   A 4x4 game board is displayed on an LCD screen. The player interacts with the game using a joystick. There are four possible directions in which the tiles can move using the joystick: N(up), S(down), E(left) and W(right). By pressing the joystick button, the player can return to the previous game state, effectively undoing the last action (the last move will be reversed).  
   ### Block diagram  
   
![block-diagram-var2](https://github.com/user-attachments/assets/1a09e09c-861a-45c4-b462-1afc776b680f)  

### Components description  

#### Microcontroller  
            The project is based on the ESP32 microcontroller, using the NodeMCU ESP32 development board that integrates the ESP32-WROOM-32 module (processor). The ESP32 is ideal for handling complex tasks, including high-resolution graphics, making it perfect for controlling a high-resolution LCD.    

* Power Supply: The development board is powered via a USB-C connector, which provides 5V. However, the ESP32 itself operates at 3.3 V for proper functioning.  

* Interfaces: In this project the ESP32 is going to communicate with the components using the next communication interfaces: SPI, ADC, and GPIO. These interfaces are used to connect various external modules like the LCD and the joystick.  

#### LCD Display (TFT 3.5” ILI9488 SPI)  
            Because I choose to recreate the popular 2048 game, of course I need a screen to display the grid and the blocks. I chose a 3.5-inch TFT LCD with a resolution of 480x320 pixels, driven by an ILI9488 controller. The display communicates with the microcontroller via the SPI interface, which allows for fast data transfer required for rendering complex images in real-time.  

* Power supply: The LCD display requires a 3.3V power supply.  

* Communication: The communication interface is a 4-wire SPI interface, which is going to be used for receiving data from the microcontroller at every correct move from the joystick.  

#### Joystick  
            The main action of the game is moving the components (the blocks) on the display. But how to move them? I choose a joystick to take care of this task.  

            The joystick is used to allow the player to control the movement of the blocks on the screen. The joystick has two axes (X and Y) for directional control, along with a button for additional functionality (start game, return to the last block configuration).  

* Power supply: The joystick requires 5V to operate.  

* Communication: The joystick communicates with the ESP32 via ADC (Analog-to-Digital Converter) for the X and Y axes (it’s needed for the up, down, left, and right movements). The button of the joystick is connected to a GPIO pin (software: it triggers an interrupt each time it is pressed).  


#### ESP32 and communication  
            Starting with the core of the project, the ESP32 microcontroller is connected to both the LCD display and the joystick. It receives data from the joystick and transmits data to the LCD display. The data that the microcontroller receives from the joystick comes from the ADC (for the joystick's X and Y axis movement) or from a GPIO pin (for the button press). The ADC provides the coordinates of the joystick (representing movement along the X and Y axes), or the GPIO pin reads the low-level signal from the button when pressed, so the microcontroller can interpret these inputs and transmit the appropriate changes to the LCD.  

            The LCD receives data via the SPI interface, specifically through the MOSI (Master Out Slave In) line. This transmission happens after the SCK (Serial Clock) is set to the correct frequency, and the LCD is selected using the CS (Chip Select) pin. The SPI protocol ensures fast data transfer, which is ideal for real-time updates of the game state on the LCD display. 

## Hardware Design  
### Components list
| Component  | Image | Model    | Number| More information |
| ------------- | ------------- | -------------| -------------| -------------|
| Breadboard  |![image](https://github.com/user-attachments/assets/55cbcf73-1f63-4177-8bd7-0ffa49542146)
 |Full-sized | 1 | |
| ESP32  |   | NodeMCU | 1 |[Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)|
| LCD display| |ILI9488 | 1 |[Store](https://www.aliexpress.com/item/1005004804238339.html?srcSns=sns_WhatsApp&spreadType=socialShare&bizType=ProductDetail&social_params=60906366425&aff_fcid=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&tt=MG&aff_fsk=_EHL67gs&aff_platform=default&sk=_EHL67gs&aff_trace_key=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&shareId=60906366425&businessType=ProductDetail&platform=AE&terminal_id=c35ec2ea804245d1a09f2fcf4cb090a3&afSmartRedirect=y)|
|Joystick|  | PS2| 1 |
|USB cable| |Type C| 1 | 
| Jumper wires| | Male-Male, Male-Female | many |

## Software Design  

## Final Results  

## Conclusions  

## Source Code  

## Journal  
* 26.11.2024 Project decision  
*  1.12.2024 Creating a repository for the project on GitHub
  
## Bibliography  

