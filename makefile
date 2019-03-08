all: main.o drawer.o display.o edge_matrix.o transformation_matrix.o mdl_parser.o obj_parser.o
	g++ -std=c++11 -o main.out main.o drawer.o display.o edge_matrix.o transformation_matrix.o mdl_parser.o obj_parser.o
	./main.out

main.o: main.cpp settings.h
	g++ -std=c++11 -c main.cpp

drawer.o: drawing/drawer.cpp drawing/drawer.h settings.h
	g++ -std=c++11 -c drawing/drawer.cpp

display.o: drawing/display.cpp drawing/display.h settings.h
	g++ -std=c++11 -c drawing/display.cpp

edge_matrix.o: matrix/edge_matrix.cpp matrix/edge_matrix.h matrix/transformation_matrix.h settings.h
	g++ -std=c++11 -c matrix/edge_matrix.cpp

transformation_matrix.o: matrix/transformation_matrix.cpp matrix/transformation_matrix.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -c matrix/transformation_matrix.cpp

mdl_parser.o: parsing/mdl_parser.cpp matrix/transformation_matrix.h matrix/edge_matrix.h drawing/drawer.h settings.h
	g++ -std=c++11 -c parsing/mdl_parser.cpp

obj_parser.o: parsing/obj_parser.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -c parsing/obj_parser.cpp

clean:
	touch fakefile.o
	touch fakefile.h.gch
	touch main.out
	rm *.o
	rm main.out
	rm *.h.gch