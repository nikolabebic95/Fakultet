// Zadatak 2, 2012

const unsigned MAXPROC = ...; // Maximum number of processes
const unsigned MAXRES = ...; // Maximum number of resources
extern unsigned numOfProc; // Actual number of processes
extern unsigned numOfRes; // Actual number of resources
int resourceAlloc[MAXPROC][MAXRES];
int getHolder(int rid){
	for(int i=0; i<numOfProc; i++)
		if(resourceAlloc[i][rid] == -1)
			return i;
	return -1;
}

int getWaiter(unsigned rid){
	for(int i=0; i<numOfProc; i++)
		if(resourceAlloc[i][rid] == 1)
			return i;
	return -1;
}
int allocate (unsigned pid, unsigned rid){
	if(pid<0 || pid>=numOfProc || rid<0 || rid>=numOfRes) return -1;
	if(resourceAlloc[pid][rid] == -1) return 1;
	
	if(getHolder(rid) == -1){
		resourceAlloc[pid][rid] == -1;
		return 1;
	}
	else{
		resourceAlloc[pid][rid] = 1;
		return 0;
	}
}
int release (unsigned pid, unsigned rid){
	if(pid<0 || pid>=numOfProc || rid<0 || rid>=numOfRes) return -1;
	
	resourceAlloc[pid][rid] == 0;
	int waiter=getWaiter(rid);

	if(waiter == -1){
		return -1;
	}
	else{
		resourceAlloc[waiter][rid] == -1;
		return waiter;
	}

}