raylib_dep = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

worldGen: worldGen.o 
	@g++ -g -std=c++20 ${raylib_dep} -lraylib src/obj/worldGen.o -o worldGen 
	@mv worldGen execs
	@echo "built!"

worldGen.o: src/worldGen.cpp
	@g++ -g -std=c++20 -c src/worldGen.cpp -o src/obj/worldGen.o -I . 

