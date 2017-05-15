/*Neki sistem koristi preklope(overlays).Prevodilac i linker u generisanom kodu prevedenog
programa koji koristi preklope staticki alociraju i adekvatno inicijalizuju sledece strukture
podataka :
- za svaki modul(preklop, overlay) postoji sledeci deskriptor; moduli koji se preklapaju
imaju istu pocetnu adresu :
struct OverlayDescr {
	const char* filename; // Naziv fajla u kome je binarni sadrzaj preklopa
	void* addr; // Adresa u adresnom prostoru procesa na kojoj se nalazi
	bool isLoaded; // Da li je preklop trenutno ucitan?
}
- tabela svih preklopa - modula :
const int numOfOverlays = ...; // Ukupan broj preklopa
OverlayDescr overlays[numOfOverlays]; // Tabela svih preklopa
- svakom potprogramu koji se nalazi u nekom preklopu prevodilac pridružuje jedan
jedinstveni ceo broj(identifikator), koji predstavlja ulaz u tabelu tih potprograma;
svaki ulaz u ovoj tabeli sadrzi pokazivac na deskriptor preklopa u kome se nalazi taj
potprogram :
const int numOfProcs = ...; // Ukupan broj potprograma
OverlayDescr* procedureMap[numOfProcs]; // Tabela potprograma
Za svaki poziv potprograma koji se nalazi u nekom preklopu, na uvek istoj i prevodiocu
poznatoj adresi u adresnom prostoru procesa, npr.proc(a, b, c), prevodilac generiše kod koji
je ekvivalent sledeceg koda :
ensureOverlay(proc_id); // proc_id je identifikator za proc
proc(a, b, c); // standardan poziv na poznatoj adresi
Funkcija ensureOverlay(int procID) treba da obezbedi da je potprogram sa datim
identifikatorom prisutan u memoriji, odnosno po potrebi ucita njegov preklop.Potrebno je
implementirati ovu funkciju, pri cemu je na raspolaganju sistemski poziv koji ucitava binarni
sadrzaj iz fajla sa zadatim imenom na zadatu adresu u adresnom prostoru procesa :
void sys_loadBinary(const char* filename, void* address);*/

/**
 * \brief Loads the overlay from file to the address
 * \param filename Name of the file
 * \param address Address of overlay
 */
void sys_loadBinary(const char* filename, void* address);

/**
 * \brief Struct representing the overlay descriptor
 */
struct OverlayDescr{
    const char* filename; /**< File where overlay is */
    void* addr; /**< Address in memory where overlay is */
    bool isLoaded; /**< Whether the overlay is loaded */
};

const int numOfOverlays=100; /**< Number of overlays */
OverlayDescr overlays[numOfOverlays]; /**< Array of descriptors */

const int numOfProcs=50; /**< Number of procedures */
OverlayDescr* procedureMap[numOfProcs]; /**< Array of procedures */

/**
 * \brief Ensures overlay is loaded
 * \param proc_id Index of the procedure
 */
void ensureOverlay(int proc_id){
    OverlayDescr* overlay=procedureMap[proc_id];
    if(!overlay->isLoaded){
        sys_loadBinary(overlay->filename, overlay->adress);

        for(int i=0; i<numOfOverlays; i++)
            if(overlay->addr==overlays[i].addr)
                overlays[i].isLoaded=false;

        overlay->isLoaded=true;
    }
}