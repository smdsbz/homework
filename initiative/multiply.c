#include <stdio.h>
#include <inttypes.h>

#define BIT_SIZE  8

int main(int argc, const char *argv[]) {

  uint32_t a, b;
  uint64_t result = 0;

  scanf("%u %u", &a, &b);

  /*** MUL ***/
  size_t i;
  for (i = 0;
       i < sizeof(uint32_t) * BIT_SIZE;
       i++) {
    if (b & (0x1U << i)) {
      result += (uint64_t) (a << i);
    }
  }
  /*** MUL ***/

  printf("%lu\n", result);
}
