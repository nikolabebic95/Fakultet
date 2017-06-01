#; Napisati program na x86 asembleru koji ucita broj elemenata niza, alocira prostor u dinamickoj zoni
#; podataka, popuni elemente vrednostima redom od 1, zatim procita broj koji je potrebno pronaci, pozove napisani
#; potprogram, ispise rezultat poziva i oslobodi alocirani prostor. Za ciranje i ispis podataka koristiti scanf i
#; printf funkcije

.intel_syntax noprefix
.arch i386

.data

printf_format_number_of_elements:
        .asciz "Input number of elements: "

printf_format_number_to_search_for:
        .asciz "Input number to search for in array: "

printf_format_result:
        .asciz "Index of found number is %d\n"

printf_format_unsuccessful:
        .asciz "Number not found in array\n"

scanf_format:
        .asciz "%d"

.text

.macro START_FUNCTION
enter 0, 0 
push ebx
push ecx
push edx
.endm

.macro END_FUNCTION
pop edx
pop ecx
pop ebx
leave
ret
.endm

.macro START_VOID_FUNCTION
START_FUNCTION
push eax
.endm

.macro END_VOID_FUNCTION
pop eax
END_FUNCTION
.endm

.macro CALL_FUNCTION_ONE_PARAM func, param
push \param
call \func
add esp, 4
.endm

.macro CALL_FUNCTION_TWO_PARAMS func, param1, param2
push \param2
push \param1
call \func
add esp, 8
.endm

.macro CALL_FUNCTION_THREE_PARAMS func, param1, param2, param3
push \param3
push \param2
push \param1
call \func
add esp, 12
.endm

.extern malloc
.extern free
.extern exit
.extern scanf
.extern printf

.extern findInArray

#; void *allocateSpace(unsigned size) {
#;     void *ret = malloc(size * sizeof(int));
#;     if (ret == NULL) {
#;         exit(-1);   
#;     }
#;
#;     return ret;
#; }
allocateSpace:
        START_FUNCTION                                  #; starts the function
        mov ebx, [ebp + 8]                              #; ebx = size                             
        shl ebx, 2                                      #; ebx <<= 2; (multiply by sizeof(int))
        CALL_FUNCTION_ONE_PARAM malloc, ebx             #; calls malloc(ebx) -> return value is in eax
        cmp eax, 0                                      #; compare return value == nullptr
        jne 1f                                          #; if not equal jump to end of function
        push -1                                         #; pass the value to exit(-1)
        call exit                                       #; calls exit(-1)
1:      END_FUNCTION                                    #; ends function

#; void freeSpace(void *arr) {
#;     free(arr);
#; }
freeSpace:
        START_VOID_FUNCTION                             #; starts the function
        CALL_FUNCTION_ONE_PARAM free, [ebp + 8]         #; calls free(arr);
        END_VOID_FUNCTION                               #; ends function

#; eax -> arr, ebx -> len, ecx -> len
#; 
#; void fillArray(int *arr, int len) {
#;     while (len != 0) {
#;         len--;
#;         arr[len] = len + 1;
#;     }
#; }
fillArray:
        START_VOID_FUNCTION             #; start the function
        mov eax, [ebp + 8]              #; eax = arr
        mov ebx, [ebp + 12]             #; ebx = len
        mov ecx, ebx                    #; ecx = len
1:      cmp ebx, 0                      #; loop start: compare ebx != 0
        je 1f                           #; if == 0 break out of loop
        dec ebx                         #; ebx--
        mov [eax + 4 * ebx], ecx        #; eax[ebx] = ecx
        dec ecx                         #; ecx--
        jmp 1b                          #; jump to start of loop
1:      END_VOID_FUNCTION               #; end the function

#; void loadInt(int *address) {
#;     scanf("%d", address);
#; }
loadInt:
        START_VOID_FUNCTION                             #; start the function
        mov eax, offset scanf_format                    #; eax = "%d";
        CALL_FUNCTION_TWO_PARAMS scanf, eax, [ebp + 8]  #; call scanf(eax, address);
        END_VOID_FUNCTION                               #; end function

#; void printString(char *str) {
#;     printf(str);
#; }
printString:
        START_VOID_FUNCTION                             #; start the function
        CALL_FUNCTION_ONE_PARAM printf, [ebp + 8]       #; call printf(str)
        END_VOID_FUNCTION                               #; end function

#; void printStringWithParam(char *str, int param) {
#;     printf(str, param);
#; }
printStringWithParam:
        START_VOID_FUNCTION                                     #; start the function
        CALL_FUNCTION_TWO_PARAMS printf, [ebp + 8], [ebp + 12]  #; call printf(str, param)
        END_VOID_FUNCTION                                       #; end function

#; int findInArrayWrapper(int *arr, int len, int num) {
#;     findInArray(arr, len, num);
#; }
findInArrayWrapper:
        START_FUNCTION                                                                  #; start the function
        CALL_FUNCTION_THREE_PARAMS findInArray, [ebp + 8], [ebp + 12], [ebp + 16]       #; call findInArray(arr, len, num);
        END_FUNCTION                                                                    #; end function

.globl main
#; int main() {
#;     int len, num;
#;     printString("Input number of elements: ");
#;     loadInt(&len);
#;     int *arr = allocateSpace(len);
#;     fillArray(arr, len);
#;     printString("Input number to search for: ");
#;     loadInt(&num);
#;     int index = findInArray(arr, len, num);
#;     if (index != -1) {
#;         printStringWithParam("Index of found number is %d\n", index);
#;     }
#;     else {
#;         printString("Number not found in array\n")
#;     }
#;
#;     freeSpace(arr);
#;     return 0;
#; }
main:
        enter 4, 0                                                      #; reserve one local variable
        mov eax, offset printf_format_number_of_elements                #; eax = "..."
        CALL_FUNCTION_ONE_PARAM printString, eax                        #; call printString(eax);
        lea eax, [ebp - 4]                                              #; eax = &local_var;
        CALL_FUNCTION_ONE_PARAM loadInt, eax                            #; call loadInt(eax);
        mov ebx, [ebp - 4]                                              #; ebx = local_var;
        CALL_FUNCTION_ONE_PARAM allocateSpace, ebx                      #; call allocateSpace(ebx);
        mov ecx, eax                                                    #; ecx = eax;
        CALL_FUNCTION_TWO_PARAMS fillArray, ecx, ebx                    #; call fillArray(ecx, ebx);
        mov eax, offset printf_format_number_to_search_for              #; eax = "...";
        CALL_FUNCTION_ONE_PARAM printString, eax                        #; call printf(eax);
        lea eax, [ebp - 4]                                              #; eax = &local_var
        CALL_FUNCTION_ONE_PARAM loadInt, eax                            #; call loadInt(eax);
        mov edx, [ebp - 4]                                              #; edx = local_var;
        CALL_FUNCTION_THREE_PARAMS findInArrayWrapper, ecx, ebx, edx    #; call findInArray(ecx, ebx, edx);
        cmp eax, -1                                                     #; compare eax == -1
        je 1f                                                           #; if equal jump to that case
        mov edx, offset printf_format_result                            #; edx = "...";
        CALL_FUNCTION_TWO_PARAMS printStringWithParam, edx, eax         #; print index of found number
        jmp 2f                                                          #; jump to end of function         
1:      mov eax, offset printf_format_unsuccessful                      #; eax = "...";
        CALL_FUNCTION_ONE_PARAM printString, eax                        #; print that number is not found  
2:      CALL_FUNCTION_ONE_PARAM freeSpace, ecx                          #; call freeSpace(ecx)      
        leave                                                           #; clear space reserved for local_var
        mov eax, 0                                                      #; main return value
        ret                                                             #; return from main
