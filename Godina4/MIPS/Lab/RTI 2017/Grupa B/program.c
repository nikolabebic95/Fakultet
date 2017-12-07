typedef unsigned char uchar_t;
typedef unsigned short ushort_t;

uchar_t digits_array[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
ushort_t min = 1;
ushort_t sec = 1;
ushort_t cnt = 1;

#define DISPLAY (0x000c)
#define DISPLAY_CONTROL (0x80)
#define DISPLAY_CONTROL_ADDRESS (DISPLAY | 0x0002)
#define DISPLAY_PORT_A (DISPLAY | 0x0020)
#define DISPLAY_PORT_B (DISPLAY)

#define TIMER (0x0008)
#define TIMER_CONTROL_ADDRESS (TIMER | 0x0010)
#define TIMER_0_ADDRESS (TIMER | 0x0002)
#define TIMER_0_CONTROL (0x36)
#define TIMER_2_ADDRESS (TIMER)
#define TIMER_2_CONTROL (0x96)

#define INTR (0x0004)
#define INTR_ICW1_ADDRESS (INTR)
#define INTR_ICW2_ADDRESS (INTR | 0x0040)
#define INTR_ICW4_ADDRESS (INTR | 0x0040)
#define INTR_OCW2_ADDRESS (INTR)
#define INTR_OCW3_ADDRESS (INTR)
#define INTR_ICW1_DATA (0x13)
#define INTR_ICW2_DATA (0x20)
#define INTR_ICW4_DATA (0x01)
#define INTR_OCW3_DATA (0x0b)

#define EOI (0x60)

void out_func(ushort_t address, uchar_t data) {
    _asm {
        push dx
        push ax
        mov al, data
        mov ah, al
        mov dx, address
        out dx, ax
        pop ax
        pop dx
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

void init_display() {
    out_func(DISPLAY_CONTROL_ADDRESS, DISPLAY_CONTROL);

    out_func(DISPLAY_PORT_B, digits_array[8]);
    out_func(DISPLAY_PORT_A, 0);
}

void init_refresh() {
    out_func(TIMER_CONTROL_ADDRESS, TIMER_2_CONTROL);
    out_func(TIMER_2_ADDRESS, 0x04);
}

void init_intr() {
    out_func(INTR_ICW1_ADDRESS, INTR_ICW1_DATA);
    out_func(INTR_ICW2_ADDRESS, INTR_ICW2_DATA);
    out_func(INTR_ICW4_ADDRESS, INTR_ICW4_DATA);
    out_func(INTR_OCW3_ADDRESS, INTR_OCW3_DATA);
}

void init_timer() {
    out_func(TIMER_CONTROL_ADDRESS, TIMER_0_CONTROL);
    out_func(TIMER_0_ADDRESS, 0xd0);
    out_func(TIMER_0_ADDRESS, 0x07);
}

void main_func() {
    cnt = min = sec = 0;

    init_display();
    init_intr();
    init_refresh();
    init_timer();

    _asm sti;
}

void interrupt interrupt_routine() {
    uchar_t isr = in_func(INTR_OCW2_ADDRESS);

    if (isr & 0x02) {
        min = 0;
        sec = 0;
        out_func(INTR_OCW2_ADDRESS, EOI | 1);
    }
    else if (isr & 0x04) {
        sec++;
        if (sec >= 60) min++, sec = 0;

        out_func(INTR_OCW2_ADDRESS, EOI | 2);
    }
    else if (isr & 0x08) {
        out_func(DISPLAY_PORT_A, 0xff);
        
        if (cnt == 0) {
            out_func(DISPLAY_PORT_B, digits_array[min / 10]);
        }
        else if (cnt == 1) {
            out_func(DISPLAY_PORT_B, digits_array[min % 10]);
        }
        else if (cnt == 2) {
            out_func(DISPLAY_PORT_B, digits_array[sec / 10]);
        }
        else if (cnt == 3) {
            out_func(DISPLAY_PORT_B, digits_array[sec % 10]);
        }
        
        out_func(DISPLAY_PORT_A, ~(0x08 >> cnt));
        cnt++;
        if (cnt >= 4) cnt = 0;

        out_func(INTR_OCW2_ADDRESS, EOI | 3);
    }
}
