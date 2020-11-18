#include <string.h>
#include <stdio.h>

#define TRACE (*(unsigned char *)0x40000000)

#define UART_REGISTER_A (*(unsigned char *)0x40008000)
#define UART_REGISTER_B (*(unsigned char *)0x40008008)

int _write(int file, const char *ptr, int len) {
  int x;

  for (x = 0; x < len; x++) {
    TRACE =  *ptr++;
  }

  return (len);
}


int main(void) {

  unsigned char my_varA;
  unsigned char my_varB;

  //READ first
  my_varA=UART_REGISTER_A;
  my_varB=UART_REGISTER_B;

  printf("Initial Values: \n");
  printf("Register A: %08lX \n", my_varA);
  printf("Register B: %08lX \n", my_varB);

  //WRITE after
  UART_REGISTER_A = 16;
  UART_REGISTER_B = 255;

  //READ again
  my_varA=UART_REGISTER_A;
  my_varB=UART_REGISTER_B;

  printf("Written Values: \n");
  printf("Register A: %08lX \n", my_varA);
  printf("Register B: %08lX \n", my_varB);


  asm volatile ("ecall");
}
