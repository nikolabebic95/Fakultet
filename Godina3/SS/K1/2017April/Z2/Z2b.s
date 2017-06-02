@ Napisati program na ARM asembleru (funkciju main) koji sa standardnog ulaza ucita broj elemenata u listi,
@ zatim pozivom funkcije loadList formira jednostruko ulancanu listu ucitavanjem zadatog broja brojeva, zatim
@ pozove potprogram za obradu i na kraju obrise kreiranu listu pozivom potprograma freeList.

.section .text

.extern loadList
.extern freeList
.extern printList
.extern recursivePrintList
.extern printf
.extern scanf

.global main
.func
@ int main() {
@     int variable;
@     ListElement *ptr;    
@     printf("Input number of elements in list: ");
@     scanf("%d", &variable);
@     printf("Input list: ")
@     ptr = readList(variable);
@     printf("Input x: ");
@     scanf("%d", &variable);
@     printf("Number of matching elements: %d", recursivePrintList(ptr, variable));
@     freeList(&variable);
@     return 0;     
@ }
main:
    push {lr}                               @ save return address for later use
    ldr r0, =ask_for_number_of_elements     @ r0 = parameter for printf ("...")
    bl printf                               @ call printf("...")
    ldr r0, =scanf_format                   @ r0 = first parameter for scanf ("%d")
    ldr r1, =variable                       @ r1 = second parameter for scanf (&variable)
    bl scanf                                @ call scanf("%d", &variable)
    ldr r0, =ask_for_list                   @ r0 = parameter for printf("...")
    bl printf                               @ call printf("...")
    ldr r0, =variable                       @ r0 = &variable
    ldr r0, [r0]                            @ r0 = *r0 (variable - parameter for loadList - list size)
    bl loadList                             @ call loadList(size)
    ldr r1, =ptr                            @ r1 = &ptr 
    stm r1, {r0}                            @ *r1 = r0 (what loadList returned)
    ldr r0, =ask_for_x                      @ r0 = parameter for printf ("...")
    bl printf                               @ call printf("...")
    ldr r0, =scanf_format                   @ r0 = first parameter for scanf ("%d")
    ldr r1, =variable                       @ r1 = second parameter for scanf (&variable)
    bl scanf                                @ call scanf("%d", &variable)
    ldr r1, =variable                       @ r1 = &variable
    ldr r1, [r1]                            @ r1 = *r1 (variable - x - second parameter for recursivePrintList)
    ldr r0, =ptr                            @ r0 = &ptr
    ldr r0, [r0]                            @ r0 = *r0 (head of the list - first parameter for recursivePrintList)
    bl recursivePrintList                   @ call recursivePrintList(head, x)
    mov r1, r0                              @ r1 = returned value (second parameter for printf)
    ldr r0, =printf_format                  @ r0 = "..." -- first parameter for printf
    bl printf                               @ call printf("... %d ...", ret_val)
    ldr r0, =ptr                            @ r0 = first parameter for freeList (&head)
    bl freeList                             @ call freeList(&head)
    mov r0, #0                              @ write return value from main to r0
    pop {pc}                                @ return from main


.section .data

ptr: .long 0
variable: .long 0

ask_for_number_of_elements:
    .asciz "Input number of elements in list: "

ask_for_list:
    .asciz "Input list: "

ask_for_x:
    .asciz "Input x: "

printf_format:
    .asciz "\nNumber of matching elements: %d\n"

scanf_format:
    .asciz "%d"
