Byte* getDiskBlock (BlkNo blk) {
    int hash = blk%CACHESIZE;

    if (diskCacheMap[hash]==blk)
        return diskCache[hash];

    if (diskCacheMap[hash]!=0)
        diskWrite(diskCacheMap[hash],diskCache[hash]);

    diskCacheMap[hash] = blk;
    diskRead(blk,diskCache[hash]);
    return diskCache[hash];
}
