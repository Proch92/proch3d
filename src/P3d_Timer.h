class P3d_Timer {
	public:
		P3d_Timer();
		void start();
		void stop();
		long get_tick();
		long get_elapsed_last_call();
	private:
		long last;
		long last_tick;
};
