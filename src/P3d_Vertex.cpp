#include "proch3d.h"

P3d_Vertex::P3d_Vertex(const P3d_Vector3f& p, const P3d_Vector2f& t, const P3d_Vector3f& n) {
	pos = p;
	tex = t;
	norm = n;
}

void P3d_Vertex::set_position(const P3d_Vector3f& p) {
	pos = p;
}

void P3d_Vertex::set_tex_coordinate(const P3d_Vector2f& t) {
	tex = t;
}

void P3d_Vertex::set_normal(const P3d_Vector3f& n) {
	norm = n;
}