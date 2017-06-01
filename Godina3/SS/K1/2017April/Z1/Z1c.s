#; Napisati program na x86 asembleru koji poziva potprogram rotateLeft opisan u fajlu Z1a.s, pri cemu za poziv treba
#; da koristi labele opisane u fajlu Z1b.s kako bi izracunao broj elemenata niza. Posle poziva potprograma, program
#; treba da ispise sadrzaj niza na standardni izlaz.

.intel_syntax noprefix
.arch i386

.data

.extern rotateLeft

.extern ARRAY_BEGIN
.extern ARRAY_END

.extern scanf
.extern printf

out_string_number:
        .asciz "%d "

out_string_endl:
        .asciz "\n"

ask_for_x_string:
        .asciz "Input number x: "

scanf_int:
        .asciz "%d"

variable:
        .long 0

.text

#; Before rotateLeft:
#; eax -> everything, ebx -> pointer to array
#;
#; After rotateLeft:
#; eax -> array length, ebx -> pointer to array, ecx -> iterator, edx -> helper
#;
#; int main() {
#;     int i;
#;     printf("Input...");
#;     scanf("%d", &variable);
#;     rotateLeft(variable, ARRAY_BEGIN, ARRAY_END - ARRAY_BEGIN);
#;     for (i = 0; i < ARRAY_END - ARRAY_BEGIN; i++) {
#;         printf("%d ", ARRAY_BEGIN[i]);
#;     }        
#;
#;     printf("\n");
#;     return 0;
#; }
#;
#;
.globl main
main:
        enter 0, 0                              #; start the function
        push ebx                                #; save ebx (function must preserve the value of ebx)
        mov eax, offset ask_for_x_string        #; eax = "Input..."
        push eax                                #; push argument for printf
        call printf                             #; call printf("...")
        add esp, 4                              #; pop argument from stack (printf is cdecl)
        lea eax, variable                       #; eax = &variable
        push eax                                #; push second argument for scanf (&variable)
        mov eax, offset scanf_int               #; eax = "%d"
        push eax                                #; push first argument for scanf ("%d")
        call scanf                              #; call scanf("%d", &variable)
        add esp, 8                              #; pop arguments from stack (scanf is cdecl)
        push variable                           #; push third argument for rotateLeft (variable)
        mov eax, offset ARRAY_END               #; eax = address after the end of array
        sub eax, offset ARRAY_BEGIN             #; eax -= address of th beggining of the array
        shr eax, 2                              #; eax /= sizeof(int) -- eax becomes array length
        push eax                                #; push second argument for rotateLeft (array length)
        mov ebx, offset ARRAY_BEGIN             #; ebx = address of array
        push ebx                                #; push first argument for rotateLetft (pointer to array)
        call rotateLeft                         #; call rotateLeft(array, length, variable)
        mov eax, offset ARRAY_END               #; eax = address after the end of array
        sub eax, offset ARRAY_BEGIN             #; eax -= address of th beggining of the array
        shr eax, 2                              #; eax /= sizeof(int) -- eax becomes array length
        mov ecx, 0                              #; ecx = 0
1:      cmp ecx, eax                            #; loop for (ecx = 0; ecx < array_length; ecx++)
        je 1f                                   #; if condition not met jump out of loop
        push eax                                #; save eax because printf will change it
        push ecx                                #; save ecx because printf will change it
        push [ebx + 4 * ecx]                    #; push second argument for printf (arr[ecx])
        mov edx, offset out_string_number       #; edx = "%d "
        push edx                                #; push first argument for printf ("%d ")
        call printf                             #; call printf("%d ", arr[ecx])
        add esp, 8                              #; pop arguments from stack (printf is cdecl)
        pop ecx                                 #; restore ecx
        pop eax                                 #; restore eax
        inc ecx                                 #; ecx++ (third instruction in the above for loop)
        jmp 1b                                  #; jump to beggining of loop
1:      mov edx, offset out_string_endl         #; edx = "\n"
        push edx                                #; push argument for printf ("\n")
        call printf                             #; call printf("\n")
        add esp, 8                              #; pop arguments from stack (printf is cdecl)
        pop ebx                                 #; restore ebx
        leave                                   #; prepare to leave the function
        mov eax, 0                              #; return value from main is 0
        ret                                     #; return 0
