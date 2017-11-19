int open (const char *pathname, int flags, mode_t mode);
int close (int fhandle);
int read (int fhandle, byte* buffer, unsigned long size);
int write (int fhandle, byte* buffer, unsigned long size);

class File {
public:
    File (const char *pathname, int flags, mode_t mode) throw Exception;
    ~File () throw Exception;
    void read (byte* buffer, unsigned long size) throw Exception;
    void write (byte* buffer, unsigned long size) throw Exception;
private:
    int fhandle=0;
}; 

File::File(const char *pathname, int flags, mode_t mode) throw Exception{
    int code;
    code=open (pathname, flags, mode);
    if(code<0)
        throw Exception(code);
    fhandle=code;
}

File::~File () throw Exception{
    int code;
    code=close(fhandle);
    if(code<0)
        throw Exception(code);
}

void File::read (byte* buffer, unsigned long size) throw Exception{
    int code;
    code=read(fhandle, buffer, size);
    if(code<0)
        throw Exception(code);
}

void File::write (byte* buffer, unsigned long size) throw Exception{
    int code;
    code=write(fhandle, buffer, size);
    if(code<0)
        throw Exception(code);
}