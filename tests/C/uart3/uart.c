#include <string.h>
#include <stdio.h>

#define TRACE (*(unsigned char *)0x40000000)

#define UART_REGISTERS_MEMORY_ADDRESS (*(unsigned char *)0x40008000)
#define UART_BASE (0x40008000UL)

typedef struct {
   volatile uint8_t thr;
   volatile uint8_t ier;
   volatile uint8_t reg_c;
   volatile uint8_t reg_d;
   volatile uint8_t reg_e;
} uart_registers_t;

#define UART1 (*(uart_registers_t *) UART_BASE)

int _write(int file, const char *ptr, int len) {
  int x;

  for (x = 0; x < len; x++) {
    TRACE =  *ptr++;
  }

  return (len);
}


int main(void) {

  uart_registers_t my_regs;
  
  //UART_REGISTERS_MEMORY_ADDRESS = 0x5A;
  my_regs.thr = 0x01;
  
  printf("UART REG A: 0x%08X\n", &UART1);
  printf("Address: 0x%08X\n", &my_regs);
    
  my_regs.ier = 0x02;
  my_regs.reg_c = 0x03;
  my_regs.reg_d = 0x04;
  my_regs.reg_e = 0x05;
  
  printf("Struct: 0x%08lX\n", my_regs.thr);
  printf("Struct: 0x%08lX\n", my_regs.ier);
  printf("Struct: 0x%08lX\n", my_regs.reg_c);
  printf("Struct: 0x%08lX\n", my_regs.reg_d);
  printf("Struct: 0x%08lX\n", my_regs.reg_e);
  
  
  asm volatile ("ecall");
}
