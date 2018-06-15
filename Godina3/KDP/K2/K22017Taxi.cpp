monitor TaxiStation{
    enum Type {SMALL = 0, MEDIUM = 1, LARGE = 2, SIZE = 3};
    conditionVariable cvPeople[SIZE];
    conditionVariable cvTaxis[SIZE];

    void wantVehicle(Type type){
        if(!cvTaxis[type].empty()){
            cvTaxis[type].signal();
            return;
        }

        if(type + 1 < SIZE){
            if(!cvTaxis[type + 1].empty()){
                cvTaxis[type + 1].signal();
                return;
            }
        }

        if(type + 2 < SIZE){
            if(!cvTaxis[type + 2].empty()){
                cvTaxis[type + 2].signal();
                return;
            }
        }

        cvPeople[type].wait();
    }

    void vehicleArrived(Type type){
        if(!cvPeople[type].empty()){
            cvPeople[type].signal();
            return;
        }

        if(type - 1 >= 0){
            if(!cvPeople[type - 1].empty()){
                cvPeople[type - 1].signal();
                return;
            }
        }

        if(type - 2 >= 0){
            if(!cvPeople[type - 2].empty()){
                cvPeople[type - 2].signal();
                return;
            }
        }

        cvTaxis[type].wait();
    }
};