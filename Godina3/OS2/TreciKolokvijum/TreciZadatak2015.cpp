#include <set>

#define M 6
#define N 3
#define MESSAGE_Q_KEY 1
struct requestMsg {
    long mtype; // msg type – street ID
    char msg[1]; // value not relevant
};

int main(){
    int requestMsgQueueId = msgget(MESSAGE_Q_KEY, IPC_CREAT | 0666);
    int responseMsgQueueId = msgget(MESSAGE_Q_KEY + 1, IPC_CREAT | 0666);
    size_t len = sizeof(char);
    std::set<int> received;
    int occupied = 0;

    requestMsg req;
    while(true){
        msgrcv(requestMsgQueueId, &req, len, 0);
        if(req.mtype == M + 1){
            occupied--;
            if(received.size() > 0){
                int id = *(received.begin());
                received.erase(id);
                occupied++;
                requestMsg res;
                res.mtype = id;
                msgsnd(responseMsgQueueId, &res, len, 0);
            }
        }
        else{
            if(occupied == N){
                received.insert(req.mtype);
            }
            else{
                occupied++;
                requestMsg res;
                res.mtype = req.mtype;
                msgsnd(responseMsgQueueId, &res, len, 0);
            }
        }
    }
}
