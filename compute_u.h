
#define M_row 1000 //row
#define N_col 784 //col
#define K_comp 30 //


void compute_u(float uread[M_row][K_comp],float vtread[K_comp][N_col],\
		float vread[N_col][K_comp],float b_u[M_row][K_comp],\
		int ite_maxnum, float outputuread[M_row][K_comp] );
