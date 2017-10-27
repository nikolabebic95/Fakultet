class Mutex{
public:
    void lock(){
        if(in) con_var_.wait();
        in=true;
    }

    void unlock(){
        in=false;
        con_var_.notify();
    }

private:
    conditional_variable con_var_;
    bool in=false;
};
