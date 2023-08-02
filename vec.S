    .text
    .align 2

#define output a0

    .globl vector_sum
vector_sum:
    vsetvli t0, a1, e32
    fmv.w.x fa0, zero
    vfmv.s.f v1, fa0
    vle32.v v0, (a0)
    vfredusum.vs v1, v0, v1
    vfmv.f.s fa0, v1
    ret

    .globl dot_product_2
dot_product_2:
    vsetvli t0, a2, e32
    fmv.w.x fa0, zero
    vfmv.s.f v3, fa0
    vle32.v v0, (a0)
    vle32.v v1, (a1)
    vfmul.vv  v2, v1, v0
    vfredusum.vs v3, v2, v3
    vfmv.f.s fa0, v3
    ret

    .globl dot_product_3
dot_product_3:
    vsetvli t0, a3, e32
    fmv.w.x fa0, zero
    vfmv.s.f v5, fa0
    vle32.v v0, (a0)
    vle32.v v1, (a1)
    vle32.v v2, (a2)
    vfmul.vv  v3, v1, v0
    vfmul.vv  v4, v3, v2
    vfredusum.vs v5, v4, v5
    vfmv.f.s fa0, v5
    ret

