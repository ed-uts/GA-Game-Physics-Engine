clang   -I/usr/riscv64-linux-gnu/include/ \
        -I/usr/riscv64-linux-gnu/include/c++/11/ \
        --target=riscv64 -march=rv64gcv main.c -c -o main.o
riscv64-linux-gnu-ld -o main -dynamic-linker \
    /usr/riscv64-linux-gnu/lib/ld-linux-riscv64-lp64d.so.1 \
    /usr/riscv64-linux-gnu/lib/crt1.o /usr/riscv64-linux-gnu/lib/crti.o \
    -lc main.o /usr/riscv64-linux-gnu/lib/crtn.o
