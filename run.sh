g++ sender.cpp -o sender.o -std=c++17
./sender.o keyfile.txt

g++ recv.cpp -o recv.o -std=c++17
./recv.o

rm *.o