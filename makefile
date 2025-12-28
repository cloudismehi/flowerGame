raylib_dep = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
portaudio_dep = -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreServices

gamey: Flowers.o World.o Character.o GameLogic.o gamey.o
	@g++ -std=c++20 ${raylib_dep} ${portaudio_dep} -lportaudio -lraylib src/obj/Character.o src/obj/GameLogic.o \
	src/obj/World.o src/obj/Flowers.o src/obj/gamey.o -o gamey
	@@mv gamey execs
	@echo "built! :) "

gamey.o: src/main.cpp
	@g++ -std=c++20 src/main.cpp -I . -I include -c -o gamey.o 
	@mv gamey.o src/obj

GameLogic.o: src/GameLogic.cpp
	@g++ -std=c++20 src/GameLogic.cpp -I . -I include -c -o GameLogic.o 
	@mv GameLogic.o src/obj

Flowers.o: src/Flowers.cpp
	@g++ -std=c++20 src/Flowers.cpp -I . -I include -c -o Flowers.o 
	@mv Flowers.o src/obj

Character.o: src/Character.cpp
	@g++ -std=c++20 src/Character.cpp -I . -I include -c -o Character.o 
	@mv Character.o src/obj


World.o: src/World.cpp
	@g++ -std=c++20 src/World.cpp -I . -I include -c -o World.o 
	@mv World.o src/obj



clean: 
	@rm -f src/obj/*.o execs/gamey
	@rm -r execs
	@mkdir execs
	@echo "cleaned! :) "