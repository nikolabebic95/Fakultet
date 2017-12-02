// Zadatak 1, Nadoknada 2014

int ResourceAllocator::request (int p, ResourceVector req){
    if(p<0 || p>=np)
        return -1;
    if(alloc[p] + req > max[p])
        return -2;
    if(req > free)
        return -3;
    
    alloc[p]+=req;
    free-=req;
    if(isSafeState())
        return 0;
    else{
        alloc[p]-=req;
        free+=req;
        return -4;
    }
}
