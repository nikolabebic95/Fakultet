//program.c

typedef unsigned char Byte8;
typedef unsigned short Word16;

//Kontroler prekida - 8259
#define ADR_8259_0				0x0022
#define ADR_8259_1				0x0026

//Serijski port - 8251
#define ADR_8251_DATA			0x0029
#define ADR_8251_CONTROL		0x0039

//Paralelni port - 8255
#define ADR_8255_0				0x000B
#define ADR_8255_1				0x000F
#define ADR_8255_2				0x001B
#define ADR_8255_3				0x001F

//Tajmer - 8254
#define ADR_8254_0				0x0018
#define ADR_8254_1				0x001C
#define ADR_8254_2				0x0008
#define ADR_8254_3				0x000C

//LCD Displej
#define CTRL_LCD_INST_CLEAR_DISP	0x01

#define CTRL_LCD_INST_RET_HOME		0x02

#define CTRL_LCD_INST_ENTRY_MODE	0x04
#define CTRL_LCD_INC_ADR			0x02
#define CTRL_LCD_DEC_ADR			0x00
#define CTRL_LCD_SHIFT_ON			0x01
#define CTRL_LCD_SHIFT_OFF			0x00

#define CTRL_LCD_INST_DISP_ON_OFF	0x08
#define CTRL_LCD_DISP_ON			0x04
#define CTRL_LCD_DISP_OFF			0x00
#define CTRL_LCD_CURS_ON			0x02
#define CTRL_LCD_CURS_OFF			0x00
#define CTRL_LCD_BLINK_ON			0x01
#define CTRL_LCD_BLINK_OFF			0x00

#define CTRL_LCD_INST_FUNCTION_SET	0x20
#define CTRL_LCD_8_BIT				0x10
#define CTRL_LCD_1_LINE				0x00
#define CTRL_LCD_5x7_DOTS			0x00

#define CTRL_LCD_INST_SHIFT			0x10
#define CTRL_LCD_SHIFT_CURS			0x00
#define CTRL_LCD_SHIFT_DISP			0x08
#define CTRL_LCD_SHIFT_RIGHT		0x04
#define CTRL_LCD_SHIFT_LEFT			0x00

#define CTRL_LCD_INST_DD_RAM_ADR	0x80

#define CTRL_LCD_BUSY_FLAG			0x80

void outp(Word16 addr, Byte8 data)
{
	_asm
	{
		push dx
		push ax
		mov dx, addr
		mov al, data
		out dx, al
		pop ax
		pop dx
	}
}

Byte8 inp(Word16 addr)
{
	Byte8 result;
	_asm
	{
		push dx
		push ax
		mov dx, addr
		in al, dx
		mov result, al
		pop ax
		pop dx
	}
	return result;
}

Byte8 messageInitial[] = "\n\r\n\rChoose an option [initial]:\n\r- S<len>{<char>} = set\n\r\n\r\0";
Byte8 messageUnlocked[] = "\n\r\n\rChoose an option [unlocked]:\n\r- R = remove\n\r- L = lock\n\r\n\r\0";
Byte8 messageLocked[] = "\n\r\n\rChoose an option [locked]:\n\r- U{<char>} = unlock\n\r\n\r\0";

typedef enum state_enum {
	INITIAL,
	WAIT_FOR_LEN,
	WAIT_FOR_PASS,
	LOCKED,
	UNLOCKING,
	GOOD,
	WAIT,
	MSG
} State;

State state = INITIAL;

State old = INITIAL;

int len = 0;
int curr = 0;

unsigned char password[10] = "";
unsigned char try[10] = "";

int init_transmit = 0;
int should_transmit = 0;
int transmit_len = 0;
int transmit_curr = 0;
Byte8 *buffer = messageInitial;

int accepted = 0;
int reject_counter = 0;

int matrix[4][4] = { {7, 8, 9, -1}, {4, 5, 6, -1}, {1, 2, 3, -1}, {-1, 0, -2, -1} };

unsigned char msg[1000];
int msg_cnt = 0;
int should_write = 1;

#define EOI (0x60)

void startTransmit() {
	init_transmit = 1;
	switch(state) {
	case INITIAL:
		buffer = messageInitial;
		transmit_len = 60;
		break;
	case LOCKED:
		buffer = messageLocked;
		transmit_len = 57;
		break;
	case GOOD:
		buffer = messageUnlocked;
		transmit_len = 63;
		break;
	case MSG:
		buffer = msg;
		transmit_len = msg_cnt;
		break;
	}

	transmit_curr = 0;
}

void reject() {
	accepted = 0;
	reject_counter = 0;
	state = WAIT;
	outp(ADR_8255_0, 0);
	outp(ADR_8254_3, 0x90);
	outp(ADR_8254_2, 0x64);
}

void accept() {
	accepted = 1;
	state = WAIT;
	outp(ADR_8254_3, 0x90);
	outp(ADR_8254_2, 0xCD);
}

void check() {
	int i;
	for (i = 0; i < len; i++) {
		if (password[i] != try[i]) {
			reject();
			return;
		}
	}

	accept();
}

int makeMask(int i) {
	switch(i) {
	case 0:
		return 0x00;
	case 1:
		return 0x01;
	case 2:
		return 0x03;
	case 3:
		return 0x07;
	case 4:
		return 0x0f;
	case 5:
		return 0x1f;
	case 6:
		return 0x3f;
	case 7:
		return 0x7f;
	case 8:
		return 0xff;
	default:
		return 0;
	}
}

void rxIntr() {
	Byte8 received = inp(ADR_8251_DATA);
	switch (state) {
	case INITIAL:
		if (received == 's' || received == 'S') state = WAIT_FOR_LEN;
		break;
	case WAIT_FOR_LEN:
		if (received >= '1' && received <= '8') {
			len = received - '0';
			curr = 0;
			state = WAIT_FOR_PASS;
		}
		break;
	case WAIT_FOR_PASS:
		password[curr++] = received;
		if (curr == len) {
			state = GOOD;
			startTransmit();
		}
		break;
	case LOCKED:
		if (received == 'u' || received == 'U') {
			curr = 0;
			state = UNLOCKING;
		}
		break;
	case UNLOCKING:
		try[curr++] = received;
		outp(ADR_8255_0, makeMask(curr));
		if (curr == len) check();
		break;
	case GOOD:
		if (received == 'r' || received == 'R') {
			state = INITIAL;
			startTransmit();
		}
		else if (received == 'l' || received == 'L') {
			state = LOCKED;
			startTransmit();
		}
		break;
	}
}

void txIntr() {
	if (should_transmit) {
		if (transmit_curr < transmit_len) outp(ADR_8251_DATA, buffer[transmit_curr++]);
		if (transmit_curr == transmit_len) {
			should_transmit = 0;
			if (state == MSG) state = old;
		}
	}
}

void cntIntr() {
	if (accepted) {		
		state = GOOD;
		outp(ADR_8255_0, 0);
		startTransmit();
	}
	else {
		reject_counter++;
		if (reject_counter % 2 == 0) {
			outp(ADR_8255_0, 0);
		}
		else {
			outp(ADR_8255_0, makeMask(len));
		}
		if (reject_counter < 6) {
			outp(ADR_8254_3, 0x90);
			outp(ADR_8254_2, 0x64);
		}
		else {
			state = LOCKED;
			startTransmit();
		}
	}
}

void keyIntr() {
	Byte8 portc;
	int column;
	int row;

	if (should_write == 0) return;
		should_write = 0;

	portc = ~inp(ADR_8255_2);

	if (portc & 0x01) {
		column = 0;
	}
	else if (portc & 0x02) {
		column = 1;
	}
	else if (portc & 0x04) {
		column = 2;
	}
	else return;

	outp(ADR_8255_1, 0x07);
	if (inp(ADR_8255_2) != 0x0f) {
		row = 3;
		outp(ADR_8255_1, 0);
	}
	else {
		outp(ADR_8255_1, 0x0B);
		if (inp(ADR_8255_2) != 0x0f) {
			row = 2;
			outp(ADR_8255_1, 0);
		}
		else {
			outp(ADR_8255_1, 0x0D);
			if (inp(ADR_8255_2) != 0x0f) {
				row = 1;
				outp(ADR_8255_1, 0);
			}
			else row = 0;
		}
	}
	
	outp(ADR_8255_1, 0);

	outp(ADR_8254_3, 0x50);
	outp(ADR_8254_1, 0xCD);

	if (matrix[row][column] == -2) {
		msg[msg_cnt++] = '\n';
		msg[msg_cnt++] = '\r';
		msg[msg_cnt++] = '\0';
		old = state;
		state = MSG;
		startTransmit();
		msg_cnt = 0;
	}
	else if (matrix[row][column] != -1) {
		msg[msg_cnt++] = matrix[row][column] + '0';
	}
}

void cntKeyIntr() {
	should_write = 1;
}

void interrupt prekidnaRutina() {
	Byte8 isr = inp(ADR_8259_0);

	if (isr & 0x04) {
		keyIntr();	
		outp(ADR_8259_0, EOI | 2);
	}
	else if (isr & 0x08) {
		rxIntr();
		outp(ADR_8259_0, EOI | 3);
	}
	else if (isr & 0x10) {
		txIntr();
		outp(ADR_8259_0, EOI | 4);
	}
	else if (isr & 0x20) {
		cntIntr();
		outp(ADR_8259_0, EOI | 5);
	}
	else if (isr & 0x40) {
		cntKeyIntr();
		outp(ADR_8259_0, EOI | 6);
	}
}

void initIntr() {
	outp(ADR_8259_0, 0x13);
	outp(ADR_8259_1, 0x10);
	outp(ADR_8259_1, 0x01);
	outp(ADR_8259_0, 0x0B);
}

void initParallel() {
	outp(ADR_8255_3, 0x81);
	outp(ADR_8255_0, 0x00);
	outp(ADR_8255_1, 0x00);
}

void initSerial() {
	outp(ADR_8251_CONTROL, 0x00);
	outp(ADR_8251_CONTROL, 0x00);
	outp(ADR_8251_CONTROL, 0x00);

	outp(ADR_8251_CONTROL, 0x40);

	outp(ADR_8251_CONTROL, 0x4E);
	outp(ADR_8251_CONTROL, 0x25);	
}

void initTimer() {}


void glavnaFunkcija() {
	initIntr();
	initParallel();
	initSerial();
	initTimer();

	state = INITIAL;

	matrix[0][1] = 7;
	matrix[0][1] = 8;
	matrix[0][2] = 9;
	matrix[0][3] = -1;

	matrix[1][0] = 4;
	matrix[1][1] = 5;
	matrix[1][2] = 6;
	matrix[0][3] = -1;

	matrix[2][0] = 1;
	matrix[2][1] = 2;
	matrix[2][2] = 3;
	matrix[0][3] = -1;

	matrix[3][0] = -1;
	matrix[3][1] = 0;
	matrix[3][2] = -2;
	matrix[3][3] = -1;
	
	startTransmit();

	should_write = 1;

	_asm sti;

	while (1) {
		if (init_transmit == 1) {
			while((inp(ADR_8251_CONTROL) & 0x01) == 0);
			should_transmit = 1;
			txIntr();
			init_transmit = 0;
		}
	}
}

