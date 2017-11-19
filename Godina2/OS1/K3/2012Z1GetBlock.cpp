Byte* getDiskBlock (BlkNo blk) {
    int base=blk%CACHESIZE;
    int cursor=base;

    for (int i=0; i<CACHESIZE; i++) {
        cursor=(base+i)%CACHESIZE;
        if (diskCacheMap[cursor]==blk) return diskCache[cursor];
        if (diskCacheMap[cursor]==0) break;
    }

    if (diskCacheMap[cursor]!=0){
        cursor=base;
        diskWrite(diskCacheMap[cursor],diskCache[cursor]);
    }

    diskCacheMap[cursor] = blk;
    diskRead(blk,diskCache[cursor]);
    return diskCache[cursor];
}
