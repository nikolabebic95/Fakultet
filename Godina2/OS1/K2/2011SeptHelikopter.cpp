/*Koriscenjem standardnih brojackih semafora resiti problem utrkivanja (
engl. race condition) u kodu datog programa koji simulira rad policijskog 
helikoptera i automobila, a koji je objasnjen na predavanjima.
type Coord = record {
  x : integer;
  y : integer;
};

var sharedCoord : Coord;

process Helicopter
var nextCoord : Coord;
begin
  loop
    computeNextCoord(nextCoord);
    sharedCoord := nextCoord; 
  end;
end;

process PoliceCar
begin
  loop
    moveTo(sharedCoord);
  end;
end;*/

type Coord = record {
    x : integer;
    y : integer;
};

var
    sh: semaphore :=1;
    sa: semaphore :=0; 

var sharedCoord : Coord;

process Helicopter
var nextCoord : Coord;
begin
    loop
        computeNextCoord(nextCoord);
        sh.wait();
        sharedCoord := nextCoord;
        sa.signal();
    end;
end;

process PoliceCar
var nextCoord : Coord;
begin
    loop
        sa.wait();
        nextCoord:=sharedCoord;
        sh.signal();
        moveTo(sharedCoord);
    end;
end;
