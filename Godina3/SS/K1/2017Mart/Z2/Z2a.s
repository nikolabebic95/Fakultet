@ Na ARM asembleru napisati rekurzivnu funkciju koja ispisuje elemente prosledjenog niza s kraja
@ ka pocetku. Konvencija pozivanja funkcije treba da bude u skladu sa AAPCS.

.section .text

.extern printf

.global recursiveArrayPrint
.func
@ arr -> r0, n -> r1
@
@ void recursiveArrayPrint(int arr[], int n) {
@     if (n < 1) return;
@     if (n > 1) recursiveArrayPrint(arr + 1, n - 1);
@     printf("%d ", arr[0]);
@     
@ }
recursiveArrayPrint:
    cmp r1, #1              @ compare n with 1
    movlt pc, lr            @ if (n < 1) return from function
    bgt recurse             @ if (n > 1) recurse
printElement:    
    ldr r1, [r0]            @ r1 = second parameter for printf (arr[0])
    ldr r0, =printf_format  @ r0 = first parameter for printf ("%d ")
    stmfd sp!, {lr}         @ save return address on stack
    bl printf               @ call printf for current element
    ldmfd sp!, {pc}         @ return from function

recurse:
    stmfd sp!, {r0, lr}     @ save the array address and return address on stack
    add r0, r0, #4          @ arr = arr + sizeof(int)
    sub r1, r1, #1          @ n = n - 1
    bl recursiveArrayPrint  @ recursive call to the above function with new parameters
    ldmfd sp!, {r0, lr}     @ restore the array address and return address from stack
    b printElement          @ return to function

.section .data
printf_format:  .asciz  "%d "
