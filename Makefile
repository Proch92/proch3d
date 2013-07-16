all: p3d test
	ar rvs libp3d.a P3d_Window.o P3d_Renderer.o P3d_Camera.o P3d_Math.o P3d_Entity.o P3d_Object.o P3d_Timer.o utils.o P3d_InputManager.o P3d_Mesh.o P3d_Vertex.o
	g++ -o exe test_mesh.o libp3d.a -lGL -lGLU -lsfml-graphics -lsfml-window -lsfml-system -lassimp
	
	rm *.o
p3d: src/P3d_Window.cpp src/P3d_Renderer.cpp src/P3d_Camera.cpp src/P3d_Math.cpp src/P3d_Entity.cpp src/P3d_Object.cpp src/P3d_Timer.cpp src/utils.cpp src/P3d_InputManager.cpp src/P3d_Mesh.cpp src/P3d_Vertex.cpp
	g++ -c src/P3d_Window.cpp src/P3d_Renderer.cpp src/P3d_Camera.cpp src/P3d_Math.cpp src/P3d_Entity.cpp src/P3d_Object.cpp src/P3d_Timer.cpp src/utils.cpp src/P3d_InputManager.cpp src/P3d_Mesh.cpp src/P3d_Vertex.cpp
test: examples/test_mesh.cpp
	g++ -c examples/test_mesh.cpp
clean:
	rm *.o