exe: p3d test
	g++ -o exe test.o P3d_Window.o P3d_Renderer.o P3d_Camera.o P3d_Math.o P3d_Entity.o P3d_Object.o P3d_Timer.o utils.o P3d_InputManager.o -lGL -lGLU -lsfml-graphics -lsfml-window -lsfml-system
test: test.cpp
	g++ -c test.cpp
p3d: src/P3d_Window.cpp src/P3d_Renderer.cpp src/P3d_Camera.cpp src/P3d_Math.cpp src/P3d_Entity.cpp src/P3d_Object.cpp src/P3d_Timer.cpp src/utils.cpp src/P3d_InputManager.cpp
	g++ -c src/P3d_Window.cpp src/P3d_Renderer.cpp src/P3d_Camera.cpp src/P3d_Math.cpp src/P3d_Entity.cpp src/P3d_Object.cpp src/P3d_Timer.cpp src/utils.cpp src/P3d_InputManager.cpp
