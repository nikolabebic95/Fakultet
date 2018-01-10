public __PIA

RAM_SIZE_IN_PARS EQU 1000h

extern _interrupt_routine: far ptr
extern _main_func: far ptr

ivtRam SEGMENT 'IVTRAM'
DD 256 DUP (_interrupt_routine)
ivtRam ENDS

dataRam SEGMENT 'DATARAM'
dataRam ENDS

stack SEGMENT 'STACK'
stack ENDS

code SEGMENT 'CODE'

initialize:
	; initialize stack segment
	mov ax, stack
	mov ss, ax

	; initialize stack offset
	mov bx, RAM_SIZE_IN_PARS
	sub bx, ax
	test bx, 0xf000
	jne enough

	mov cl, 4
	shl bx, cl
	mov sp, bx
	jmp far ptr initialize_ivt
enough:
	mov sp, 0xfffe

initialize_ivt:
	mov ax, ivtRam
	mov es, ax
	mov ax, ivtRom
	mov ds, ax
	mov ax, 0
	mov si, ax
	mov di, ax
	mov cx, 512
	rep movsw

	; initialize data segment
	mov ax, dataRam
	mov es, ax
	mov ax, dataRom
	mov ds, ax
	mov ax, 0
	mov si, ax
	mov di, ax
	mov cx, 16
	rep movsw

call_main:
	call _main_func
infinity_loop:
	jmp infinity_loop

; PointerIntegerAdd (procedura koju uvozi objektni fajl "program.obj" za pristup nizovima)
__PIA proc far
			add AX, BX
			retf
__PIA endp

code ENDS

dataRom SEGMENT 'DATAROM'
dataRom ENDS

ivtRom SEGMENT 'IVTROM'
ivtRom ENDS

startup SEGMENT 'STARTUP'
	jmp far ptr initialize
startup ENDS

END
