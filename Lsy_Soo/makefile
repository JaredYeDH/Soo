Soo:soo_main.o soo_ast.o soo_global.o soo_parse.o soo_token.o
	g++ -g soo_main.o soo_ast.o soo_global.o soo_parse.o soo_token.o -o Soo
soo_main.o:src/soo_main.cpp src/soo_token.h src/soo_parse.h
	g++ -std=c++11 -g -c src/soo_main.cpp
soo_ast.o:src/soo_ast.cpp src/soo_ast.h src/soo_token.h
	g++ -std=c++11 -g -c src/soo_ast.cpp
soo_global.o:src/soo_global.cpp src/soo_global.h
	g++ -std=c++11 -g -c src/soo_global.cpp
soo_parse.o:src/soo_parse.cpp src/soo_parse.h src/soo_ast.h src/soo_global.h
	g++ -std=c++11 -g -c src/soo_parse.cpp
soo_token.o:src/soo_token.cpp src/soo_token.h src/soo_global.h
	g++ -std=c++11 -g -c src/soo_token.cpp

clean:
	rm -f *.o Soo
