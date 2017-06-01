#; Napisati potprogram na x86 asembleru koji prihvata niz brojeva, broj elemenata i vrednost koju je potrebno
#; pronaci u prosledjenom nizu, redom kojim su navedeni. Potprogram vraca indeks poslednjeg pojavljivanja zadatog
#; elementa. Potprogram koristi cdecl konvenciju pozivanja potprograma.

.intel_syntax noprefix
.arch i386

.data

.text

#;
#; ret -> eax ; arr -> ebx ; len -> ecx ; num -> edx
#;
#; int findInArray(int *arr, int len, int num) {
#;     ret = -1;
#;     while (len != 0) {
#;         if (arr[len] == num) {
#;             ret = len;
#;             break;
#;         }
#;     }
#;
#;     return ret;
#; }
#;
.globl findInArray
findInArray:
                enter 0, 0                      #; function start, no local variables
                push ebx                        #; save ebx (function must preserve the value of ebx)
                mov ebx, [ebp + 8]              #; ebx = arr;
                mov ecx, [ebp + 12]             #; ecx = len;
                mov edx, [ebp + 16]             #; edx = num; 
                mov eax, -1                     #; eax = -1; (nothing found)
1:              cmp ecx, 0                      #; while (ecx != 0) do
                je 1f                           #; if condition not met jump out of loop
                dec ecx                         #; ecx--;
                cmp [ebx + 4 * ecx], edx        #; compare (arr[ecx] == edx)
                jne 1b                          #; if condition not met continue to next iteration
                mov eax, ecx                    #; eax = ecx;
                pop ebx                         #; restore the value of ebx
1:              leave                           #; prepare for return
                ret                             #; return eax
