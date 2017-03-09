all: img

img: bin/main.o
	gcc -o $@ $^ `pkg-config --libs glib-2.0 gtk+-2.0` -pthread -lm

bin/%.o: src/%.c
	mkdir -p `dirname $@`
	gcc -o $@ -c $< `pkg-config --cflags glib-2.0 gtk+-2.0`
