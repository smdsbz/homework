#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////

struct ISR_BITS {
    unsigned int bit0: 1;
    unsigned int bit1: 1;
    unsigned int bit2: 1;
    unsigned int bit3: 1;
    unsigned int bit4: 1;
    unsigned int bit5: 1;
    unsigned int bit6: 1;
    unsigned int bit7: 1;
    unsigned int rsv : 8;
};


union ISR_REG {
    unsigned short all;
    struct ISR_BITS bit;
};


void isr0(void) { puts("The Interrupt Service Routine isr0 is called!"); }
void isr1(void) { puts("The Interrupt Service Routine isr1 is called!"); }
void isr2(void) { puts("The Interrupt Service Routine isr2 is called!"); }
void isr3(void) { puts("The Interrupt Service Routine isr3 is called!"); }
void isr4(void) { puts("The Interrupt Service Routine isr4 is called!"); }
void isr5(void) { puts("The Interrupt Service Routine isr5 is called!"); }
void isr6(void) { puts("The Interrupt Service Routine isr6 is called!"); }
void isr7(void) { puts("The Interrupt Service Routine isr7 is called!"); }


/////////////////////////////////////////////////////////////

void main(void) {

    void (*p_isr[8])(void);
    p_isr[0] = isr0; p_isr[1] = isr1; p_isr[2] = isr2; p_isr[3] = isr3;
    p_isr[4] = isr4; p_isr[5] = isr5; p_isr[6] = isr6; p_isr[7] = isr7;


    unsigned n, i;
    scanf("%u", &n); getchar();

    union ISR_REG *flags = (union ISR_REG *)malloc(n * sizeof(union ISR_REG));

    for (i = 0; i < n; ++i) {
        scanf("%hu", &(flags[i].all)); getchar();
    }



    for (i = 0; i < n; ++i) {

        /**** CORE CODE ****/

        printf("%hu:\n", flags[i].all);

        if (flags[i].bit.bit0) { p_isr[0](); }
        if (flags[i].bit.bit1) { p_isr[1](); }
        if (flags[i].bit.bit2) { p_isr[2](); }
        if (flags[i].bit.bit3) { p_isr[3](); }
        if (flags[i].bit.bit4) { p_isr[4](); }
        if (flags[i].bit.bit5) { p_isr[5](); }
        if (flags[i].bit.bit6) { p_isr[6](); }
        if (flags[i].bit.bit7) { p_isr[7](); }

        putchar('\n');

        /**** END ****/

    }



    for (i = 0; i < n; ++i) {
        free(flags+i);
    }


    return;
}
