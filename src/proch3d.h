//#define GLEW_STATIC

//utils
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "unistd.h"
#include <iostream>
#include <vector>
#include <sstream>

//libraries
#include <GL/glew.h>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

//proch3d engine
#include "utils.h"
#include "P3d_Timer.h"
#include "P3d_Entity.h"
#include "P3d_Vertex.h"
#include "P3d_Mesh.h"
#include "P3d_Object.h"
#include "P3d_Window.h"
#include "P3d_Camera.h"
#include "P3d_Renderer.h"
#include "P3d_InputManager.h"

#define FLAT_SHADING false
#define SMOOTH_SHADING true