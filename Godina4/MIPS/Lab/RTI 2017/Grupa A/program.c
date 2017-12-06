typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef signed char char_t;
typedef signed short short_t;

#define DISPLAY (0x000A)
#define DISPLAY_CONTROL (0x80)
#define DISPLAY_CONTROL_ADDRESS (DISPLAY | 0x0020)
#define DISPLAY_PORT_A (DISPLAY | 0x0040)
#define DISPLAY_PORT_B (DISPLAY | 0x0060)
#define DISPLAY_ALL_SEGMENTS (0xfe)

#define TIMER (0x000c)
#define TIMER_CONTROL_ADDRESS (TIMER | 0x0010)
#define TIMER_REFRESH_CONTROL (0x96)
#define TIMER_REFRESH_ADDRESS (TIMER | 0x0090)
#define TIMER_SEC_CONTROL (0x36)
#define TIMER_SEC_ADDRESS (TIMER | 0x0080)

#define INTR (0x0000)
#define INTR_ICW1_ADDRESS (INTR)
#define INTR_ICW2_ADDRESS (INTR | 0x0080)
#define INTR_ICW4_ADDRESS (INTR | 0x0080)
#define INTR_OCW2_ADDRESS (INTR)
#define INTR_OCW3_ADDRESS (INTR)
#define INTR_ICW1_DATA (0x13)
#define INTR_ICW2_DATA (0x20)
#define INTR_ICW4_DATA (0x01)
#define INTR_OCW3_DATA (0x0b)

#define ISR (INTR_OCW3_ADDRESS)
#define EOI (0x60)

uchar_t digits_array[] = { 0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6 };

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

void out_func(ushort_t address, uchar_t data) {
    _asm {
        push dx
        push ax
        mov dx, address
        mov al, data
        out dx, al
        pop ax
        pop dx
    }
}

void out_func_upper(ushort_t address, uchar_t data) {
    _asm {
        push dx
        push ax
        mov dx, address
        mov ah, data
        mov al, 0
        out dx, ax
        pop ax
        pop dx
    }
}

ushort_t counter = 1;

ushort_t min = 1;
ushort_t sec = 1;

void interrupt interrupt_routine() {
    uchar_t isr = in_func(ISR);

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
        out_func(DISPLAY_PORT_B, 0xff);

        if (counter == 0) {
            out_func(DISPLAY_PORT_A, digits_array[min / 10]);
        }
        else if (counter == 1) {
            out_func(DISPLAY_PORT_A, digits_array[min % 10]);
        }
        else if (counter == 2) {
            out_func(DISPLAY_PORT_A, digits_array[sec / 10]);
        }
        else if (counter == 3) {
            out_func(DISPLAY_PORT_A, digits_array[sec % 10]);
        }

        out_func(DISPLAY_PORT_B, ~(0x08 >> counter));
        counter++;
        if (counter >= 4) counter = 0;
        out_func(INTR_OCW2_ADDRESS, EOI | 3);
    }
}

void init_display() {
    out_func(DISPLAY_CONTROL_ADDRESS, DISPLAY_CONTROL);
    out_func(DISPLAY_PORT_A, digits_array[0]);
    out_func(DISPLAY_PORT_B, 0x0);
}

void init_refresh_timer() {
    out_func_upper(TIMER_CONTROL_ADDRESS, TIMER_REFRESH_CONTROL);
    out_func_upper(TIMER_REFRESH_ADDRESS, 0x20);
}

void init_sec_timer() {
    out_func_upper(TIMER_CONTROL_ADDRESS, TIMER_SEC_CONTROL);
    out_func_upper(TIMER_SEC_ADDRESS, 0xf4);
    out_func_upper(TIMER_SEC_ADDRESS, 0x01);
}

void init_intr_control() {
    out_func(INTR_ICW1_ADDRESS, INTR_ICW1_DATA);
    out_func(INTR_ICW2_ADDRESS, INTR_ICW2_DATA);
    out_func(INTR_ICW4_ADDRESS, INTR_ICW4_DATA);
    out_func(INTR_OCW3_ADDRESS, INTR_OCW3_DATA);
}

void main_func() {
    min = 0;
    sec = 0;
    counter = 0;
    init_display();
    init_intr_control();
    init_sec_timer();
    init_refresh_timer();

    _asm sti;
}
