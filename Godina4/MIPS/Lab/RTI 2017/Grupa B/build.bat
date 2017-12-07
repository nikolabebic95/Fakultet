@rem build.bat

@rem REM command stands for remark (comment).
@rem The @ symbol tells the command processor to be less verbose (only show the output of the command).
@rem When @ symbol is used it is prepended to the beginning of the command and it is not necessary to leave a space between the "@" and the command.

@rem Cleaning.
@rem DEL command deletes the file.
del *.obj
del *.bin

@rem CLS command clears the video display screen, setting the cursor in the upper left-hand corner.
cls

@rem WASM - Watcom ASseMbler
@rem Usage: wasm [options] asm_file
@rem Compiling assembler part.
@rem 0:     8086 instructions.
@rem d0:    No debugging information.
@rem mh:    The "huge" memory model is selected.
@rem wx:    Set the warning level to its maximum setting.

wasm -0 -d0 -mh -wx startup.asm

@rem WCC - Watcom C Compiler
@rem Usage: wcc [options] file
@rem Compiling C part.
@rem 0:     8088 and 8086 instructions.
@rem mh:    The "huge" memory model (large code, huge data) is selected.
@rem na:	Disable automatic inclusion of "_ialias.h"
@rem ecc:	Set default calling convention to __cdecl
@rem d0:    No debugging information.
@rem od:    Turn off all optimizations.
@rem s:     Remove stack overflow checks.
@rem zl:    Suppress generation of library file names and references in object file.
@rem zld:   Remove file dependency information.
@rem zu:	SS != DGROUP (i.e., don't assume stack is in your data segment).
@rem zdf:	DS floats i.e. not fixed to DGROUP.

wcc -0 -mh -na -ecc -d0 -od -s -zl -zld -zu -zdf program.c

@rem lnks - linker
@rem -f <naziv_fajla> Ukljucuje objektni fajl u linkovanje
@rem -s <naziv_klase> [<zeljena_pocetna_segmentna_adresa>] [NOE|COPY <naziv_klase_iz_koje_se_uzima_sadrzaj>]
lnks -f startup.obj -f program.obj -s IVTRAM 0x0000 NOE -s DATARAM -s NOE -s DATA NOE -s BSS -s STACK NOE -s CODE 0xf800 -s IVTROM COPY IVTRAM -s DATAROM COPY DATA -s STARTUP 0xffff >linker_output.txt
