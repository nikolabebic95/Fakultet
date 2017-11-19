// blokovski uredjaj, direktan pristup
extern const int BlockSize; // velicina bloka
extern int BlockIOHandle; // id uredjaja
long getSize(BlockIOHandle handle); // velicinu sadrzaja datog uredjaja
int readBlock(BlockIOHandle handle, long blockNo, char* addr);
// ucitava zadati blok(blockNo) na zadatu memorijsku lokaciju

// napraviti od njega znakovni uredjaj

class IOStream{
public:
    IOStream(BlockIOHandle d);
    int seek (long offset);
    int getChar(char& c);
private:
    BlockIOHandle device_id;
    long cursor;

    long curr_block;
    char block[BlockSize];

    long size;
    long num_of_blocks;
}

IOStream::IOStream(BlockIOHandle d): device_id(d){
    size=getSize(device_id);
    if(size<0){
        device_id=0;
        return size;
    }
    
    cursor=size;
}

int IOStream::seek(long offset){
    if(device_id==0 || offset<0 || offset>=size)
        return -1;
    
    cursor=offset;
    if(cursor/BlockSize!=curr_block){
        curr_block=cursor/BlockSize;
        int code=readBlock(device_id, curr_block, block);
        if(code<0)
            return code;
    }
    
    return 0;
}

int IOStream::getChar(char& c){
    int code=seek(cursor);
    if(code<0)
        return code;
    else{
        c=block[cursor%BlockSize];
        cursor++;
        return 0;
    }
}