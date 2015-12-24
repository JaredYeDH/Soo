Lsy:soo_main.o soo_ast.o soo_global.o soo_parse.o soo_token.o
	g++ -g soo_main.o soo_ast.o soo_global.o soo_parse.o soo_token.o -o Lsy
soo_main.o:soo/soo_main.cpp soo/soo_token.h soo/soo_parse.h
	g++ -std=c++11 -g -c soo/soo_main.cpp
soo_ast.o:soo/soo_ast.cpp soo/soo_ast.h soo/soo_token.h
	g++ -std=c++11 -g -c soo/soo_ast.cpp
soo_global.o:soo/soo_global.cpp soo/soo_global.h
	g++ -std=c++11 -g -c soo/soo_global.cpp
soo_parse.o:soo/soo_parse.cpp soo/soo_parse.h soo/soo_ast.h soo/soo_global.h
	g++ -std=c++11 -g -c soo/soo_parse.cpp
soo_token.o:soo/soo_token.cpp soo/soo_token.h soo/soo_global.h
	g++ -std=c++11 -g -c soo/soo_token.cpp

clean:
	rm -f *.o Lsy
