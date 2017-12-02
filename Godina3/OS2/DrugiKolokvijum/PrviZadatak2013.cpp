// Zadatak 1, 2013

const unsigned MAXPROC = ...; // Maximum number of processes
const unsigned MAXRES = ...; // Maximum number of resources
extern unsigned numOfProc; // Actual number of processes
extern unsigned numOfRes; // Actual number of resources
int resourceAlloc[MAXPROC][MAXRES];
int allocate (unsigned pid, unsigned rid);
int release (unsigned pid, unsigned rid);

int findWhoHolds(unsigned rid){
	int i;
	for(i=0; i<numOfProc; i++)
		if(resourceAlloc[i][rid] == -1)
			return i;

	return -1;
}

int findWhatWants(unsigned pid){
	int i;
	for(i=0; i<numOfRes; i++)
		if(resourceAlloc[pid][i] == 1)
			return i;

	return -1;
}

int wouldMakeDeadlock(unsigned pid, unsigned rid){
	if(pid<0 || pid>=numOfProc || rid<0 || rid>=numOfRes) return -1;

	int p, r;
	r=rid;
	while (true){
		p=findWhoHolds(r);
		if (p == -1) return 0;
		if (p == pid) return 1;
		r=findWhatWants(p);
		if (r == -1) return 0;
	}
}