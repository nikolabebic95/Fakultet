void client(){
    int ticket;
    int response;
    while(true){
        in("ticket", ?ticket);
        out("ticket", ticket + 1);
        int requestType = ...;
        out("request", ticket, requestType);
        in("response", ticket, ?response);
        // do smth with response
    }
}

void server(){
    int requestType;
    int counter = 0;
    int ticket;

    while(true){
        in("next", ?ticket);
        out("next", ticket + 1);
        in("request", ticket, ?requestType);
        int response = execute(requestType);
        out("response", ticket, response);
        counter++;

        bool sum = rdp("sum");
        if(sum){
            out("report", counter);
            counter = 0;
            rd("continue");
            out("released");
        }
    }   
}

void summator(){
    int numServers;
    int sum = 0;
    in("numOfServers", ?numServers);
    while(true){
        out("sum");
        for(int i = 0; i < numOfServers; i++){
            int n;
            in("report", ?n);
            sum += n;
        }
        // do smth with sum

        in("sum");
        out("continue");
        for(int i = 0; i < N; i++)
            in("released");
        in("continue");
        sleep(SLEEP_TIME);
    }
}

int main(){
    const int N = ...;
    out("ticket", 1);
    out("numOfServers", N);

    for(int i = 0; i < N; i++)
        eval(server());

    for(int i = 0; i < M; i++)
        eval(client());

    eval(summator());
}