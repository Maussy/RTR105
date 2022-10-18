#include<stdio.h>

int main()
{
if(1); // iekš () var but "apaļa" nulle vai (visi biti ir ar 0) bitu seciba kas
      // satur  kaut vienu bitu ar 1

int a = 10;
if(a > 7)
printf("viena darbiba kas tiks izpildita, ja \"nosacijums ir speka\".\a");

printf("ši darbiba tiks izpildita jebkura gadijuma!\n");

if(a > 7)
{
printf("Darbibu bloks,kas tiks izpildits, ja \"nosacijums ir speka\".\n");
printf("Pirma darbiba.\n");
printf("Ōtra darbiba.\n");
}
if(a < 7)
{
printf("Darbibu bloks, kas tiks izpildits, ja\"nosacijums ir speka\".\n");
printf("Pirma darbiba.\n");
printf("Otra darbiba.\n");
}
else

{
printf("Darbibu bloks, kas tiks izpildits, ja \"nosacijums nav speka\".\a");
printf("Pirma darbiba.\n");
printf("Otra darbiba.\n");
}
return 0;
}
