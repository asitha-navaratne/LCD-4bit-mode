# LCD-4bit-mode
<p align="justify">In this code a 16x2 LCD module is interfaced with the ATmega32A in 4-bit mode.</p>

<p align="justify">The 16x2 LCD module can be interfaced with a microcontroller in two modes; 8-bit mode where all 8 data pins of the LCD module are connected to the 
microcontroller, and 4-bit mode where only the last 4 data pins are connected. While 8-bit mode is easier to understand and implement in code, 4-bit mode, which we have used here, 
saves up the microcontroller's pins for other modules to use. Therefore, 4-bit mode is better for large-scale projects or projects that use a large number of modules.</p>

![Circuit diagram](https://github.com/asitha-navaratne/LCD-4bit-mode/blob/master/LCD_4bit_mode.jpg?raw=true)

<p align="justify">In 4-bit mode, the 8-bit command or character is sent as two consecutive 4-bit packages (4 bits = 1 nibble) to the pins D4 to D7. While this method might be 
slower than sending the entire data byte at once, as when using 8-bit mode, the actual difference in time is almost negligible. The remaining data pins can be connected to GND or 
left unconnected. When sending data there should be a time delay between sending the two consecutive nibbles of a data byte, or the data will be read incorrectly. The upper 4 bits of the data are selected by bit-shifting the data byte and loaded onto the data pins of the module, followed by the lower 4 bits selected in a similar manner.</p>

<p align="justify">Before using 4-bit mode, the module should first be notified of the mode of operation by sending the relevant commands. The remaining operation and connections are all similar to 8-bit mode (Refer to the <a href="https://github.com/asitha-navaratne/LCD-8bit-mode">LCD-8bit-mode</a> repo).</p>
