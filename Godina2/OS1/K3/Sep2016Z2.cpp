int fcopyreverse (const char *filenamefrom, const char *filenameto){
    FILE* file_from=fopen(filenamefrom, "r");
    if(file_from==0)
        return -1;
    FILE* file_to=fopen(filenameto, "w");
    if(file_to==0)
        return -1;

    int offset=-1;
    while(!fseek(file_from, offset--, SEEK_END)){
        int c=fgetc(file_from);
        if(c==EOF)
            return -1;
        int code=putc(c, file_to);
        if(code==EOF)
            return -1;
    }

    fclose(file_from);
    fclose(file_to);
    return 0;
}