class FlipFlopMonitor{
private:
    const int N_;
    condition_variable con_var_;
    int cnt_;
public:
    FlipFlopMonitor(int N): N_(N), cnt_(N){}

    void flip(){
        while(cnt_<N_) con_var_.wait();

        ...

        cnt_=0;
    }

    void flop(){
        if(cnt_<N_)
            cnt_++;

        ...

        con_var_.notify());
    }
};