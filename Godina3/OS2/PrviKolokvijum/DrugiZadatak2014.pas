monitor TaxiDispatcher;
 export userRequest, taxiAvailable;
 var 
    cnt_taxi:int;
    cnt_user:int;
    con_var:conditional_variable;
 procedure userRequest ()
 begin
    cnt_user=cnt_user+1;
    if(cnt_taxi>0) 
    begin
        cnt_taxi=cnt_taxi-1;
        con_var.notify();
    end
    else
    begin
        while(cnt_taxi==0) con_var.wait();
        cnt_taxi=cnt_taxi-1;
    end;
 end

 procedure taxiAvailable ()
 begin
    cnt_taxi=cnt_taxi+1;
    if(cnt_user>0) 
    begin
        cnt_user=cnt_user-1;
        con_var.notify();
    end
    else
    begin
        while(cnt_user==0) con_var.wait();
        cnt_user=cnt_user-1;
    end;
 end

begin
    cnt_taxi=0;
    cnt_user=0;
end;