// Zadatak 1, Nadoknada 2013

class ResourceAllocator {
public:
 ResourceAllocator (int numOfProcesses, int numOfResources);
 int announce (int proc, int res);
 int request (int proc, int res); // 1 – acquired, 0 – cannot get it
 int release (int proc, int res);

protected:
 int hasCycle ();
private:
 int** alloc;
 int np, nr;
};

ResourceAllocator::ResourceAllocator (int p, int r) : np(p), nr(r) {
 if (np==0 || nr==0) return; // Exception
 alloc = new int*[np];
 for (int i = 0; i < np; i++) alloc[i] = new int[nr];
 if (alloc==0) return; // Exception
 for (int i=0; i<np; i++) {
 alloc[i] = new int[nr];
 if (alloc[i]==0) return; // Exception
 for (int j=0; j<nr; j++) alloc[i][j]=0;
 }
}

int ResourceAllocator::announce(int proc, int res){
    if(proc < 0 || proc >= np || res < 0 || res >= nr) return -1;
    if(alloc[proc][res] != 0) return 0;
    alloc[proc][res] = 1;
    return 1;
}

int ResourceAllocator::request (int proc, int res){
    if(proc < 0 || proc >= np || res < 0 || res >= nr) return -1;
    if(alloc[proc][res] == -1) return 1;
    if(alloc[proc][res] == 0) return 0;

    for(int i=0; i<np; i++)
        if(alloc[i][res] == -1){
            alloc[proc][res] = 2;
            return 0;
        }

    alloc[proc][res]=-1;
    if(hasCycle()){
        alloc[proc][res] = 2;
        return 0;
    }

    return 1;
}

int ResourceAllocator::release (int proc, int res){
    if(proc < 0 || proc >= np || res < 0 || res >= nr) return -1;
    if(alloc[proc][res] != -1)
        return 0;
    else{
        alloc[proc][res] = 1;
        return 1;
    }
}
