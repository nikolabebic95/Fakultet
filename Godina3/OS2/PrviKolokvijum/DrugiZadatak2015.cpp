class Server {
private Data data_;
private boolean put_allowed_=true;

public synchronized void put (Data d){
    while(put_allowed_==false) wait();
    data_=d;
    put_allowed_==false;
    notifyAll();
}

public synchronized Data get (){
    Data d;
    while(put_allowed_==true) wait();
    d=data_;
    put_allowed_==true;
    notifyAll();
    return d;
}

}
