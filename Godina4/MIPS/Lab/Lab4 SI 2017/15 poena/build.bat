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
@rem Linking object files.
@rem Objasnjenje sledece linije:
@rem -f startup.obj -f program.obj          - fajlovi koje treba ukljuciti u povezivanje.
@rem
@rem -s IVTRAM 0x0000 NOE                   - klasa segmenata 'IVTRAM' (ova klasa segmenata obuhvata samo segment ivtRam) se mapira na adresu 0x00000.
@rem                                          Opcija NOE (NO Emitting) je naznaka linkeru da sadrzaj klase segmenata 'IVTRAM' ne treba emitovati na adresu
@rem                                          na koju se klasa mapira. Razlog tome jeste to sto se klasa segmenata 'IVTRAM' mapira u opseg RAM memorije (RAM memorija
@rem                                          je volatile tj. ne cuva sadrzaj nakon gubitka napajanja), zbog cega nema smisla vrsiti emitovanje. Pocetni sadrzaj
@rem										  ove klase segmenata bice emitovan u oblast ROM memorije kao rezultat jedne od narednih opcija).
@rem
@rem -s DATARAM NOE                         - klasa segmenata 'DATARAM' (ova klasa segmenata obuhvata samo prazan segment dataRam) se mapira odmah nakon segmenata
@rem                                          prethodno navedene klase (klasa 'IVTRAM'). Treba primetiti da ce klasa segmenata 'DATARAM' biti mapirana neposredno ispred 
@rem                                          segmenata klase 'DATA' (zato sto se narednom opcijom klasa segmenata 'DATA' mapira odmah nakon segmenata klase 'DATARAM').
@rem                                          Zbog toga i zato sto je segment dataRam klase 'DATARAM' prazan, adresa segmenta dataRam bice ista kao i adresa prvog
@rem                                          segmenta iz klase 'DATA'. Opcija NOE se koristi zato sto je klasa segmenata 'DATARAM' mapirana u opseg RAM memorije,
@rem                                          zbog cega nema smisla da se emituje (linker opciju NOE zahteva cak i za prazne segmente).
@rem
@rem -s DATA NOE                            - klasa segmenata 'DATA' (ova klasa segmenata mozda obuhvata veci broj segmenata) se mapira odmah nakon segmenata
@rem                                          prethodno navedene klase (klasa 'DATARAM'). Sadrzaj klase 'DATA' takodje ne treba emitovati na adresu na koju se klasa
@rem										  mapira (pocetni sadrzaj ove klase segmenata bice emitovan u oblast ROM memorije kao rezultat jedne od narednih opcija).
@rem
@rem -s BSS                                 - klasa segmenata 'BSS' se mapira odmah nakon segmenata prethodno navedene klase (klasa 'DATA'). Iako se klasa segmenata 'BSS'
@rem										  mapira u opseg RAM memorije, nema potrebe navesti opciju NOE zato sto segmenti klase 'BSS' svakako ne mogu da se emituju
@rem                                          jer po svojoj prirodi nemaju pocetni sadrzaj (to je iz ugla linkera razlicito od praznog segmenta).
@rem
@rem -s STACKSTART NOE                      - klasa segmenata 'STACKSTART' (ova klasa segmenata obuhvata samo prazan segment stackStart) se mapira odmah nakon segmenata
@rem                                          prethodno navedene klase (klasa 'BSS'). Segment stackStart klase 'STACKSTART' se koristi samo da bi se dohvatila adresa
@rem                                          prvog slobodnog segmenta u RAM memoriji.
@rem									      U SS registar treba upisati adresu prvog slobodnog segmenta u RAM memoriji.
@rem                                          U SP registar treba upisati razliku izmedju velicine RAM memorije i adrese prvog slobodnog segmenta u RAM memoriji.
@rem
@rem -s CODE 0xF000                         - klasa segmenata 'CODE' se mapira pocev od adrese 0xF0000 (adresa pocetka ROM memorije uz pretpostavku da je velicina
@rem                                          ROM memorije 64KB), pritom tu treba i emitovati sadrzaj klase 'CODE' (sadrzaj ce biti emitovan jer nije navedena opcija NOE).
@rem
@rem -s IVTROM COPY IVTRAM                  - klasa segmenata 'IVTROM' (ova klasa segmenata obuhvata samo prazan segment ivtRom) se mapira odmah nakon segmenata
@rem 										  prethodno navedene klase (klasa 'CODE'). Zbog navodjenja opcije COPY moraju biti zadovoljena sledeca dva uslova:
@rem                                          		1. mora postojati tacno jedan segment klase 'IVTROM' (sme postojati samo u jednom od fajlova koji ucestvuju u linkovanju)
@rem                                          		2. taj jedan segment klase 'IVTROM' mora biti prazan
@rem                                          Segment ivtRom klase 'IVTROM' zadovoljava oba navedena uslova, tako da moze da se koristi za smestanje pocetnog sadrzaja
@rem                                          segmenta klase 'IVTRAM' (opcija COPY IVTRAM), zbog cega ce konacna velicina segmenta klase 'IVTROM' nakon linkovanja
@rem                                          biti ista kao i velicina segmenta klase 'IVTRAM' (sadrzaj klase 'IVTRAM' bice emitovan u klasu 'IVTROM').
@rem
@rem -s DATAROM COPY DATA                   - klasa segmenata 'DATAROM' (ova klasa segmenata obuhvata samo prazan segment dataRom) se mapira odmah nakon segmenata 
@rem                                          prethodno navedene klase (klasa 'IVTROM'). Zbog navodjenja opcije COPY moraju biti zadovoljena sledeca dva uslova:
@rem                                                1. mora postojati tacno jedan segment klase 'DATAROM' (sme postojati samo u jednom od fajlova koji ucestvuju u linkovanju)
@rem                                                2. taj jedan segment klase 'DATAROM' mora biti prazan
@rem                                          Segment dataRom klase 'DATAROM' zadovoljava oba navedena uslova, tako da moze da se koristi za smestanje pocetnog sadrzaja
@rem                                          segmenata klase 'DATA' (opcija COPY DATA), zbog cega ce konacna velicina segmenta klase 'DATAROM' nakon linkovanja
@rem                                          biti ista kao i velicina segmenata klase 'DATA' (sadrzaj klase 'DATA' bice emitovan u klasu 'DATAROM').
@rem
@rem -s DATAROMEND                          - klasa segmenata 'DATAROMEND' (ova klasa segmenata obuhvata samo prazan segment dataRomEnd) se mapira odmah nakon segmenata
@rem                                          prethodno navedene klase (klasa 'DATAROM'). Segment dataRomEnd klase 'DATAROMEND' se koristi samo da bi se dohvatila adresa
@rem 										  prvog slobodnog segmenta nakon klase 'DATAROM' (uz pomoc te adrese moze da se izracuna velicina segmenta klase 'DATAROM'
@rem                                          tj. ukupna velicina svih segmenata klase 'DATA').
@rem
@rem -s STARTUP 0xFFFF                      - klasa segmenata 'STARTUP' (ova klasa segmenata obuhvata samo segment startup) se mapira na adresu 0xFFFF0. Ova adresa
@rem                                          predstavlja adresu od koje pocinje izvrsavanje nakon resetovanja (ukljucivanja) sistema.

lnks.exe -f startup.obj -f program.obj -s IVTRAM 0x0000 NOE -s DATARAM NOE -s DATA NOE -s BSS -s STACKSTART NOE -s CODE 0xF000 -s IVTROM COPY IVTRAM -s DATAROM COPY DATA -s DATAROMEND -s STARTUP 0xFFFF >lnks_verbose.txt

@rem                                            |---------------|                        \
@rem                                            |   'STARTUP'   |                         |
@rem                                0xFFFF0---->|---------------|                         |
@rem                                            |       .       |                         |
@rem                                            |       .       |                         |
@rem                                            |       .       |                         |
@rem                                            |---------------|                         |
@rem                                            | 'DATAROMEND'  |                          \
@rem                          dataRomEnd*16---->|---------------|                           |  64K x 8b ROM Chip
@rem                                            |   'DATAROM'   | <---- COPY 'DATA'        /
@rem                             dataRom*16---->|---------------|                         |
@rem                                            |   'IVTROM'    | <---- COPY 'IVTRAM'     |
@rem                              ivtRom*16---->|---------------|                         |
@rem                                            |               |                         |
@rem                                            |    'CODE'     |                         |
@rem                                            |               |                         |
@rem                                0xF0000---->|---------------|                        /
@rem                                            |               |
@rem                                            |               |
@rem                                            |       .       |
@rem                                            |       .       |                        \
@rem                                            |       .       |                         |
@rem                                            |               |                         |
@rem                                            |               |                         |
@rem                                            |---------------|                         |
@rem                                            |  'STACKSTART' | <---- NOE               |
@rem                          stackStart*16---->|---------------|                         |
@rem                                            |     'BSS'     |                          \
@rem                                            |---------------|                           |  64K x 8b RAM Chip (VOLATILE)
@rem                                            |               |                          /
@rem                                            |    'DATA'     | <---- NOE               |
@rem                                            |               |                         |
@rem                                            |---------------|                         |
@rem                                            |   'DATARAM'   | <---- NOE               |
@rem                             dataRam*16---->|---------------|                         |
@rem                                            |   'IVTRAM'    | <---- NOE               |
@rem                                0x00000---->|---------------|                        /