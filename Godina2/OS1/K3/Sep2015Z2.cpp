int fgetsize (int fhandle, unsigned long& size);
int fresize (int fhandle, unsigned long newsize);
int fmoveto (int fhandle, unsigned long offset);
int fwrite (int fhandle, byte* buffer, unsigned long size);

int append (int fhandle, byte* buffer, unsigned long size){
    int fsize;
    int code;
    code=fgetsize(fhandle, fsize);
    if(code<0)return code;

    code=fresize(fhandle, fsize+size);
    if(code<0)return code;

    code=fmoveto(fhandle, size);
    if(code<0)return code;

    code=fwrite(fhandle, buffer, size);
    if(code<0)return code;

    return 0;
}