objects = src/main.o src/system.o src/auth.o src/utils.o

atm: $(objects)
	cc -o atm $(objects)

src/main.o: src/header.h 
src/system.o: src/header.h 
src/auth.o: src/header.h 
src/utils.o: src/header.h

clean:
	rm -f $(objects) atm
