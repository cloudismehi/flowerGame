raylib_dep = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

worldGen: worldGen.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/worldGen.o -o worldGen 
	@mv worldGen execs
	@echo "built!"

worldGen.o: src/worldGen.cpp
	@g++ -g -std=c++20 -c src/worldGen.cpp -o src/obj/worldGen.o -I . 

roomGen: roomGen.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/roomGen.o -o roomGen 
	@mv roomGen execs
	@echo "built!"

roomGen.o: src/roomGen.cpp
	@g++ -g -std=c++20 -c src/roomGen.cpp -o src/obj/roomGen.o -I . 

enemy: enemy.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/enemy.o -o enemy 
	@mv enemy execs
	@echo "built!"

enemy.o: src/enemy.cpp
	@g++ -g -std=c++20 -c src/enemy.cpp -o src/obj/enemy.o -I . 

basicScreen: basicScreen.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/basicScreen.o -o basicScreen 
	@mv basicScreen execs
	@echo "built!"

basicScreen.o: src/basicScreen.cpp
	@g++ -g -std=c++20 -c src/basicScreen.cpp -o src/obj/basicScreen.o -I . 


babysBreathScreen: babysBreathScreen.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/babysBreathScreen.o -o babysBreathScreen 
	@mv babysBreathScreen execs
	@echo "built!"

babysBreathScreen.o: src/babysBreathScreen.cpp
	@g++ -g -std=c++20 -c src/babysBreathScreen.cpp -o src/obj/babysBreathScreen.o -I . 

