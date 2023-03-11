SHELL=/bin/bash
DIR=./bin

run: bf.c
	if [ ! -d $(DIR) ]; then mkdir $(DIR); fi
	gcc -o bin/bf bf.c && ./bin/bf $(FILE)

debug: bf.c
	gcc -g -o ./bin/bf bf.c
	gdb ./bin/bf
