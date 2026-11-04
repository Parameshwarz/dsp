/**
 * ==============================================================================
 * MICROCONTROLLER & EMBEDDED SYSTEMS LAB (TM4C123G TIVA C) - CODE COLLECTION
 * Department of Electronics and Communication Engineering (ECE), NIT Warangal
 * Target Platform: Texas Instruments TM4C123GH6PM ARM Cortex-M4 Microcontroller
 * File Name: target.c
 * ==============================================================================
 * 
 * ==============================================================================
 *                                INDEX OF EXPERIMENTS
 * ==============================================================================
 *  EXP NO. | EXPERIMENT TITLE        | TARGET HARDWARE & PERIPHERALS
 * ---------+-------------------------+------------------------------------------
 *   EXP 01 | Led_switch              | GPIO Port F (PF0/SW2, PF4/SW1, PF1-3 RGB LED)
 *   EXP 02 | Roll_Scroll             | 7-Segment Display (Port E Shift Registers)
 *   EXP 03 | Buzzer                  | Piezo Buzzer (PD7) & Green LED (PF3) with SW1
 *   EXP 04 | Key_Board interfacing   | Analog Keypad (ADC0/AIN4 on PD3) & 16x2 LCD
 *   EXP 05 | Nitw_Roll               | 16x2 Character LCD Roll Number Display
 *   EXP 06 | DC_Motor                | DC Motor H-Bridge Speed/Direction (PWM1 Gen 3)
 *   EXP 07 | Stepper                 | Stepper Motor Step Sequence & Rotation Angles
 *   EXP 08 | Switch_Stepper          | Stepper Motor Direction Control via Switch PF4
 *   EXP 09 | PotMeter                | Potentiometer ADC0 Conversion & 7-Segment Out
 * ==============================================================================
 * 
 * NOTE ON USAGE:
 * Each experiment section below is complete and standalone, containing its own
 * required #include directives, peripheral configuration routines, and main() function.
 * ==============================================================================
 */


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 01: Led_switch
 * ============================================================================
 * Title: GPIO Port F On-Board Switch Monitoring and Tri-Color RGB LED Control
 * Description: Reads active-low switches SW1 (PF4) and SW2 (PF0) using internal
 *              pull-up resistors. Changes onboard RGB LED colors based on switch
 *              combinations (White, Red, Blue, Off).
 * Peripherals: GPIO Port F (PF0 locked pin unlock, PF1 Red, PF2 Blue, PF3 Green, PF4 SW1)
 ******************************************************************************/

#include "TM4C123GH6PM.h"

int main(void) {
    unsigned int switch_state;

    // 1. Enable the clock for GPIO Port F
    SYSCTL->RCGCGPIO |= 0x20; 

    // 2. Unlock Port F Pin 0 (PF0 is locked by default)
    GPIOF->LOCK = 0x4C4F434B; // Magic number to unlock the GPIO Commit register
    GPIOF->CR |= 0x01;        // Commit the change to allow configuring PF0

    // 3. Configure the GPIO Port F pins
    GPIOF->DIR |= 0x0E;       // Set PF1 (Red), PF2 (Blue), PF3 (Green) as outputs
    GPIOF->DIR &= ~0x11;      // Set PF4 (SW1) and PF0 (SW2) as inputs (~0x11 clears bits 0 and 4)
    
    GPIOF->DEN |= 0x1F;       // Enable digital functionality for PF0, PF1, PF2, PF3, PF4
    GPIOF->PUR |= 0x11;       // Enable internal pull-up resistors for PF4 and PF0

    // 4. Infinite loop to monitor switches and change LED colors
    while(1) {
        // Read the state of Port F and mask out everything except PF4 and PF0
        switch_state = GPIOF->DATA & 0x11; 

        // Switches are active-low (0 when PRESSED, 1 when UNPRESSED)
        switch(switch_state) {
            
            case 0x00: // State 00: Both switches PRESSED
                // Turn on White (Red + Blue + Green = 0x0E)
                GPIOF->DATA = 0x0E; 
                break;
                
            case 0x01: // State 01: SW1 (PF4) PRESSED, SW2 (PF0) UNPRESSED
                // Turn on Red (PF1 = 0x02)
                GPIOF->DATA = 0x02; 
                break;
                
            case 0x10: // State 10: SW1 (PF4) UNPRESSED, SW2 (PF0) PRESSED
                // Turn on Blue (PF2 = 0x04)
                GPIOF->DATA = 0x04; 
                break;
                
            case 0x11: // State 11: Both switches UNPRESSED
                // Turn LEDs Off (0x00 / Green led bit 0x08)
                GPIOF->DATA = 0x08; 
                break;
        }
    }
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 02: Roll_Scroll
 * ============================================================================
 * Title: 7-Segment Display Roll Number Scrolling via Shift Registers
 * Description: Cascaded serial-in parallel-out shift registers driven through
 *              GPIO Port E (Data: PE2, Clock: PE3, Latch: PE4) to display and
 *              scroll alphanumeric characters on multi-digit 7-segment displays.
 * Peripherals: GPIO Port E (PE0-PE4 digital outputs)
 ******************************************************************************/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delayMs(int n);
void shift_out1(unsigned char data);

int main(void)
{
    int i;

    // Enable clock for Port E
    SYSCTL_RCGCGPIO_R |= 0x10;

    // Small delay for GPIO clock to stabilize
    delayMs(1);

    // Configure PE0-PE4 as digital outputs
    GPIO_PORTE_DIR_R |= 0x1F;
    GPIO_PORTE_DEN_R |= 0x1F;

    // Hex codes for 7-segment display: 0 to F
    unsigned char hex_digits[16] = {
        0xFC, 0x60, 0xDA, 0xF2,
        0x66, 0xB6, 0xBE, 0xE0,
        0xFE, 0xF6, 0xEE, 0x3E,
        0x9C, 0x7A, 0x9E, 0x8E
    };

    while (1)
    {
        for (i = 0; i < 16; i++)
        {
            // Send data to cascaded shift registers
            shift_out1(hex_digits[4]);
            delayMs(1000);
            shift_out1(hex_digits[2]);
            delayMs(1000);
            shift_out1(hex_digits[10]);
            delayMs(1000);
            shift_out1(hex_digits[1]);
            delayMs(1000);
            shift_out1(hex_digits[11]);
            delayMs(1000);
            shift_out1(hex_digits[12]);
            delayMs(1000);
            shift_out1(hex_digits[14]);
            delayMs(1000);
            shift_out1(hex_digits[4]);
            delayMs(1000);
            shift_out1(hex_digits[2]);
            delayMs(1000);
            // Delay before displaying next value
            delayMs(1000);
        }
    }
}

void shift_out1(unsigned char data)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        // Clock LOW
        GPIO_PORTE_DATA_R &= ~0x08;     // PE3 = 0

        // Send data bit through PE2
        if (data & (1 << i))
        {
            GPIO_PORTE_DATA_R |= 0x04;  // PE2 = 1
        }
        else
        {
            GPIO_PORTE_DATA_R &= ~0x04; // PE2 = 0
        }

        // Clock HIGH
        GPIO_PORTE_DATA_R |= 0x08;      // PE3 = 1
    }

    // Latch the shifted data
    GPIO_PORTE_DATA_R |= 0x10;          // PE4 = 1
    delayMs(1);
    GPIO_PORTE_DATA_R &= ~0x10;         // PE4 = 0
}

void delayMs(int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3180; j++)
        {
            // Approximately 1 ms delay
        }
    }
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 03: Buzzer
 * ============================================================================
 * Title: Piezo Buzzer and Green LED Interface with Push Button Switch
 * Description: Unlocks protected NMI pin PD7 for buzzer output. When SW1 (PF4)
 *              is pressed, turns ON both the Green LED (PF3) and Buzzer (PD7);
 *              turns them OFF when SW1 is released.
 * Peripherals: GPIO Port D (PD7 unlocked output for Buzzer), GPIO Port F (PF3 LED, PF4 SW1)
 ******************************************************************************/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delayMs(int n);

int main(void)
{
    volatile uint32_t delay;

    /* 1. Enable clock to GPIO Port D (Bit 3) and Port F (Bit 5) */
    SYSCTL_RCGCGPIO_R |= 0x28; 
    delay = SYSCTL_RCGCGPIO_R;      /* Dummy read to allow clock to stabilize */

    /* 2. Unlock PD7 (PD7 is a protected NMI pin by default) */
    GPIO_PORTD_LOCK_R = 0x4C4F434B; /* Unlock GPIO Port D */
    GPIO_PORTD_CR_R |= 0x80;        /* Allow changes to PD7 */

    /* 3. Configure Port D (PD7 for Buzzer) */
    GPIO_PORTD_DIR_R |= 0x80;       /* Set PD7 as output */
    GPIO_PORTD_DEN_R |= 0x80;       /* Enable digital function on PD7 */

    /* 4. Configure Port F (PF3 for Green LED, PF4 for SW1) */
    GPIO_PORTF_DIR_R |= 0x08;       /* Set PF3 as output (LED) */
    GPIO_PORTF_DIR_R &= ~0x10;      /* Ensure PF4 is an input (SW1) */
    GPIO_PORTF_DEN_R |= 0x18;       /* Enable digital function on PF3 and PF4 */
    GPIO_PORTF_PUR_R |= 0x10;       /* Enable pull-up resistor for PF4 */

    while (1)
    {
        /* Read PF4 (SW1). Since we use a pull-up, it reads 0 when pressed. */
        if ((GPIO_PORTF_DATA_R & 0x10) == 0) 
        {
            /* Switch is pressed: Turn ON LED and Buzzer */
            GPIO_PORTF_DATA_R |= 0x08;  /* Set PF3 HIGH */
            GPIO_PORTD_DATA_R |= 0x80;  /* Set PD7 HIGH */
        }
        else 
        {
            /* Switch is NOT pressed: Turn OFF LED and Buzzer */
            GPIO_PORTF_DATA_R &= ~0x08; /* Set PF3 LOW */
            GPIO_PORTD_DATA_R &= ~0x80; /* Set PD7 LOW */
        }
    }
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 4180; j++)
        {} /* do nothing for 1 ms */
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 04: Key_Board interfacing
 * ============================================================================
 * Title: Analog Keypad and 16x2 Character LCD Interfacing via ADC0
 * Description: Reads an analog resistor ladder keypad using ADC0 Sequencer 0 on
 *              channel 4 (PD3/AIN4). Maps analog voltage values to characters ('0'-'F')
 *              and displays pressed keys on a 16x2 alphanumeric LCD via shift registers.
 * Peripherals: ADC0 (AIN4/PD3), GPIO Port D/E/A/F, 4-bit mode 16x2 LCD
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define LCD_clear()  LCD_command(0x1)  /* Clear display LCD */
#define LCD_origin() LCD_command(0x2)  /* Set to origin LCD */
#define LCD_row1()   LCD_command(0x80) /* Begin at Line 1 */ 
#define LCD_row2()   LCD_command(0xC0) /* Begin at Line 2 */

/* Global variables for LCD shift register state */
unsigned char PP1 = 0x00;
unsigned char PP0 = 0x00;

/* Function Prototypes */
void shift_out1(unsigned char str);
void LCD_enable(void);
void LCD_command(unsigned char command);
void LCD_putc(unsigned char ascii);
void LCD_puts(unsigned char *lcd_string);
void LCD_init(void);
unsigned char key_scan(unsigned int volatile rec_val);

/* Main Program */
int main(void) {
    uint32_t ui32ADC0Value;
    unsigned char Dig_val;
    volatile uint32_t ui32TempAvg, Temp_val;

    SYSCTL_RCGCGPIO_R |= 0x039; /* enable clock to GPIOD/E/A/F */
    SYSCTL_RCGCADC_R |= 1;      /* enable clock to ADC0 */

    /* initialize PD3 for AIN4 input */
    GPIO_PORTD_AFSEL_R |= 8;    /* enable alternate function */
    GPIO_PORTD_DEN_R &= ~8;     /* disable digital function */
    GPIO_PORTD_AMSEL_R |= 8;    /* enable analog function */

    GPIO_PORTE_DIR_R |= 0x0C;
    GPIO_PORTE_DEN_R |= 0x0C;
    
    GPIO_PORTA_DIR_R |= 0x20;
    GPIO_PORTA_DEN_R |= 0x20;
    
    GPIO_PORTF_DIR_R |= 0x01;
    GPIO_PORTF_DEN_R |= 0x01;

    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~1;         /* disable SS0 during configuration */
    ADC0_EMUX_R &= ~0x000F;     /* software trigger conversion */ 
    ADC0_SSMUX0_R |= 0x05 ;     /* get input from channel 4 */
    ADC0_SSCTL0_R |= 0x06;      /* take one sample at a time, set */
    ADC0_ACTSS_R |= 0x01;       /* enable ADC0 sequencer 0 */

    LCD_init();                 // LCD 16x2 initializing
    LCD_row1();                 // Cursor position at 1st line
    LCD_puts("Interfacing");
    LCD_row2();                 // Cursor position at 2nd line
    LCD_puts("Analog KEYPAD");
    SysCtlDelay(5000000);
    LCD_clear(); 

    while(1) {
        ADC0_PSSI_R |= 1;                   /* start a conversion sequence 0 */
        while((ADC0_RIS_R & 1) == 0);       /* wait for conversion complete */
        ui32ADC0Value = ADC0_SSFIFO0_R;     /* read conversion result */
        ADC0_ISC_R = 1;                     /* clear completion flag */
        
        Temp_val = ui32ADC0Value / 10;
        Dig_val = key_scan(Temp_val);       // compare the key pressed
        
        SysCtlDelay(50000);
        LCD_row1();
        LCD_puts("Press any Key");
        LCD_row2();
        
        if(Dig_val <= 'F')                  // if the ascii is <= F put the value in LCD
            LCD_putc(Dig_val);
    }
}

/* Key scanning */
unsigned char key_scan(unsigned int volatile rec_val) { 
    if(rec_val == 371 || rec_val == 372) return '0'; // 0 key pressed
    else if(rec_val == 376 || rec_val == 377) return '1'; // 1st key pressed
    else if(rec_val == 380 || rec_val == 379) return '2'; // 2nd key pressed
    else if(rec_val == 381 || rec_val == 382) return '3'; // 3rd key pressed
    else if(rec_val == 357 || rec_val == 358 || rec_val == 359) return '4'; // 4th key pressed
    else if(rec_val == 362 || rec_val == 363 || rec_val == 364) return '5'; // 5th key pressed
    else if(rec_val == 367 || rec_val == 368 || rec_val == 369) return '6'; // 6th key pressed
    else if(rec_val == 371 || rec_val == 372) return '7'; // 7th key pressed
    else if(rec_val == 317 || rec_val == 318 || rec_val == 319) return '8'; // 8th key pressed
    else if(rec_val == 333 || rec_val == 334 || rec_val == 335) return '9'; // 9th key pressed
    else if(rec_val == 345 || rec_val == 346 || rec_val == 347) return 'A'; // A key pressed
    else if(rec_val == 353 || rec_val == 354 || rec_val == 355) return 'B'; // B key pressed
    else if(rec_val == 0) return 'C'; // C key pressed
    else if(rec_val == 203 || rec_val == 204 || rec_val == 205) return 'D'; // D key pressed
    else if(rec_val == 272 || rec_val == 273 || rec_val == 274) return 'E'; // E key pressed
    else if(rec_val == 306 || rec_val == 307 || rec_val == 308) return 'F'; // F key pressed
    else return 'G'; 
}

/* LCD Initialization and Write functions */
void LCD_puts(unsigned char *lcd_string) {
    while (*lcd_string) {
        LCD_putc(*lcd_string++);
    }
}

void LCD_init() {
    SysCtlDelay(500000);
    LCD_command(0x20);
    SysCtlDelay(500000);
    LCD_command(0x28); // Selecting 4bit LCD 16x2
    SysCtlDelay(500000);
    LCD_command(0x0C); // LCD cursor off
    SysCtlDelay(500000);
    LCD_command(0x06); // LCD display on
    SysCtlDelay(500000);
    LCD_command(0x01); // LCD clear screen
    SysCtlDelay(500000);
}

/* Sending Character to LCD */
void LCD_putc(unsigned char ascii) {
    unsigned char volatile num;
    num = ascii;
    
    // Reverse bit ordering for shift register format
    num = ((num & 0x11)<<3) | ((num & 0x22)<<1) | ((num & 0x44)>>1) | ((num & 0x88)>>3);
    ascii = num;
    
    // Sending higher nibble of lcd data
    PP1 = (PP1 & 0xF0) | ((ascii>>4) & 0x0F);
    PP1 = PP1 | 0xA0; // setting 7th pin as high RS = 1, EN = 1;
    PP1 = PP1 & ~(0x40); // RW = 0
    
    // shifting data bits to shift register
    shift_out1(PP1);
    SysCtlDelay(500);
    PP1 = PP1 & ~(0x20); // En = 0
    shift_out1(PP1);
    SysCtlDelay(500);
    
    // Sending lower nibble of lcd data
    PP1 = (PP1 & 0xF0) | (ascii & 0x0F);
    PP1 = PP1 | 0xA0; // setting 7th bit as high RS = 1, EN = 1;
    PP1 = PP1 & ~(0x40); // RW = 0
    shift_out1(PP1);
    SysCtlDelay(500);
    PP1 = PP1 & ~(0x20); // EN = 0
    shift_out1(PP1);
    SysCtlDelay(500);
}

/* Command to LCD */
void LCD_command(unsigned char command) {
    unsigned char volatile num;
    num = command;
    
    // Reverse bit ordering for shift register format
    num = ((num & 0x11)<<3) | ((num & 0x22)<<1) | ((num & 0x44)>>1) | ((num & 0x88)>>3);
    command = num;
    
    // Sending higher nibble of lcd Command
    PP0 = (PP0 & 0xF0) | ((command>>4) & 0x0F);
    PP0 = PP0 & (~(3 << 7)); // setting 7th pin as low RS = 0 , RW = 0
    PP0 = PP0 | 0x20; // EN = 1
    
    // shifting bits to shift register
    shift_out1(PP0);
    SysCtlDelay(500);
    PP0 = PP0 & ~(0x20); // EN = 0
    shift_out1(PP0);
    SysCtlDelay(500);

    // Sending lower nibble of lcd command
    PP0 = (PP0 & 0xF0) | (command & 0x0F);
    PP0 = PP0 & (~(3 << 7)); // RS = 0, RW = 0
    PP0 = PP0 | 0x20; // EN = 1
    shift_out1(PP0);
    SysCtlDelay(500);
    PP0 = PP0 & ~(0x20); // EN = 0
    shift_out1(PP0);
    SysCtlDelay(500);
}

/* Data Transfer through Shift register */
void shift_out1(unsigned char str) {
    unsigned char j=0, check;
    GPIO_PORTA_DATA_R = 0x00; // PA5 pin(stk) is low (0000 0000)
    
    for(j=0; j<=7; j++) { 
        GPIO_PORTE_DATA_R = 0x00; // PE3 pin(sclk) is low (0000 0000)
        check = (str & (1<<j));
        
        if(check)
            GPIO_PORTE_DATA_R |= 0x04; // PE2 pin(sdat) is high (0000 0100)
        else
            GPIO_PORTE_DATA_R = 0x00; // PE2 pin(sdat) is low (0000 0000)
            
        GPIO_PORTE_DATA_R |= 0x08; // PE3 pin(sclk) is high (0000 1000), sclk=1;
    }
    
    GPIO_PORTA_DATA_R |= 0x20; // PA5 pin(stk) is high (0010 0000) , stk=1, storing completed;
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 05: Nitw_Roll
 * ============================================================================
 * Title: 16x2 Character LCD Alphanumeric Roll Number Display
 * Description: Initializes 16x2 LCD in 4-bit mode using shift registers. Alternately
 *              displays Department name ("Dept of ECE, N I T Warangal") and student
 *              roll number ("My Roll No is 24ECB1A24_15") with 5-second viewing delays.
 * Peripherals: GPIO Port E (PE2 Data, PE3 Clock), Port A (PA5 Strobe), Port F
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define LCD_clear()  LCD_command(0x1)  /* Clear display LCD */
#define LCD_origin() LCD_command(0x2)  /* Set to origin LCD */
#define LCD_row1()   LCD_command(0x80) /* Begin at Line 1 */ 
#define LCD_row2()   LCD_command(0xC0) /* Begin at Line 2 */

/* Global variables for LCD shift register state */
unsigned char PP1 = 0x00;
unsigned char PP0 = 0x00;

/* Function Prototypes */
void shift_out1(unsigned char str);
void LCD_enable(void);
void LCD_command(unsigned char command);
void LCD_putc(unsigned char ascii);
void LCD_puts(unsigned char *lcd_string);
void LCD_init(void);

/* Main Program */
int main(void) {
    volatile uint32_t ui32TempAvg, Temp_val;

    SYSCTL_RCGCGPIO_R |= 0x039; /* enable clock to GPIOD/E/A/F */

    GPIO_PORTE_DIR_R |= 0x0C;
    GPIO_PORTE_DEN_R |= 0x0C;
    
    GPIO_PORTA_DIR_R |= 0x20;
    GPIO_PORTA_DEN_R |= 0x20;
    
    GPIO_PORTF_DIR_R |= 0x01;
    GPIO_PORTF_DEN_R |= 0x01;

    while(1) {
        LCD_init();                 // LCD 16x2 initializing
        LCD_row1();                 // Cursor position at 1st line
        LCD_puts("  Dept of ECE");
        LCD_row2();                 // Cursor position at 2nd line
        LCD_puts("  N I T Warangal");
        SysCtlDelay(5000000);
        LCD_clear(); 
                
        LCD_init();                 // LCD 16x2 initializing
        LCD_row1();                 // Cursor position at 1st line
        LCD_puts("  My Roll No is ");
        LCD_row2();                 // Cursor position at 2nd line
        LCD_puts("  24ECB1A24_15");
        SysCtlDelay(5000000);
        LCD_clear(); 
    }
}

/* LCD Initialization and Write functions */
void LCD_puts(unsigned char *lcd_string) {
    while (*lcd_string) {
        LCD_putc(*lcd_string++);
    }
}

void LCD_init() {
    SysCtlDelay(500000);
    LCD_command(0x20);
    SysCtlDelay(500000);
    LCD_command(0x28); // Selecting 4bit LCD 16x2
    SysCtlDelay(500000);
    LCD_command(0x0C); // LCD cursor off
    SysCtlDelay(500000);
    LCD_command(0x06); // LCD display on
    SysCtlDelay(500000);
    LCD_command(0x01); // LCD clear screen
    SysCtlDelay(500000);
}

/* Sending Character to LCD */
void LCD_putc(unsigned char ascii) {
    unsigned char volatile num;
    num = ascii;
    
    // Reverse bit ordering for shift register format
    num = ((num & 0x11)<<3) | ((num & 0x22)<<1) | ((num & 0x44)>>1) | ((num & 0x88)>>3);
    ascii = num;
    
    // Sending higher nibble of lcd data
    PP1 = (PP1 & 0xF0) | ((ascii>>4) & 0x0F);
    PP1 = PP1 | 0xA0; // setting 7th pin as high RS = 1, EN = 1;
    PP1 = PP1 & ~(0x40); // RW = 0
    
    // shifting data bits to shift register
    shift_out1(PP1);
    SysCtlDelay(500);
    PP1 = PP1 & ~(0x20); // En = 0
    shift_out1(PP1);
    SysCtlDelay(500);
    
    // Sending lower nibble of lcd data
    PP1 = (PP1 & 0xF0) | (ascii & 0x0F);
    PP1 = PP1 | 0xA0; // setting 7th bit as high RS = 1, EN = 1;
    PP1 = PP1 & ~(0x40); // RW = 0
    shift_out1(PP1);
    SysCtlDelay(500);
    PP1 = PP1 & ~(0x20); // EN = 0
    shift_out1(PP1);
    SysCtlDelay(500);
}

/* Command to LCD */
void LCD_command(unsigned char command) {
    unsigned char volatile num;
    num = command;
    
    // Reverse bit ordering for shift register format
    num = ((num & 0x11)<<3) | ((num & 0x22)<<1) | ((num & 0x44)>>1) | ((num & 0x88)>>3);
    command = num;
    
    // Sending higher nibble of lcd Command
    PP0 = (PP0 & 0xF0) | ((command>>4) & 0x0F);
    PP0 = PP0 & (~(3 << 7)); // setting 7th pin as low RS = 0 , RW = 0
    PP0 = PP0 | 0x20; // EN = 1
    
    // shifting bits to shift register
    shift_out1(PP0);
    SysCtlDelay(500);
    PP0 = PP0 & ~(0x20); // EN = 0
    shift_out1(PP0);
    SysCtlDelay(500);

    // Sending lower nibble of lcd command
    PP0 = (PP0 & 0xF0) | (command & 0x0F);
    PP0 = PP0 & (~(3 << 7)); // RS = 0, RW = 0
    PP0 = PP0 | 0x20; // EN = 1
    shift_out1(PP0);
    SysCtlDelay(500);
    PP0 = PP0 & ~(0x20); // EN = 0
    shift_out1(PP0);
    SysCtlDelay(500);
}

/* Data Transfer through Shift register */
void shift_out1(unsigned char str) {
    unsigned char j=0, check;
    GPIO_PORTA_DATA_R = 0x00; // PA5 pin(stk) is low (0000 0000)
    
    for(j=0; j<=7; j++) { 
        GPIO_PORTE_DATA_R = 0x00; // PE3 pin(sclk) is low (0000 0000)
        check = (str & (1<<j));
        
        if(check)
            GPIO_PORTE_DATA_R |= 0x04; // PE2 pin(sdat) is high (0000 0100)
        else
            GPIO_PORTE_DATA_R = 0x00; // PE2 pin(sdat) is low (0000 0000)
            
        GPIO_PORTE_DATA_R |= 0x08; // PE3 pin(sclk) is high (0000 1000), sclk=1;
    }
    
    GPIO_PORTA_DATA_R |= 0x20; // PA5 pin(stk) is high (0010 0000) , stk=1, storing completed;
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 06: DC_Motor
 * ============================================================================
 * Title: DC Motor Speed and Direction Control using Hardware PWM
 * Description: Configures PWM Module 1 Generator 3 on PF2 (PWM6) and PF3 (PWM7).
 *              Drives an H-Bridge to run motor forward and reverse through stepped
 *              duty cycles (30%, 60%, 100%) with inter-transition deadband stops.
 * Peripherals: PWM Module 1 (Generator 3), GPIO Port F (PF2 PWM6, PF3 PWM7)
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"

/* Function Prototypes */
void PWM_Init(void);
void Motor_Forward(uint16_t speed);
void Motor_Reverse(uint16_t speed);
void Motor_Stop(void);
void Delay_ms(int time_ms);

int main(void) {
    // 1. Initialize PWM on PF2 and PF3
    PWM_Init();
    
    while(1) {
        // Run Forward, increasing speed
        Motor_Forward(3000);  // 30% Speed
        Delay_ms(2000);
        Motor_Forward(6000);  // 60% Speed
        Delay_ms(2000);
        Motor_Forward(9999);  // 100% Speed
        Delay_ms(2000);
        
        Motor_Stop();
        Delay_ms(1000);
        
        // Run Reverse, increasing speed
        Motor_Reverse(3000);  // 30% Speed
        Delay_ms(2000);
        Motor_Reverse(6000);  // 60% Speed
        Delay_ms(2000);
        Motor_Reverse(9999);  // 100% Speed
        Delay_ms(2000);
        
        Motor_Stop();
        Delay_ms(2000);
    }
}

/* 
 * Initialize PWM Module 1 Generator 3 on PF2 (PWM6) and PF3 (PWM7)
 */
void PWM_Init(void) {
    // Enable Clock for PWM Module 1 and Port F
    SYSCTL_RCGCPWM_R |= 2;       // PWM Module 1
    SYSCTL_RCGCGPIO_R |= 0x20;   // Port F
    Delay_ms(1);                 // Wait for clock to stabilize
    
    // Configure PF2 and PF3 for Alternate Function (PWM)
    GPIO_PORTF_AFSEL_R |= 0x0C;  // Enable alternate function on PF2 (0x04) & PF3 (0x08)
    
    // Assign PWM signals to PF2 and PF3 (PCTL value = 5 for both)
    GPIO_PORTF_PCTL_R &= ~0x0000FF00; 
    GPIO_PORTF_PCTL_R |= 0x00005500;  
    GPIO_PORTF_DEN_R |= 0x0C;    // Enable digital I/O on PF2 and PF3
    
    // Configure PWM Clock (System Clock / 64)
    SYSCTL_RCC_R |= 0x00100000;  // Enable PWM clock divisor
    SYSCTL_RCC_R &= ~0x000E0000; // Clear divisor bits
    SYSCTL_RCC_R |= 0x000A0000;  // Set divisor to 64
    
    // Configure PWM Module 1 Generator 3 (Controls PWM6/PF2 and PWM7/PF3)
    PWM1_3_CTL_R = 0;            // Disable generator before config
    
    // Drive PWM High at 0, Low when it matches CMPA (PF2) and CMPB (PF3)
    PWM1_3_GENA_R = 0x0000008C;  // Config for PF2
    PWM1_3_GENB_R = 0x0000080C;  // Config for PF3
    
    // Set PWM Frequency
    PWM1_3_LOAD_R = 10000;       
    
    // Initial Duty Cycle = 0% (Motor Stopped)
    PWM1_3_CMPA_R = 0;           // PF2 speed
    PWM1_3_CMPB_R = 0;           // PF3 speed
    
    // Start PWM
    PWM1_3_CTL_R |= 1;           // Enable Generator 3
    PWM1_ENABLE_R |= 0xC0;       // Enable PWM outputs 6 (Bit 6) and 7 (Bit 7)
}

/* 
 * Move Forward: Apply PWM to L1 (PF2), set L2 (PF3) to 0
 */
void Motor_Forward(uint16_t speed) {
    if(speed >= 10000) speed = 9999;
    PWM1_3_CMPB_R = 0;       // Turn OFF L2 first to prevent shorting
    PWM1_3_CMPA_R = speed;   // Apply PWM to L1
}

/* 
 * Move Reverse: Set L1 (PF2) to 0, apply PWM to L2 (PF3)
 */
void Motor_Reverse(uint16_t speed) {
    if(speed >= 10000) speed = 9999;
    PWM1_3_CMPA_R = 0;       // Turn OFF L1 first to prevent shorting
    PWM1_3_CMPB_R = speed;   // Apply PWM to L2
}

/* 
 * Stop the motor
 */
void Motor_Stop(void) {
    PWM1_3_CMPA_R = 0;       // 0% Duty cycle on L1
    PWM1_3_CMPB_R = 0;       // 0% Duty cycle on L2
}

/* 
 * Simple delay function
 */
void Delay_ms(int time_ms) {
    int i, j;
    for(i = 0; i < time_ms; i++) {
        for(j = 0; j < 3180; j++) {}
    }
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 07: Stepper
 * ============================================================================
 * Title: 4-Phase Stepper Motor Angle Rotation Control (720° Forward, 360° Reverse)
 * Description: Drives 4 coils of a stepper motor via PF2, PF3, PB3, PC4 using a
 *              4-step excitation sequence. Rotates 720 degrees forward (2 revolutions),
 *              pauses for 1 second, then rotates 360 degrees reverse (1 revolution).
 * Peripherals: GPIO Port F (PF2, PF3), Port B (PB3), Port C (PC4)
 ******************************************************************************/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

/* --- MOTOR CONFIGURATION --- */
#define STEPS_PER_REV 200 // 200 steps per revolution (1.8 deg per step)

/* Function Prototypes */
void delayMs(int n);
void take_step(int step_index);

int main(void) {
    /* enable clock to GPIOF/B/C */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; // PF
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; // PB
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; // PC
    
    // Brief delay to let clocks stabilize
    delayMs(1);
    
    /* enable the GPIO pins as outputs */
    GPIO_PORTF_DIR_R |= 0x0C; // PF2 and PF3
    GPIO_PORTB_DIR_R |= 0x08; // PB3
    GPIO_PORTC_DIR_R |= 0x10; // PC4
    
    /* enable the GPIO pins for digital function */
    GPIO_PORTF_DEN_R |= 0x0C;
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTC_DEN_R |= 0x10;

    int step_sequence = 0;
    
    // Calculate total steps needed for the angles
    int steps_720 = STEPS_PER_REV * 1; // 720 degrees rotation sequence
    int steps_360 = STEPS_PER_REV * 2; // 360 degrees rotation sequence
    int i;

    while(1) {
        
        // 1. Move FORWARD 720 Degrees
        for(i = 0; i < steps_720; i++) {
            take_step(step_sequence);
            
            // Advance sequence forward (0, 1, 2, 3 -> 0)
            step_sequence = (step_sequence + 1) % 4; 
            
            // Speed of rotation
            delayMs(5); 
        }
        
        // Pause for 1 second before reversing
        delayMs(1000);
        
        // 2. Move REVERSE 360 Degrees
        for(i = 0; i < steps_360; i++) {
            take_step(step_sequence);
            
            // Advance sequence backward (3, 2, 1, 0 -> 3)
            step_sequence = (step_sequence - 1 + 4) % 4; 
            
            delayMs(5);
        }
        
        // Pause for 1 second before repeating
        delayMs(1000);
    }
}

/* 
 * This function handles switching the correct pins high/low 
 * according to the 4-step sequence.
 */
void take_step(int step_index) {
    // 1. Turn OFF all motor pins first to prevent shorting or lockup
    GPIO_PORTF_DATA_R &= ~0x0C; // Clear PF2, PF3
    GPIO_PORTB_DATA_R &= ~0x08; // Clear PB3
    GPIO_PORTC_DATA_R &= ~0x10; // Clear PC4

    // 2. Turn ON only the pin for the current step
    switch(step_index) {
        case 0: 
            GPIO_PORTF_DATA_R |= 0x04; // PF2 High
            break; 
        case 1: 
            GPIO_PORTF_DATA_R |= 0x08; // PF3 High
            break; 
        case 2: 
            GPIO_PORTB_DATA_R |= 0x08; // PB3 High
            break; 
        case 3: 
            GPIO_PORTC_DATA_R |= 0x10; // PC4 High
            break; 
    }
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n) {
    int i, j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < 4180; j++) {} 
    }
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 08: Switch_Stepper
 * ============================================================================
 * Title: Push-Button Direction-Controlled Stepper Motor
 * Description: Monitors push-button SW1 on PF4 (with pull-up resistor). When SW1
 *              is pressed (0), rotates stepper motor in reverse; when unpressed (1),
 *              rotates stepper motor in forward direction.
 * Peripherals: GPIO Port F (PF2/3 outputs, PF4 input with PUR), Port B (PB3), Port C (PC4)
 ******************************************************************************/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

/* Function Prototypes */
void delayMs(int n);
void take_step(int step_index);

int main(void) {
    /* Enable clock to GPIOF, GPIOB, and GPIOC */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; // PF (Motor L1/L2 & Switch)
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; // PB (Motor L3)
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; // PC (Motor L4)
    
    // Brief delay to let clocks stabilize
    delayMs(1);
    
    /* Configure Motor Pins as Outputs (PF2, PF3, PB3, PC4) */
    GPIO_PORTF_DIR_R |= 0x0C; // PF2 and PF3 as output
    GPIO_PORTB_DIR_R |= 0x08; // PB3 as output
    GPIO_PORTC_DIR_R |= 0x10; // PC4 as output
    
    /* Enable digital function for motor pins */
    GPIO_PORTF_DEN_R |= 0x0C;
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTC_DEN_R |= 0x10;

    /* Configure Switch Pin as Input (PF4 - Onboard SW1) */
    GPIO_PORTF_DIR_R &= ~0x10; // PF4 as input (clear bit 4)
    GPIO_PORTF_DEN_R |= 0x10;  // Enable digital function for PF4
    GPIO_PORTF_PUR_R |= 0x10;  // Enable internal Pull-Up Resistor for PF4

    int step_sequence = 0;

    while(1) {
        // Read the state of the switch on PF4
        // Because of the pull-up resistor, pressed = 0, unpressed = 1
        if((GPIO_PORTF_DATA_R & 0x10) == 0) {
            // SWITCH IS PRESSED: Move Reverse
            step_sequence = (step_sequence - 1 + 4) % 4; 
        } else {
            // SWITCH IS NOT PRESSED: Move Forward
            step_sequence = (step_sequence + 1) % 4; 
        }
        
        // Execute the calculated step
        take_step(step_sequence);
        
        // Speed of rotation (10ms is smooth for most steppers)
        delayMs(10); 
    }
}

/* 
 * This function handles switching the correct pins high/low 
 * according to the 4-step sequence.
 */
void take_step(int step_index) {
    // 1. Turn OFF all motor pins first to prevent shorting or lockup
    GPIO_PORTF_DATA_R &= ~0x0C; // Clear PF2, PF3
    GPIO_PORTB_DATA_R &= ~0x08; // Clear PB3
    GPIO_PORTC_DATA_R &= ~0x10; // Clear PC4

    // 2. Turn ON only the pin for the current step
    switch(step_index) {
        case 0: 
            GPIO_PORTF_DATA_R |= 0x04; // PF2 High
            break; 
        case 1: 
            GPIO_PORTF_DATA_R |= 0x08; // PF3 High
            break; 
        case 2: 
            GPIO_PORTB_DATA_R |= 0x08; // PB3 High
            break; 
        case 3: 
            GPIO_PORTC_DATA_R |= 0x10; // PC4 High
            break; 
    }
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n) {
    int i, j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < 3180; j++) {} // 3180 loop cycles equals roughly 1ms
    }
}


/*******************************************************************************
 * ============================================================================
 * EXPERIMENT 09: PotMeter
 * ============================================================================
 * Title: Potentiometer ADC0 Sampling & 4-Digit 7-Segment Shift Register Display
 * Description: Samples analog voltage from potentiometer on PD3 (ADC0 Sequencer 0,
 *              channel 4 / AIN4). Splits 12-bit ADC result into individual decimal
 *              digits and streams them to 7-segment displays via Port E shift registers.
 * Peripherals: ADC0 (AIN4/PD3 analog input), GPIO Port E (PE0-PE4 digital outputs)
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"

void delayMs(int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 4180; j++) {}
}

void shift_out1(unsigned char str);

volatile int num1, num2, num3, num4;

int main(void) {
    volatile int result;
    unsigned char a[16] = {
        0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0,
        0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E
    };

    /* enable clocks */
    SYSCTL_RCGCGPIO_R |= 0x08; /* enable clock to GPIOD */
    SYSCTL_RCGCADC_R |= 1;     /* enable clock to ADC0 */
    SYSCTL_RCGCGPIO_R |= 0x10; /* enable clock to GPIOE */
    
    GPIO_PORTE_DIR_R |= 0x1F;
    GPIO_PORTE_DEN_R |= 0x1F;
    
    /* initialize PD3 for AIN4 input */
    GPIO_PORTD_AFSEL_R |= 8;  /* enable alternate function */
    GPIO_PORTD_DEN_R &= ~8;   /* disable digital function */
    GPIO_PORTD_AMSEL_R |= 8;  /* enable analog function */

    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~1;           /* disable SS0 during configuration */
    ADC0_EMUX_R &= ~0x000F;       /* software trigger conversion */
    ADC0_SSMUX0_R &= ~0xFFFFFFFF; 
    ADC0_SSMUX0_R |= 0x04;        /* get input from channel 4 */
    ADC0_SSCTL0_R |= 0x06;        /* take one sample at a time, set flag */
    ADC0_ACTSS_R |= 0x01;         /* enable ADC0 sequencer 0 */

    while(1) {
        ADC0_PSSI_R |= 1;             /* start conversion sequence 0 */
        while((ADC0_RIS_R & 1) == 0); /* wait for conversion complete */
        result = ADC0_SSFIFO0_R;      /* read conversion result */
        ADC0_ISC_R = 1;               /* clear completion flag */

        num1 = result % 10;
        result = result / 10;
        num2 = result % 10;
        result = result / 10;
        num3 = result % 10;
        result = result / 10;
        num4 = result % 10;

        shift_out1(a[num1]);
        shift_out1(a[num2]);
        shift_out1(a[num3]);
        shift_out1(a[num4]);
        shift_out1(0x00);
        delayMs(1000);
    }
}

void shift_out1(unsigned char str) {
    unsigned char j, check;
    for(j = 0; j <= 7; j++) {
        GPIO_PORTE_DATA_R = 0x00; // PE3 pin(sclk) is low (0000 0000)
        check = (str & (1 << j));
        if(check)
            GPIO_PORTE_DATA_R |= 0x04; // PE2 pin(sdat) is high (0000 0100)
        else
            GPIO_PORTE_DATA_R |= 0x00;
        GPIO_PORTE_DATA_R |= 0x08; // PE3 pin(sclk) is high (0000 1000)
        GPIO_PORTE_DATA_R |= 0x10;
    }
}
