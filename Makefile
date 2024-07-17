parametrosCompilacao = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 --libs --cflags)
nomePrograma = streetfighter
srcDir = src

all: $(nomePrograma)

$(nomePrograma): $(srcDir)/streetfighter.o $(srcDir)/streetlib.o $(srcDir)/ataques.o $(srcDir)/Joystick.o $(srcDir)/maingameFunc.o
	gcc -Wall $(srcDir)/streetfighter.o $(srcDir)/streetlib.o $(srcDir)/ataques.o $(srcDir)/Joystick.o $(srcDir)/maingameFunc.o -o $(nomePrograma) $(parametrosCompilacao)

$(srcDir)/streetfighter.o: $(srcDir)/streetfighter.c
	gcc -c $(srcDir)/streetfighter.c -o $(srcDir)/streetfighter.o -Wall $(parametrosCompilacao)

$(srcDir)/streetlib.o: $(srcDir)/streetlib.c
	gcc -c $(srcDir)/streetlib.c -o $(srcDir)/streetlib.o -Wall $(parametrosCompilacao)

$(srcDir)/ataques.o: $(srcDir)/ataques.c
	gcc -c $(srcDir)/ataques.c -o $(srcDir)/ataques.o -Wall $(parametrosCompilacao)

$(srcDir)/Joystick.o: $(srcDir)/Joystick.c
	gcc -c $(srcDir)/Joystick.c -o $(srcDir)/Joystick.o -Wall $(parametrosCompilacao)

$(srcDir)/maingameFunc.o: $(srcDir)/maingameFunc.c
	gcc -c $(srcDir)/maingameFunc.c -o $(srcDir)/maingameFunc.o -Wall $(parametrosCompilacao)

clean:
	rm -f $(srcDir)/*.o

purge:
	rm -f $(srcDir)/*.o *~ *.gch $(nomePrograma)

.PHONY: purge clean

