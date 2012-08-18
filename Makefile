exe: ogre test
	g++ -o exe test.o Core.o Window.o Renderer.o -lGL -lGLU -lglut
test: test.cpp
	g++ -c test.cpp
ogre: src/Core.cpp src/Window.cpp src/Renderer.cpp src/Camera.cpp
	g++ -c src/Core.cpp src/Window.cpp src/Renderer.cpp src/Camera.cpp
