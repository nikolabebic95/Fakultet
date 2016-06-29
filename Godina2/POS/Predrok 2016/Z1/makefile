all: lib/libmyposix.a izvrsni

lib/libmyposix.a: sys/obj/Matrix.o sys/obj/Semaphore.o sys/obj/Thread.o
	ar cq $@ $^
	ar -t $@

sys/obj/%.o: sys/src/%.cpp
	g++ -o $@ -c $< -Isys/h -Wall

izvrsni: usr/jezgro.cpp usr/NitX.h
	g++ -pthread -o izvrsni usr/jezgro.cpp usr/NitX.h lib/libmyposix.a -Isys/h -Wall

clean:
	rm -f sys/obj/*
	rm -f lib/*
	rm izvrsni
PHONY.:clean
