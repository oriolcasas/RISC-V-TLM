#include <string.h>
#include <stdio.h>

#define TRACE (*(unsigned char *)0x40000000)

#define UART_REGISTERS_MEMORY_ADDRESS (*(unsigned char *)0x40008000)
#define UART_BASE (0x40008000UL)

typedef struct {
   volatile uint8_t thr;
   volatile uint8_t ier;
   //volatile uint32_t reg_c;
   //volatile uint32_t reg_d;
   //volatile uint32_t reg_e;
} uart_registers_t;

#define UART1 ((uart_registers_t *) UART_BASE)

int _write(int file, const char *ptr, int len) {
  int x;

  for (x = 0; x < len; x++) {
    TRACE =  *ptr++;
  }

  return (len);
}


int main(void) {
  
  //UART_REGISTERS_MEMORY_ADDRESS = 0x5A;
  UART1->thr = 0x5A;
  
  printf("UART REG A: 0x%08X\n", UART_REGISTERS_MEMORY_ADDRESS);
    
  UART1->ier = 0xFF;
  //UART1->reg_c = 0xAC;
  //UART1->reg_d = 0x12;
  //UART1->reg_e = 0x6E;
  
  printf("Struct: 0x%08lX\n", UART1->thr);
  printf("Struct: 0x%08lX\n", UART1->ier);
  //printf("Struct: 0x%08lX\n", UART1->reg_c);
  //printf("Struct: 0x%08lX\n", UART1->reg_d);
  //printf("Struct: 0x%08lX\n", UART1->reg_e);
  
  
  asm volatile ("ecall");
}
