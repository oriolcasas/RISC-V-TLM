#include <string.h>
#include <stdio.h>

#define TRACE (*(unsigned char *)0x40000000)

#define UART_REGISTERS_MEMORY_ADDRESS (*(unsigned char *) 0x40008000)
//#define UART_REGISTERS_MEMORY_ADDRESS_2 (*(unsigned char *)0x40008100)

//#define UART_REGISTERS_BASE (0x40008000UL)


  typedef struct {
    volatile uint8_t   rbr;   // R: Rx buffer,
    volatile uint8_t   thr;   // W: Tx hold reg,
    volatile uint8_t   ier;   // R/W: Interrupt Enable Register
    volatile uint8_t   iir;   // R: Interrupt ID Register
    volatile uint8_t   lcr;   // R/W: Line Control Register
    volatile uint8_t   mcr;   // W: Modem Control Register
    volatile uint8_t   lsr;   // R: Line Status Register
    volatile uint8_t   msr;   // R: Modem Status Register
    volatile uint8_t   scr;   // R/W: Scratch Register            
    volatile uint8_t    dl;   // R/W: Divisor Latch
  } uart_regs;

#define UART_REGISTERS ((uart_regs *) UART_REGISTERS_MEMORY_ADDRESS)

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
  my_varA=UART_REGISTERS->rbr;
  my_varB=UART_REGISTERS->thr;

  printf("Initial Values: \n");
  printf("Register A: %08lX \n", my_varA);
  printf("Register B: %08lX \n", my_varB);

  //WRITE after
  UART_REGISTERS->rbr = 11;
  UART_REGISTERS->thr = 254;

  //READ again
  my_varA=UART_REGISTERS->rbr;
  my_varB=UART_REGISTERS->thr;

  printf("Written Values: \n");
  printf("Register A: %08lX \n", my_varA);
  printf("Register B: %08lX \n", my_varB);


  asm volatile ("ecall");
}
