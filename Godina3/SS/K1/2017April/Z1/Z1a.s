#; Na x86 asembleru napisati potprogram za obradu niza brojeva ciji je potpis void rotateLeft(int arr[], int n, int x).
#; Pri implementaciji koristiti stdcall konvenciju pozivanja potprograma. Potprogram treba da zarotira sadrzaj niza tako
#; sto sve elemente pomeri za x pozicija u levo, pri cemu se racuna po modulu n. Primer, za x=2 i niz 0 1 2 3 4 5 treba
#; dobiti 2 3 4 5 0 1

.intel_syntax noprefix
.arch i386

.data

.text

#; eax -> arr, ebx -> n, ecx -> front, edx -> temp
#;
#; void reverse(int arr[], int n) {
#;     int front = 0;
#;     n--;
#;     while (front < n) {
#;         swap(arr[front], arr[n]) // Swap using pushing and popping from stack
#;         front++;
#;         n--;
#;     }
#; }
reverse:
        enter 0, 0              #; enter the function
        push ebx                #; save ebx (function must preserve the value of ebx)
        mov eax, [ebp + 8]      #; eax = arr
        mov ebx, [ebp + 12]     #; ebx = n
        mov ecx, 0              #; ecx = 0 (front)
        dec ebx                 #; ebx-- (n--)
1:      cmp ecx, ebx            #; loop while (ecx < ebx) do
        jge 1f                  #; if condition not met, jump out of loop
        push [eax + 4 * ecx]    #; push arr[front]
        push [eax + 4 * ebx]    #; push arr[n]
        pop [eax + 4 * ecx]     #; pop into arr[front]
        pop [eax + 4 * ebx]     #; pop into arr[n]
        inc ecx                 #; ecx++ (front++)
        dec ebx                 #; ebx-- (n--)
        jmp 1b                  #; jump to beggining of loop
1:      pop ebx                 #; restore ebx
        leave                   #; prepare for return from function
        ret 8                   #; return and pop parameters (stdcall)


#; void rotateLeft(int arr[], int n, int x) {
#;     reverse(arr, n);
#;     reverse(arr, n - x);
#;     reverse(arr + n - x, x)
#; }
#;
.globl rotateLeft
rotateLeft:
        enter 0, 0                      #; enter the function
        push [ebp + 12]                 #; push second argument (n)
        push [ebp + 8]                  #; push first argument (arr)
        call reverse                    #; call reverse(arr, n)
        mov eax, [ebp + 12]             #; eax = n
        sub eax, [ebp + 16]             #; eax -= x (eax becomes n - x)
        push eax                        #; push second argument (n - x)
        push [ebp + 8]                  #; push first argument (arr)
        call reverse                    #; call reverse(arr, n - x)
        mov eax, [ebp + 12]             #; eax = n
        sub eax, [ebp + 16]             #; eax -= x (eax becomes n - x)
        shl eax, 2                      #; eax *= 4 (eax becomes (n - x) * sizeof(int))
        add eax, [ebp + 8]              #; eax += arr (eax becomes arr + n - x (pointer arithmetic))
        push [ebp + 16]                 #; push second argument (x)
        push eax                        #; push first argument (arr + n - x)
        call reverse                    #; call reverse(arr + n - x, x)
        leave                           #; prepare for return from function
        ret 12                          #; return and pop parameters (stdcall)
