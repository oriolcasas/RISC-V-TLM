#include <string.h>
#include <stdio.h>

#define TRACE (*(unsigned char *)0x40000000)

#define UART_REGISTER_A_MEMORY_ADDRESS_LO (*(unsigned char *)0x40008000)
#define UART_BASE (0x40008000UL)

typedef struct {
   volatile uint32_t reg_a;
   volatile uint32_t reg_b;
   volatile uint32_t reg_c;
   volatile uint32_t reg_d;
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
  
  UART_REGISTER_A_MEMORY_ADDRESS_LO = 0x5A;
  
  printf("UART REG A: 0x%08X\n", UART_REGISTER_A_MEMORY_ADDRESS_LO);
    
  UART1->reg_b = 0xC01DCAFE;
  UART1->reg_c = 0xACABACAB;
  UART1->reg_d = 0x12345678;
  
  printf("Struct: 0x%08lX\n", UART1->reg_a);
  printf("Struct: 0x%08lX\n", UART1->reg_b);
  printf("Struct: 0x%08lX\n", UART1->reg_c);
  printf("Struct: 0x%08lX\n", UART1->reg_d);
  
  
  asm volatile ("ecall");
}
