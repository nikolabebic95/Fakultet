// Zadatak 1, 2012

const unsigned MAXPROC = ...; // Maximum number of processes
const unsigned MAXRES = ...; // Maximum number of resources
extern unsigned numOfProc; // Actual number of processes
extern unsigned numOfRes; // Actual number of resources
int resourceAlloc[MAXPROC][MAXRES];
int allocate (unsigned pid, unsigned rid){
    if(pid<0 || pid>=numOfProc || rid<0 || rid>= numOfRes) return -1;

    boolean holden;
    int i;

    for(i=0; i<numOfProc; i++)
        if(resourceAlloc[i][rid] == -1)
            break;
    
    if(i<numOfProc){
        resourceAlloc[pid][rid]=1;
        return 0;
    }
    else{
        resourceAlloc[pid][rid]=-1;
        return 1;
    }
}

int release (unsigned pid, unsigned rid){
    if(pid<0 || pid>=numOfProc || rid<0 || rid>= numOfRes) return -1;
    if(resourceAlloc[pid][rid] != -1)
        return -1;

    resourceAlloc[pid][rid]=0;
    int i;

    for(i=0; i<numOfProc; i++)
        if(resourceAlloc[i][rid] == 1)
            break;

    if(i<numOfProc){
        resourceAlloc[i][rid] == -1;
        return i;
    }
    else{
        return -1;
    }
}