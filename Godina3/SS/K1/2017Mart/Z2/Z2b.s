@ Napisati program na ARM asembleru koji ispisuje niz brojeva pozivom funkcije iz Z2a.s. Prostor
@ za niz alocirati u sekciji za podatke. Niz treba da ima 100 elemenata koji se inicijalizuju u
@ vreme prevodjenja ponavljanjem vrednosti 1, 2 i 3 (1, 2, 3, 1, 2, 3, 1...).

.section .text

.extern recursiveArrayPrint
.extern printf

.global main
.func
@ int main() {
@     recursiveArrayPrint(arr, 100);
@     printf("\n");
@     return 0;
@ }
main:
    push {lr}                   @ save return address on stack
    ldr r0, =arr                @ load first parameter for recursiveArrayPrint (arr)
    mov r1, #100                @ load second parameter for recursiveArrayPrint (100)
    bl recursiveArrayPrint      @ call recursiveArrayPrint(arr, 100)
    ldr r0, =printf_newline     @ load parameter for printf ("\n")
    bl printf                   @ call printf("\n")
    mov r0, #0                  @ load return value
    pop {pc}                    @ return from main
    

.section .data

arr:
    .rept 33
    .long 1
    .long 2
    .long 3
    .endr
    .long 1

printf_newline:
    .asciz "\n"
