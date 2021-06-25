#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_DDR 		DDRB									///< DDR of LCD display.
#define LCD_PORT 		PORTB									///< Port of LCD display.
#define RS 				PB0										///< Pin for LCD Register Select terminal.
#define EN 				PB1										///< Pin for LCD Enable terminal.

void LCD_DISPLAY_INIT(void);
void LCD_SEND_COMMAND(unsigned char command);
void LCD_SEND_CHARACTER(unsigned char character);
void LCD_SEND_STRING(char *string);

int main(void){
	LCD_DISPLAY_INIT();
	
	LCD_SEND_STRING("Asitha");
	LCD_SEND_COMMAND(0xC0);										///< Move cursor to the beginning of second line.
	LCD_SEND_STRING("Navaratne");
	
	LCD_SEND_COMMAND(0x0C);										///< Turn cursor off.
}

/*!
 *	@brief Initialize LCD in 4-bit mode.
 */

void LCD_DISPLAY_INIT(void){
	LCD_DDR |= (1<<RS)|(1<<EN)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	
	LCD_SEND_COMMAND(0x01);										///< Clear display screen.
	LCD_SEND_COMMAND(0x02);										///< Initialize LCD in 4-bit mode.
	LCD_SEND_COMMAND(0x28);										///< 2 line, 5x7 matrix of characters in 4-bit mode.
	LCD_SEND_COMMAND(0x80);										///< Send cursor to beginning of first line.
	LCD_SEND_COMMAND(0x0E);										///< Turn display and cursor on.
	_delay_ms(2);
}

/*!
 *	@brief Send a command to the LCD display.
 *	@param Command to be sent (unsigned char).
 */

void LCD_SEND_COMMAND(unsigned char command){
	LCD_PORT = (LCD_PORT & 0x0F)|(command & 0xF0);				///< Load upper nibble of the command to the port.
	LCD_PORT &= ~(1<<RS);										///< Set RS pin low to enter command mode.
	LCD_PORT |= (1<<EN);
	_delay_us(1);
	LCD_PORT &= ~(1<<EN);										///< Create a momentary pulse at EN pin to send the data to the LCD.
 
	_delay_us(200);
 
	LCD_PORT = (LCD_PORT & 0x0F)|(command << 4);				///< Load lower nibble of the command to the port.
	LCD_PORT |= (1<<EN);
	_delay_us(1);
	LCD_PORT &= ~(1<<EN);										///< Pulse to send the data.
 
	_delay_ms(2);
}

/*!
 *	@brief Send a single character to the LCD display.
 *	@param Character to be sent (unsigned char).
 */

void LCD_SEND_CHARACTER(unsigned char character){
	LCD_PORT = (LCD_PORT & 0x0F)|(character & 0xF0);			///< Load upper nibble of the character to the port. 
	LCD_PORT |= (1<<RS);										///< Set RS pin high to enter character mode.
	LCD_PORT |= (1<<EN);
	_delay_us(1);
	LCD_PORT &= ~(1<<EN);										///< Create a momentary pulse at EN pin to send the data to the LCD.
	
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F)|(character << 4);				///< Load lower nibble of the character to the port. 
	LCD_PORT |= (1<<EN);
	_delay_us(1);
	LCD_PORT &= ~(1<<EN);										///< Pulse to send the data.
	
	_delay_ms(2);
}

/*!
 *	@brief Send a string of characters to the LCD display.
 *	@param String to be sent (char).
 */

void LCD_SEND_STRING(char *string){
	for(uint8_t i=0;string[i]!=0;i++){
		LCD_SEND_CHARACTER(string[i]);
		_delay_ms(2);
	}
}