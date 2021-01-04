/*
 * Keypad_app3.c
 *
 * Created: 9/29/2020 10:19:48 PM
 *  Author: Rita
 */ 

#include "std_macros.h"
#include "keypad.h"
#include "LCD.h"


/*
 * Function: Perform desired operation on 2 numbers & return result. Also checks for division by zero & returns error.
 * Parameter: [uint8_t], [uint8_t], [uint8_t] 2 numbers & sign
 * Output: [uint8_t] result, error status 
 */
uint8_t eval (uint8_t num1, uint8_t num2, uint8_t sign);


int main ()
{
	/* Initialize LCD & Keypad */
	lcd_init();
	keypad_init();
	
	/* Variables to hold the 2 numbers, the applied sign & number of loops to know which kind of char is next */
	uint8_t num1 = 0, num2 = 0, sign, loop = 1;
	while (1)
	{
		/* Get key value from keypad */
		uint8_t key = keypad_read();
		while ( key == '$')	key = keypad_read();
		
		/* Key is number */
		if ( key >=0 && key <10)
		{
			/* First time to loop is the first number */
			if (loop == 1)	
			{ 
				num1 = key; 
				lcd_write_command(CLEAR_DISPLAY); 
			}
			/* Third time to loop is the second number */
			else if (loop == 3)  
			{
				num2 = key;
			}
			/* Display equivalent char by adding ASCII of zero */				
			lcd_write_char(key + '0');
		}
		
		/* Key is '/' sign */				
		else if (key == 10)
		{
			sign = '/';
			lcd_write_char('/');
		}
		
		/* Key is '*' sign */
		else if (key == 11)
		{
			sign = '*';
			lcd_write_char('*');
		}
		
		/* Key is '-' sign */
		else if (key == 12)
		{
			sign = '-';
			lcd_write_char('-');
		}
		
		/* Key is '+' sign */
		else if (key == 13)
		{
			sign = '+';
			lcd_write_char('+');
		}
		
		/* Key is 'ON/C' [Clear] */
		else if (key == 14)
		{
			/* Clear Display & clear values */
			lcd_write_command(CLEAR_DISPLAY);
			num1 = 0;
			num2 = 0;
			sign = ' ';
			loop = 0;
		}
		
		/* Key is '=' sign */
		else if (key == 15)
		{
			lcd_write_char('=');
			/* Get result of the 2 numbers & the desired operation */
			uint8_t result = eval(num1,num2, sign);
			/* Indicates error of division by zero */ 
			if (result == 'E')	lcd_write_string("Wrong entry!");
			else lcd_write_num(result);
			loop = 0;
		}
		loop++;
		_delay_ms(100);
	}
	
}

uint8_t eval (uint8_t num1, uint8_t num2, uint8_t sign)
{
	/* Division by Zero returns error */
	if (sign == '/' && num2 == 0)	return 'E';
	switch(sign)
	{
		case '+':	return num1 + num2;		// Addition operation
		case '-':	return num1 - num2;		// Subtraction operation
		case '*':	return num1 * num2;		// Multiplication operation
		case '/':	return num1 / num2;		// Division operation
	}
}