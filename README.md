# *RTR105*
## ~~The second~~
#### the
Text that is not a quote

> Text that is a quote
The background color should be `#ffffff` for light mode and `#0d1117` for dark mode.
 

#include <msp430g2202.h>
char i;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_12MHZ;
  DCOCTL = CALDCO_12MHZ;
  P1DIR = 0xFF;
  P2DIR = 0xF;
  unsigned char j=0;
  char digit_position=0;
  
  for(;;)
  { j++;
  if(j>99){
    j=(j+1)%100;}
    digit_position=(digit_position+1)%4;
  
  indication(j,j,digit_position);
  delay(100);
}
}
void display(unsigned char digit)
{
if(digit==0) P1OUT = 0xF5;
if(digit==1) P1OUT = 0x05;
if(digit==2) P1OUT = 0x73;
if(digit==3) P1OUT = 0x57;
if(digit==4) P1OUT = 0x87;
if(digit==5) P1OUT = 0xD6;
if(digit==6) P1OUT = 0xF6;
if(digit==7) P1OUT = 0x45;
if(digit==8) P1OUT = 0xF7;
if(digit==9) P1OUT = 0xD7;
}
void delay(unsigned long ms)
{
  unsigned long ims;
  for(ims = 0;ims<ms;ims++)
  {
    __delay_cycles(120);
  }
}
void indication(unsigned char digit12, unsigned char digit34, unsigned char which_digit)
{
  P2OUT &= ~0x0F;
 
  if (which_digit == 0) {P2OUT |= BIT0; display(digit12/10);}
  if (which_digit == 1) {P2OUT |= BIT1; display(digit12%10);}
  if (which_digit == 2) {P2OUT |= BIT2; display(digit34/10);}
  if (which_digit == 3) {P2OUT |= BIT3;display(digit34%10);}
  
}
