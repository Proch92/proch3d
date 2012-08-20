exe: ogre test
	g++ -o exe test.o Core.o Window.o Renderer.o Camera.o P3d_Math.o Entity.o Object.o -lGL -lGLU -lglut
test: test.cpp
	g++ -c test.cpp
ogre: src/Core.cpp src/Window.cpp src/Renderer.cpp src/Camera.cpp src/P3d_Math.cpp src/Entity.cpp src/Object.cpp
	g++ -c src/Core.cpp src/Window.cpp src/Renderer.cpp src/Camera.cpp src/P3d_Math.cpp src/Entity.cpp src/Object.cpp
