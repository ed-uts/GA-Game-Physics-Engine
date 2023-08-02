#include <stdio.h>
#include <riscv_vector.h>

#define NUM_VALUES 32

void merge(uint32_t bitmask, float* result) {
  asm volatile("vsetvli zero, %0, e32, m1, ta, mu" : : "r"(1));
  asm volatile("vle32.v v0, (%0)" : : "r"(&bitmask) ); // load 32-bit bitmask
  size_t l = 0;
  for (size_t avl = NUM_VALUES; avl > 0; avl -= l) {
    asm volatile("vfmv.v.f v1, %0" : : "f"(0.0f));
    asm volatile("vsetvli %0, zero, e32, m1, ta, mu" : "=r"(l) : );
    asm volatile("vfmerge.vfm v3, v1, %0, v0" : : "f"(1.0f));
    size_t index = NUM_VALUES - avl;
    asm volatile("vse32.v v3, (%0)" : : "r"(&result[index])  );
    bitmask >>= l;
    asm volatile("vle32.v v0, (%0)" : : "r"(&bitmask) ); // load shift 32-bit bitmask
  }
}

int main() {
  float values[NUM_VALUES] = {0.5};

  uint32_t bitmask = 0b11110101;

  merge(bitmask, values);
  for (size_t i = 0; i < NUM_VALUES; ++i) {
    printf("%f ", values[i]);
    if (!((i + 1) % 4))
      printf("\n");
  }

  return 0;
}
