; startup.asm

; Izvozenje simbola:
public proceduraKopiraj
public __PIA

; Uvozenje simbola:
; Identifikatori glavnaFunkcija i prekidnaRutina su definisani u fajlu "program.c".
; Donja crta ispred simbola koji se uvoze u fajl "startup.asm" (_glavnaFunkcija i _prekidnaRutina)
; mora da se doda zbog konvencije imenovanja (naming convention) koju koristi Watcom C Compiler.
extern _glavnaFunkcija: far ptr
extern _prekidnaRutina: far ptr

RAM_SIZE_IN_PAR equ 0x1000    			;velicina RAM memorije (64KB) izrazena u paragrafima (16B); 64K/16 = 2^(6+10)/2^4 = 2^12 = 0x1000

; Citavu IVT treba popuniti adresom samo jedne prekidne rutine (ovo nije standardan pristup - objasnjenje zasto mora tako dato je u fajlu "program.c").
; Posto RAM gubi sadrzaj po nestanku napajanja (volatile), pocetni sadrzaj IVT-a mora biti smesten u ROM (non-volatile) u segment ivtRom,
; zbog cega se na pocetku u okviru inicijalizacije sistema mora izvrsiti kopiranje sadrzaja segmenta ivtRom u segment ivtRam.
; Segment koji ce biti smesten na adresu 0x00000 (tabela prekidnih rutina) - tacnije klasa segmenata 'IVTRAM' bice smestena na adresu 0x00000
ivtRam segment 'IVTRAM'
dd 256 dup (_prekidnaRutina)
ivtRam ends

; Segment koji ce biti smesten na adresu 0xFFFF0 (izvrsavanje instrukcija pocinje od ove adrese) - tacnije klasa segmenata 'STARTUP' bice smestena na adresu 0xFFFF0
startup segment 'STARTUP'
labela:	jmp far ptr pocetak
dopuna:	db (16 - (dopuna - labela)) dup (0) ; segment dopunjen nulama tako da velicina segmenta bude 16B
startup ends

makroKopiraj macro destPocetak, srcPocetak, srcKraj
			mov DX, srcKraj				; srcKraj mora da bude segmentni deo adrese segmenta koji se nalazi odmah posle izvorisnog segmenta
			mov BX, srcPocetak			; srcPocetak mora da bude segmentni deo adrese segmenta koji predstavlja izvorisni segment
			sub DX, BX					; razlika ove dve adrese (srcKraj - srcPocetak) predstavlja velicinu podataka koje treba kopirati izrazenu u paragrafima (16B)
			mov CL, 3					; velicina podataka u bajtovima dobija se tako sto se velicina u paragrafima pomnozi sa 16 ((srcKraj - srcPocetak) * 16)
			shl DX, CL					; velicina podataka u recima dobija se tako sto se velicina u paragrafima pomnozi sa 8 ((srcKraj - srcPocetak) * 8)

			mov AX, destPocetak
			mov BX, srcPocetak
			mov CX, 0

			push AX						; push destPocetak	(segmentni deo adrese odredisnog segmenta)
			push CX						; push 0			(ofsetni deo adrese je jednak nuli jer se sadrzaj segmenta kopira pocev od pocetka segmenta)
			push BX						; push srcPocetak	(segmentni deo adrese izvorisnog segmenta)
			push CX						; push 0			(ofsetni deo adrese je jednak nuli jer se sadrzaj segmenta kopira pocev od pocetka segmenta)
			push DX						; push wordNum		(velicina podataka u recima ((srcKraj - srcPocetak) << (2^3)))
			
			call proceduraKopiraj
			add SP, 0x0A
endm

text segment 'CODE'
			;inicijalizacija steka
pocetak:	mov AX, stackStart			; stackStart je prazan segment koji ce biti mapiran odmah nakon segmenata sa podacima. Stoga, stackStart predstavlja adresu
			mov SS, AX					; tj. segmentni deo adrese do koje stek sme da se napuni (stek raste ka nizim adresama). Zato upisujemo stackStart u SS.
										
			mov BX, RAM_SIZE_IN_PAR		; Imenovana konstanta RAM_SIZE_IN_PAR predstavlja velicinu RAM memorije izrazenu u paragrafima (16B), koju koristimo da bismo
			cmp BX, AX					; utvrdili da li u RAM memoriju mogu da se smeste svi podaci.
maliRam: 	jbe maliRam					; Ako podaci ne mogu da se smeste u RAM memoriju, ova instrukcija uslovnog skoka predstavlja beskonacnu petlju.

			sub BX, AX					; Velicina slobodnog dela RAM memorije (BX = RAM_SIZE_IN_PAR - stackStart) koji se koristi za stek, izrazena je u paragrafima (16B),
										; dok se ofset (SP) izrazava u bajtovima. Zato bi velicinu slobodnog dela RAM memorije izrazenu u paragrafima trebalo pomnoziti sa 16.
			test BX, 0xF000				; Prvo treba proveriti da li bi velicina slobodnog dela RAM memorije izrazena u bajtovima mogla da se smesti u SP.
			jnz maxOffset				; Da li medju najvisih cetiri bita velicine slobodnog dela RAM memorije izrazene u paragrafima postoji jedinica?
			
			mov CL, 4					; Ako moze da se smesti u SP, upisujemo velicinu slobodnog dela RAM memorije izrazenu u paragrafima pomnozenu sa 16.
			shl BX, CL
			mov SP, BX
			jmp nastavak
			
maxOffset:	mov SP, 0xFFFE				; Ako ne moze da se smesti u SP, upisujemo maksimalni moguci ofset 0xFFFE.
			
nastavak:
			;kopiranje pocetnog sadrzaja IVT-a iz ROM u RAM
			makroKopiraj ivtRam, ivtRom, dataRom
			
			;kopiranje pocetnog sadrzaja klase segmenata 'DATA' iz ROM u RAM
			makroKopiraj dataRam, dataRom, dataRomEnd
			
			call _glavnaFunkcija		; prelazak u C programski kod gde se nastavlja sa inicijalizovanjem sistema
			
beskonacna:	jmp beskonacna

; Procedura za kopiranje sadrzaja
proceduraKopiraj proc near
			push BP						;	   HIGH |---------------|
			mov BP, SP					;			|    SEG dest   | +0x0C
										;			|---------------|
			push ES						;			|  OFFSET dest  | +0x0A
			push DI						;			|---------------|
			push DS						;			|    SEG src    | +0x08
			push SI						;			|---------------|
			push CX						;			|   OFFSET src  | +0x06
										;			|---------------|
			les DI, [BP + 0x0A]			;			|       n       | +0x04
			lds SI, [BP + 0x06]			;			|---------------|
			mov CX, [BP + 0x04]			;			|    ret IP     | +0x02
										;			|---------------|
			cld							;			|     oldBP     |<----BP
										;			|---------------|
			rep movsw					;			|               |
										;			|---------------|
			pop CX						;			|               |
			pop SI						;		LOW |---------------|
			pop DS
			pop DI
			pop ES

			mov SP, BP
			pop BP
			retn
proceduraKopiraj endp

; PointerIntegerAdd (procedura koju uvozi objektni fajl "program.obj" za pristup nizovima)
__PIA proc far
			add AX, BX
			retf
__PIA endp

text ends

; Segment koji se koristi za dohvatanje pocetne adrese segmenata klase 'DATA' u RAM
dataRam segment 'DATARAM'
	; Prazan segment
dataRam ends

; Segment u koji ce biti emitovan pocetni sadrzaj IVT
ivtRom segment 'IVTROM'
	; Linker ce emitovati sadrzaj u ovaj segment
ivtRom ends

; Segment u koji ce biti emitovan pocetni sadrzaj segmenata klase 'DATA'
dataRom segment 'DATAROM'
	; Linker ce emitovati sadrzaj u ovaj segment
dataRom ends

; Segment koji se koristi za izracunavanje velicine prethodnog segmenta
dataRomEnd segment 'DATAROMEND'
	; Prazan segment
dataRomEnd ends

; Segment koji se koristi za dohvatanje adrese prvog slobodnog segmenta (donja adresa za stek)
stackStart segment 'STACKSTART'
	; Prazan segment
stackStart ends

end
