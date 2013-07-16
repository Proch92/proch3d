class P3d_Mesh {
	public:
		P3d_Mesh();
		~P3d_Mesh();
		void render();
		bool load_mesh(char*);

		P3d_Vertex* vertices;
		int* indices;
	private:
		int material_index;
		int num_vertices;
		int num_faces;
};

P3d_Mesh *P3d_load_mesh(char*);