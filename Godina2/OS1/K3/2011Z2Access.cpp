int check_access(PCB* p, FHANDLE f, int write){
    int access=p->open_files[f].access;
    if(write)
        return access;
    else{
        return 1;
    }
}