all: spbpu_lab_2.o
	g++ -o app.exe -O3 spbpu_lab_2.o
spbpu_lab_2.o:
	g++ -c -std=c++17 -O3 spbpu_lab_2.cpp
clean:
	rm -f app.exe
	rm -f *.o