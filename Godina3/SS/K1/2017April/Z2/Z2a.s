@ Na ARM asembleru napisati rekurzivnu funkciju int recursivePrintList(ListElement *head, int x) za obradu
@ jednostruko ulancane liste. Tip ListElement, kao i kod za ucitavanje jednostruko ulancane liste dati
@ su u fajlu "List.c". Konvencija pozivanja treba da bude u skladu sa AAPCS. Funkcija treba da ispise
@ sve elemente liste koji se za manje od x razlikuju od sledeceg elementa u listi, a kao rezultat treba da
@ vrati broj elemenata jednakih x. Na pocetku funkcije recursivePrintList treba pozvati funkciju test
@ definisanu u fajlu "List.c".

.section .text

.extern test
.extern printf

.global recursivePrintList
.func
@ int recursivePrintList(ListElement *head, int x) {
@     int ret, diff;
@     test();
@     ret = 0;
@     if (head == nullptr) return ret;
@     if (head->data == x) ret++;
@     if (head->next == nullptr) return ret;
@     diff = head->data - head->next->data;
@     if (diff < 0) diff = -diff;
@     if (diff < x) printf("%d ", head->data);
@ }
recursivePrintList:
    push {lr}               @ save return address on stack
    push {r0}               @ save head for later use
    push {r1}               @ save x for later use
    bl test                 @ call test function
    pop {r1}                @ restore x
    pop {r0}                @ restore head
    push {r4}               @ save r4 on stack (r4 will be used as a counter)
    mov r4, #0              @ ret = 0;
    cmp r0, #0              @ compare head with nullptr
    beq returnFromFunction  @ if (head == nullptr) return ret;
    b check
recurse:
    add r0, r0, #4
    ldr r0, [r0]
    bl recursivePrintList   @
    add r4, r4, r0
    b returnFromFunction

check:
    ldr r2, [r0]            @ r2 = head->data
    cmp r2, r1              @ compare head->data with x
    addeq r4, r4, #1        @ if (head->data == x) ret++;

    ldr r2, [r0]            @ r2 = head->data
    mov r3, r0              @ r3 = head
    add r3, r3, #4          @ r3 = &head->next
    ldr r3, [r3]            @ r3 = *r3 (effectively r3 becomes head->next)
    cmp r3, #0              @ compare r3 with nullptr
    beq returnFromFunction  @ if (head->next == nullptr) return;
    ldr r3, [r3]            @ r3 = *r3 (r3 becomes head->next->data)

    sub r2, r2, r3          @ r2 = r2 - r3
    cmp r2, #0              @ compare r2 with 0
    movlt r3, #0            @ r3 = 0 (sub must take register as second argument)
    sublt r2, r3, r2        @ if (r2 < 0) r2 = -r2; (r2 becomes difference between elements)

    cmp r2, r1              @ compare r2 (difference) and x
    bge recurse             @ if (diff >= x) skip printing and recurse

    push {r0}               @ save head for later use
    push {r1}               @ save x for later use
    ldr r1, [r0]            @ r1 = head->data; // second parameter for printf
    ldr r0, =printf_format  @ r0 = "%d "; // first parameter for printf
    bl printf               @ call printf("%d ", head->data);
    pop {r1}                @ restore x
    pop {r0}                @ restore head
    b recurse               @ return from printing

returnFromFunction:
    mov r0, r4
    pop {r4} 
    pop {pc}

.section .data

printf_format: 
    .asciz "%d "
