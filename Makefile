LDFLAGS=-lm -Wall -Werror

main : main.o csv_parser.o interface.o data_manager.o utils.o
	gcc -o main main.o csv_parser.o interface.o data_manager.o utils.o ${LDFLAGS}
	rm -f *.o *~
main.o : main.c utils.h interface.h data_manager.h csv_parser.h
	gcc -c main.c -lm
csv_parser.o : csv_parser.c csv_parser.h
	gcc -c csv_parser.c -lm
interface.o : interface.c utils.h interface.h data_manager.h csv_parser.h
	gcc -c interface.c -lm
data_manager.o : data_manager.c utils.h data_manager.h csv_parser.h
	gcc -c data_manager.c -lm
utils.o : utils.c csv_parser.h data_manager.h utils.h
	gcc -c utils.c -lm