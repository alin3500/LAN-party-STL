build: main.o Player.o echipa.o meci.o
	g++ main.o Player.o echipa.o meci.o  -o lanParty

main.o: main.cpp
	g++ -c main.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

echipa.o: echipa.cpp
	g++ -c echipa.cpp

meci.o: meci.cpp
	g++ -c meci.cpp

clean:
	rm -rf *.o lanParty

