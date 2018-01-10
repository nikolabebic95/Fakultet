typedef unsigned char uchar_t;
typedef unsigned short ushort_t;

uchar_t digits_array[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };

ushort_t min = 1;
ushort_t sec = 1;
ushort_t cnt = 1;

void out_func(ushort_t address, uchar_t data) {
    _asm {
        push ax
        push dx
        mov dx, address
        mov al, data
        mov ah, al
        out dx, ax
        pop dx
        pop ax
    }
}

uchar_t in_func(ushort_t address) {
    uchar_t result;
    _asm {
        push dx
        mov dx, address
        in al, dx
        mov result, al
        pop dx
    }

    return result;
}

#define DISPLAY (0x0014)
#define DISPLAY_CONTROL_ADDRESS (DISPLAY | 0x0002)
#define DISPLAY_CONTROL_DATA (0x80)
#define DISPLAY_PORT_B_ADDRESS (DISPLAY | 0x0042)
#define DISPLAY_PORT_C_ADDRESS (DISPLAY)

void init_display() {
    out_func(DISPLAY_CONTROL_ADDRESS, DISPLAY_CONTROL_DATA);

    out_func(DISPLAY_PORT_C_ADDRESS, digits_array[8]);
    out_func(DISPLAY_PORT_B_ADDRESS, 0xf);
}

#define TIMER (0x0018)
#define TIMER_CONTROL_ADDRESS (TIMER | 0x0002)
#define TIMER_2_CONTROL_ADDRESS (TIMER | 0x0082)
#define TIMER_2_CONTROL_DATA (0x96)
#define TIMER_0_CONTROL_ADDRESS (TIMER | 0x0080)
#define TIMER_0_CONTROL_DATA (0x36)

void init_refresh() {
    out_func(TIMER_CONTROL_ADDRESS, TIMER_2_CONTROL_DATA);
    out_func(TIMER_2_CONTROL_ADDRESS, 0x10);
}

void init_timer() {
    out_func(TIMER_CONTROL_ADDRESS, TIMER_0_CONTROL_DATA);
    out_func(TIMER_0_CONTROL_ADDRESS, 0xf4);
    out_func(TIMER_0_CONTROL_ADDRESS, 0x01);    
}

#define INTR (0x0000)
#define ICW1_ADDR (INTR)
#define ICW1_DATA (0x13)
#define ICW2_ADDR (INTR | 0x0020)
#define ICW2_DATA (0x20)
#define ICW4_ADDR (INTR | 0x0020)
#define ICW4_DATA (0x01)
#define OCW2_ADDR (INTR)
#define OCW3_ADDR (INTR)
#define OCW3_DATA (0x0b)

#define EOI 0x60

void init_intr() {
    out_func(ICW1_ADDR, ICW1_DATA);
    out_func(ICW2_ADDR, ICW2_DATA);
    out_func(ICW4_ADDR, ICW4_DATA);
    out_func(OCW3_ADDR, OCW3_DATA);
}

void main_func() {
    min = sec = cnt = 0;
    init_display();
    init_intr();
    init_refresh();
    init_timer();

    _asm sti;
}

void interrupt interrupt_routine() {
    uchar_t isr = in_func(OCW2_ADDR);

    if (isr & 2) {
        min = sec = 0;
        out_func(OCW2_ADDR, EOI | 1);
    }
    else if (isr & 4) {
        sec++;
        if (sec >= 60) min++, sec = 0;

        out_func(OCW2_ADDR, EOI | 2);
    }
    else if (isr & 8) {
        out_func(DISPLAY_PORT_B_ADDRESS, 0x0);

        if (cnt == 0) {
            out_func(DISPLAY_PORT_C_ADDRESS, digits_array[min / 10]);
        }
        else if (cnt == 1) {
            out_func(DISPLAY_PORT_C_ADDRESS, digits_array[min % 10]);
        }
        else if (cnt == 2) {
            out_func(DISPLAY_PORT_C_ADDRESS, digits_array[sec / 10]);
        }
        else if (cnt == 3) {
            out_func(DISPLAY_PORT_C_ADDRESS, digits_array[sec % 10]);
        }

        out_func(DISPLAY_PORT_B_ADDRESS, 0x08 >> cnt);

        cnt++;
        if (cnt >= 4) cnt = 0;

        out_func(OCW2_ADDR, EOI | 3);
    }
}
