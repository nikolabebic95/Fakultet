const int NUM_PROCESS = 5;

struct msgbuf{
    long mtype;
};

void barrier(int id, int msg_box){
    for(int i = 0; i < NUM_PROCESS; i++){
        if(i != id){
            msgbuf newMess;
            newMess.mtype = i + 1;
            msgsnd(msg_box, &newMess, 0, 0);
        }
    }

    msgbuf rec;
    for(int i = 0; i < NUM_PROCESS - 1; i++)
        msgrcv(msg_box, &rec, 0, id + 1, 0);
}
