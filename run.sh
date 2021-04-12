
# run.sh

# Compile and run sender.cpp 
g++ sender.cpp -o sender.o -std=c++17
./sender.o

# Compile and run recv.cpp
g++ recv.cpp -o recv.o -std=c++17 
./recv.o

# Clean up files
rm *.o

