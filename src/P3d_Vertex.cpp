#include "proch3d.h"

P3d_Vertex::P3d_Vertex(const glm::vec3& p, const glm::vec2& t, const glm::vec3& n) {
	pos = p;
	tex = t;
	norm = n;
}

void P3d_Vertex::set_position(const glm::vec3& p) {
	pos = p;
}

void P3d_Vertex::set_tex_coordinate(const glm::vec2& t) {
	tex = t;
}

void P3d_Vertex::set_normal(const glm::vec3& n) {
	norm = n;
}