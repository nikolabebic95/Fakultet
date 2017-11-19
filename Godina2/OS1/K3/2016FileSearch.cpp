class Node;
Node* Node::getSubnode(const char* pStart, const char* pEnd);

Node* Node::getNode(PCB* pcb, const char* path){
    int start, end;
    Node* curr;

    if(path[0]=='/'){
        start=1;
        curr=rootNode;
    }
    else{
        start=0;
        curr=pcb->curDir;
    }
    end=start;
    while(path[end]!='/' && path[end]!='\0')
        end++;
    
    while(true){
        curr=curr.getSubnode(path+start, path+end);
        if(curr==0)
            return 0;
        if(path[end]=='\0')
            break;
        start=end++;
        while(path[end]!='/' && path[end]!='\0')
            end++;
    }
    return curr;
}