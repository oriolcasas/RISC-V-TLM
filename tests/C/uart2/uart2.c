
#define UART_REGISTERS_MEMORY_ADDRESS (*(unsigned char *)0x40006000)

int main(void) {
  UART_REGISTERS_MEMORY_ADDRESS = 'H';
  UART_REGISTERS_MEMORY_ADDRESS = 'e';

  asm volatile ("ecall");
}