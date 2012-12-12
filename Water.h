#define SPARE 0.5

class Node {
	public:
		Node();
		void operator * (Node&);
		void applyDelta();
		void heightCorrection();
		void setPID(float, float, float);
		float yval;
		float vel;
		float delta;
		float P, I, D;
};

class Water {
	public:
		Water(int, int);
		void setPID(float, float, float);
		void compute();
		void show();
		void giveInput(int, int, float);
		int dimx;
		int dimy;
	private:
		Node** matrix;
		P3d_Color4f color;
		float P, I, D;
};

#define DEFAULT_P 0.005
#define DEFAULT_I 0.005
#define DEFAULT_D 0.005
#define K 1.2
