.section .text

.extern malloc
.extern free
.extern scanf
.extern perror
.extern exit

.func
safeAlloc:
    push {lr}
    bl malloc               @ call malloc(sizeof(ListElement))
    cmp r0, #0              @ check if malloc failed
    popne {pc}              @ if not failed, return what malloc returned
    bl perror               @ print error message
    mov r0, #1              @ argument = EXIT_FAILURE
    bl exit                 @ exit the program
.endfunc

.global recursiveLoadList
.func
@ r4 -> n, r5 -> head
@ ListElement *recursiveLoadList(int n) {
@     if (n == 0) return NULL;
@     ListElement *element = (ListElement *)malloc(sizeof(ListElement));
@     if (element == NULL) {
@         perror(NULL);
@         exit(EXIT_FAILURE);
@     }
@
@     scanf("%d", &element->data);
@     element->next = recursiveLoadList(n - 1);
@     return element;
@ }
recursiveLoadList:
    cmp r0, #0              @ compare n with 0 (recursion base case)
    moveq pc, lr            @ if n == 0 return NULL
    
    push {lr}               @ save link register for later use

    push {r4}               @ save r4 for use outside of function
    mov r4, r0              @ r4 = n

    mov r0, #8              @ argument = sizeof(ListElement)
    bl safeAlloc            @ allocate space
    push {r5}               @ save r5 for use outside of function
    mov r5, r0              @ r5 = allocated_pointer

    ldr r0, =scanf_format   @ first argument for scanf ("%d")
    mov r1, r5              @ second argument for scanf (&head->data)
    bl scanf                @ call scanf ("%d", &head->data)

    sub r0, r4, #1          @ r0 = r4 - 1 (argument = n - 1)
    bl recursiveLoadList    @ recursive call, recursiveLoadList(n - 1)

    add r5, r5, #4          @ r5 now points to data->next
    stm r5, {r0}            @ data->next = result_of_recursive_call 

    sub r0, r5, #4          @ return value = r5 - 4 (value of the pointer)

    pop {r5}                @ restore r5 
    pop {r4}                @ restore r4

    pop {pc}                @ return from function
.endfunc

.func 
@ void recursiveFreeList(ListElement *element) {
@     if (element == NULL) return;
@     recursiveFreeList(element->next);
@     free(element);
@ }
recursiveFreeList:
    push {lr}

    cmp r0, #0
    popeq {pc}

    push {r0}
    add r0, r0, #4
    ldr r0, [r0]
    bl recursiveFreeList

    pop {r0}
    bl free

    pop {pc}
.endfunc

.global asmFreeList
.func
@ void asmFreeList(ListElement **element) {
@     recursiveFreeList(*element);
@     *element = NULL;
@     return;
@ }
asmFreeList:
    push {lr}

    push {r0}
    ldr r0, [r0]
    bl recursiveFreeList
    
    pop {r0}
    mov r1, #0
    stm r0, {r1}

    pop {pc}
.endfunc

.section .data

scanf_format: .asciz "%d"
