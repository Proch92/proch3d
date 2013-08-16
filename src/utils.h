#define DEG2RAD 0.01745329252

long get_time();
void p3d_delay(long);
void load_shader(const char*, GLuint);
void print_mat4(const glm::mat4&);
void print_vec3(const glm::vec3&);
glm::quat RotationBetweenVectors(glm::vec3, glm::vec3);