all: bin/hamming.o main.cpp coder.cpp decoder.cpp
	@g++ -std=c++17 main.cpp    src/Hamming/src/hamming.cpp  src/Hamming/src/HammingArray.cpp -o bin/main
	@g++ -std=c++17 coder.cpp   src/Hamming/src/hamming.cpp  src/Hamming/src/HammingArray.cpp -o bin/coder
	@g++ -std=c++17 decoder.cpp src/Hamming/src/hamming.cpp  src/Hamming/src/HammingArray.cpp -o bin/decoder
	@g++ -std=c++17 demon.cpp   src/Hamming/src/hamming.cpp  src/Hamming/src/HammingArray.cpp -o bin/demon

bin/hamming.o : src/Hamming/src/hamming.cpp src/Hamming/include/hamming.h bin/HammingArray.o
	@g++ -std=c++17 -c src/Hamming/src/hamming.cpp bin/HammingArray.o -o bin/hamming.o 

bin/HammingArray.o : src/Hamming/src/HammingArray.cpp src/Hamming/src/HammingArray.h
	@g++ -std=c++17 -c src/Hamming/src/HammingArray.cpp -o bin/HammingArray.o 

# @g++ -std=c++17 main.cpp bin/hamming.o -o bin/main
# @g++ -std=c++17 coder.cpp bin/hamming.o -o bin/coder
# @g++ -std=c++17 decoder.cpp bin/hamming.o -o bin/decoder
# @g++ -std=c++17 demon.cpp bin/hamming.o -o bin/demon

#	xxd -b file
# 	kill -KILL PID
# 	ps -eF
