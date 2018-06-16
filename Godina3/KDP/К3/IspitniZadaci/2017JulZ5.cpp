void terminal(int konc, int term){
    int message = ...;
    while(true){
        out("terminalOut", term, konc, message);
        in("terminalIn", term, ?message);
        // do smth with message
    }
}

void koncetrator(int konc, int [] term, int size){
    int message;
    int ticket;
    while(true){
        for(int i = 0; i < size; i++){
            if(inp("terminalOut", term[i], konc, ?message)){
                in("ticket", ?ticket);
                out("ticket", ticket + 1);
                out("centralniIn", term, konc, ticket, message);
            }
        }

        for(int i = 0; i < size; i++){
            if(inp("centralniOut", term[i], konc, ?message))
                out("terminalIn", term[i], message);
        }
    }
}

void centralni(){
    int ticket = 1;
    int term;
    int konc;
    int message;
    while(true){
        in("centralniIn", ?term, ?konc, ticket++, ?message);
        // do smth with message
        out("centralniOut", term, konc, message);
    }
}

void main(){
    out("ticket", 1);
    // pokretanje svega, inicijalizacija niza...
}
