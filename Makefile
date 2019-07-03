all: clean lab_4_2019_new.o
	g++ -o app.exe -O3 lab_4_2019_new.o
lab_4_2019_new.o:
	g++ -c -std=c++17 -O3 lab_4_2019_new.cpp
clean:
	rm -f app.exe
	rm -f *.o