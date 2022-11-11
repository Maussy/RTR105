# *RTR105*
## ~~The second~~
#### the
Text that is not a quote

> Text that is a quote
The background color should be `#ffffff` for light mode and `#0d1117` for dark mode.
 
#include<msp430g2202.h>
//Globālo mainīgo deklarēšana
char i;
unsigned long ms;
unsigned char digit, digit34, digit12; //indication
unsigned char which_digit;
unsigned int j2 = 0;
unsigned char sekundes = 0, minutes = 0, stundas = 0, mode = 0, submode = 0; //time
unsigned char blink_digit_position1, blink_digit_position2; //blinking
unsigned char poga4; //SW
unsigned char alarm_minutes, alarm_hours, alarm_on; //alarm
unsigned char digit1, digit2, digit3, digit4; //indication2
//Funkcijas piesaukšana
void delay(unsigned long ms);
void indication(unsigned char digit12, unsigned char digit34, unsigned char which_digit);
void time_engine(unsigned char time_instant_in_seconds);
void digit_blinking(unsigned char digit_position, unsigned char blink_digit_position1, unsigned char blink_digit_position2, unsigned int j2);
void short_press(void);
void long_press(void);
void indication2(unsigned char digit1, unsigned char digit2, unsigned char digit3, unsigned char digit4, unsigned char which_digit);
void play(int n, int e);
int main(void){
WDTCTL = WDTPW + WDTHOLD;
BCSCTL1 = CALBC1_12MHZ;
DCOCTL = CALDCO_12MHZ;
P1DIR |= 0XFF;
P1OUT |= 0XFF;
P2DIR |= 0X0F;
P2OUT&= ~0X0F;
P2DIR &= ~0x30;
P2IES |=0x30;
P2IFG &= ~0x30;
P2IE |= 0x30;
__enable_interrupt();
unsigned char j=0;
unsigned char digit_position=0;
//Cikls
for(;;){
 
 digit_position = (digit_position + 1)%4;
 
 if(mode == 0){ // 1 mode
 
 indication(minutes, sekundes, digit_position);
 
   if((j2 > 500) && (digit_position == 0x01))
     P1OUT |=0x08;
 }
 
 else if(mode==1){ // 2 mode
 
 indication(stundas, minutes, digit_position);
   
   if((j2 > 500) && (digit_position == 0x01))
     P1OUT |=0x08;
 //indikaacijas dalas beigas
 }
 else if(mode == 2){ // 3 mode
   
   indication(stundas,minutes,digit_position);
   
   if(submode == 0) digit_blinking(digit_position, 0, 1, j2);
   if(submode == 1) digit_blinking(digit_position, 2, 3, j2);
   if(submode == 2){
 
     digit_blinking(digit_position, 2, 3, j2);
     digit_blinking(digit_position, 1, 2, j2);
    }
     if((j2 < 500) && (digit_position == 1)) P1OUT |= 0x08;
  }
   else if ((mode == 3) & (submode == 0) & (alarm_on == 1))
     indication2(0xA, 0xB, 0xC, 0xD, digit_position); //AL on
   else if ((mode == 3) & (submode == 0) & (alarm_on == 0))
     indication2(0xA, 0xB, 0xC, 0xE, digit_position); //AL off
 else if(mode == 3){ // 4 mode
   
   indication(alarm_hours, alarm_minutes, digit_position);
   
   if (submode == 1) digit_blinking(digit_position, 0, 1, j2);
   if (submode == 2) digit_blinking(digit_position, 2, 3, j2);
 }
   
 if((alarm_minutes==minutes) && (alarm_hours==stundas) && (alarm_on==1)){
     play(1,4);
     play(5,2);
     play(3,2);
     play(3,4);
     play(3,1);
 }
 
 delay(100);
 j2++;
   if(j2 == 1000){
   j2 = 0;
   time_engine(1);
   }
 }
}
//Cipara attēlošana
void display(unsigned char digit){
 
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
 if(digit==0xA) P1OUT = 0xE7;
 if(digit==0xB) P1OUT = 0xB0;
 if(digit==0xC) P1OUT = 0x36;
 if(digit==0xD) P1OUT = 0x26;
 if(digit==0xE) P1OUT = 0xE2;
 if(digit==0xF) P1OUT = 0x00;
}
 void delay(unsigned long ms){
 unsigned long  ims;
 
 for(ims = 0; ims<ms; ims++){
   __delay_cycles(120);
   
 }
}
//Indikācija 1
void indication(unsigned char digit12, unsigned char digit34, unsigned char which_digit){
 
 P2OUT &= ~0x0F;
 
 if(which_digit == 0){
   P2OUT |= BIT0;
   display(digit12/10);
 }
 
 if(which_digit == 1){
   P2OUT |= BIT1;
   display(digit12%10);
 }
 
 if(which_digit == 2){
   P2OUT |= BIT2;
   display(digit34/10);
 }
 
 if(which_digit == 3) {
   P2OUT |= BIT3;
   display(digit34%10);
 }
}
//Laika skaitīšana
void time_engine(unsigned char time_instant_in_seconds){
 
 sekundes = sekundes + time_instant_in_seconds;
 
 if (sekundes == 60){
   sekundes = 0;
   minutes++;
   }
  if (minutes == 60){
     minutes = 0;
     stundas++;
   }
 }
 #pragma vector = PORT2_VECTOR
 
 __interrupt void P2_ISR(void){
 
 if((P2IFG & BIT5) == BIT5){
   
   P2IFG &= ~BIT5; //SW1 act
   mode++;
   
   if((alarm_minutes == minutes) && (alarm_hours == stundas)){
     alarm_on = 0;
   }
      if(mode == 5) mode = 0;
   }
   
   if((P2IFG & BIT4) == BIT4){
     
     P2IFG &= ~BIT4; //SW2 act
   
     if((P2IES & BIT4) == BIT4){
       P2IES &= ~BIT4;
       poga4 = sekundes;
     }
     else {
       P2IES |= BIT4;
     
       if(sekundes - poga4 > 1){
       //SW 2 long
       long_press();
       }
       else{
       //SW2 short
      short_press();
       }
     }
   }
}
 
void digit_blinking(unsigned char digit_position, unsigned char blink_digit_position1, unsigned char blink_digit_position2, unsigned int j2){
 
  if((j2 > 500) && (digit_position == blink_digit_position1))
   P2OUT &= ~(0x01 << digit_position);
   
  if((j2 > 500) && (digit_position == blink_digit_position2))
   P2OUT &= ~(0x01 << digit_position);
}
//SW1
void short_press(void){
 if(mode == 2){
 
   if(submode == 0){
     stundas++;
   
     if(stundas > 24);
   }
   
     if(submode == 1){
       minutes++;
       if(minutes  > 60);
     }
 }
 if(mode == 3){
 
   if(submode == 0)
     alarm_on = (alarm_on + 1)%2;
   
   if(submode == 1){
     alarm_hours++;
     if(alarm_hours > 23) alarm_hours=0;
   }
   
   if(submode == 2){
     alarm_minutes++;
     if(alarm_minutes > 59) alarm_minutes = 0;
   }
 }
}
//SW2
void long_press(void){
 submode++;
 if(submode == 3) submode = 0;
 }
//Indikācija 2
void indication2(unsigned char digit1, unsigned char digit2, unsigned char digit3,unsigned char digit4, unsigned char which_digit){
 P2OUT &= ~0x0F;
 if(which_digit == 0){
   P2OUT |= BIT0;
   display(digit1);
 }
 if(which_digit == 1){
   P2OUT |= BIT1;
   display(digit2);
 }
 if(which_digit == 2){
   P2OUT |= BIT2;
   display(digit3);
 }
 if(which_digit == 3) {
   P2OUT |= BIT3;
   display(digit4);
 }
}
//Melodija
void play(int n, int e){
 unsigned int del;
 unsigned long laiks;
 volatile unsigned long i;
 volatile unsigned long j;
 if (n==1) del = 47;
 if (n==2) del = 42;
 if (n==3) del = 37;
 if (n==4) del = 35;
 if (n==5) del = 31;
 if (n==6) del = 28;
 if (n==7) del = 25;
 if (e==1) laiks = 100000;
 if (e==2) laiks = 50000;
 if (e==4) laiks = 25000;
 for(i = 0; i < laiks; i = i + del + del){
   delay(del);
   P2OUT |= 0x0C;
   delay(del);
   P2OUT &= ~0x0C;
  }
}

