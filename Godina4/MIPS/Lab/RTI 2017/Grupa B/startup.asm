public __PIA

extern _main_func: far ptr
extern _interrupt_routine: far ptr

RAM_SIZE_IN_PAR EQU 0x1000

ivtRam SEGMENT 'IVTRAM'
	DD 256 DUP (_interrupt_routine)
ivtRam ENDS

dataRam SEGMENT 'DATARAM'
dataRam ENDS

stack SEGMENT 'STACK'
stack ENDS

code SEGMENT 'CODE'

init:
	; initialize stack segment
	mov ax, stack
	mov ss, ax

	; initialize stack pointer
	mov bx, RAM_SIZE_IN_PAR
	sub bx, ax

	test bx, 0xf000
	jne skip

	mov cl, 4
	shl bx, cl
	mov sp, bx

	jmp init_ivt
skip:
	mov sp, 0xfffe

init_ivt:
	mov ax, ivtRam
	mov es, ax
	mov ax, ivtRom
	mov ds, ax
	mov ax, 0
	mov si, ax
	mov di, ax
	mov cx, 256
	rep movsw

	; init data
	mov ax, dataRam
	mov es, ax
	mov ax, dataRom
	mov ds, ax
	mov ax, 0
	mov si, ax
	mov di, ax
	mov cx, 16
	rep movsw
	
	; call main
	call _main_func

	; only interrupts are executed from here on
infinity:
	jmp infinity

; PointerIntegerAdd (procedura koju uvozi objektni fajl "program.obj" za pristup nizovima)
__PIA proc far
			add AX, BX
			retf
__PIA endp

code ENDS

ivtRom SEGMENT 'IVTROM'
ivtRom ENDS

dataRom SEGMENT 'DATAROM'
dataRom ENDS

startup SEGMENT 'STARTUP'
	jmp far ptr init
startup ENDS

END
