/*Data je jedna realizacija klase DLArray koja apstrahuje dinamicki niz elemenata tipa double
velike dimenzije zadate prilikom inicijalizacije parametrom size.U toj implementaciji, u
svakom trenutku se u memoriji drzi samo jedan kesirani blok ovog niza velicine zadate
parametrom blockSize.Implementacija koristi dinamicko ucitavanje bloka u kome se nalazi
element kome se pristupa uz zamenu(swapping), zapravo neku vrstu preklopa(overlay), tako
da se u memoriji uvek nalazi samo jedan kesirani blok kome se trenutno pristupa, dok se ceo
niz nalazi u fajlu.Interfejs te klase je u njenom javnom delu.
U funkcijama fread i fwrite za pristup fajlu i ucitavanje, odnosno snimanje datog niza
elemenata tipa double na zadatu poziciju u fajlu, pozicija se izrazava u jedinicama velicine
binarnog zapisa tipa double, pocev od 0, sto znaci da se fajl kroz ove funkcije može
posmatrati kao veliki niz elemenata tipa double:
void fread(FHANDLE, int position, double* buffer, int bufferSize);
void fwrite(FHANDLE, int position, double* buffer, int bufferSize);
Modifikovati datu implementaciju ove klase(bez modifikacije njenog interfejsa) tako da se u
memoriji nalaze uvek dva bloka iz niza u dva slota(umesto u jednom, kako je sada), pri cemu
se u jedan slot preslikavaju parni, a u drugi neparni blokovi niza.
class DLArray {
public:
	inline DLArray(int size, int blockSize, FHANDLE fromFile);
	inline double get(int i); // Get element [i]
	inline void set(int i, double x); // Set element [i]
protected:
	inline void save();
	inline void load(int blockNo);
	inline void fetch(int blockNo);
private:
	FHANDLE file;
	int size, blockSize;
	int curBlock;
	int dirty;
	double* block;
};
DLArray::DLArray(int s, int bs, FHANDLE f) :
file(f), size(s), blockSize(bs), curBlock(0), dirty(0) {
	block = new double[bs];
	if (block) load(curBlock);
}
void DLArray::save() {
	fwrite(file, curBlock*blockSize, block, blockSize);
	dirty = 0;
}
void DLArray::load(int b) {
	curBlock = b;
	fread(file, curBlock*blockSize, block, blockSize);
	dirty = 0;
}
5 / 6
void DLArray::fetch(int b) {
	if (curBlock != b) {
		if (dirty) save();
		load(b);
	}
}
double DLArray::get(int i) {
	if (block == 0 || i<0 || i >= size) return 0; // Exception
	fetch(i / blockSize);
	return block[i%blockSize];
}
void DLArray::set(int i, double x) {
	if (block == 0 || i<0 || i >= size) return; // Exception
	fetch(i / blockSize);
	if (block[i%blockSize] != x) {
		block[i%blockSize] = x;
		dirty = 1;
	}
}*/

typedef int FHANDLE; /**< File handle */

/**
 * \brief Reads a block of doubles from file
 * \param file Handle to a file where the array is stored
 * \param position Start position of the read
 * \param buff Buffer where the elements are read
 * \param bufferSize Size of the buffer in bytes
 */
void fread(FHANDLE file, int position, double[] buff, int bufferSize);

/**
 * \brief Writes a block of doubles to file
 * \param file Handle to a file where the array is stored
 * \param position Start position of the write
 * \param buff Buffer from where the elements are read
 * \param bufferSize Size of the buffer in bytes
 */
void fwrite(FHANDLE file, int position, double[] buff, int bufferSize);

/**
 * \brief Class implementing a big double array using overlays
 */
class DLArray{
public:
    DLArray (int size, int blockSize, FHANDLE fromFile): 
    size_(size), block_size_(blockSize), from_file_(fromFile){
        double_array_=new int [block_size_];
    }

    ~DLArray(){
        ensureSaved();
        delete [] double_array_;
    }

    double get(int i){
        ensureLoaded(i);
        return double_array_[i%block_size_];
    }

    void set(int i, double x){
        ensureLoaded(i);
        double_array_[i%block_size_]=x;
        dirty_=true;
    }

private:
    int size_, block_size_, block_=-1; 
    double *double_array_;
    FHANDLE from_file_;
    bool dirty_=false;

    void ensureSaved(){
        if(dirty_){
            fwrite(from_file_, block_*block_size_, double_array_, block_size_);
            dirty_=false;
        }
    }

    void ensureLoaded(int i){
        if(block_!=i/block_size_){
            ensureSaved();
            fread(from_file_, block_*block_size_, double_array_, block_size_);
            block_=i/block_size_;
        }
    }
};
