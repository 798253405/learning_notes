//
// Created by yz on 16.12.20.
//


#include "compute_u.h"
void compute_u(float uread[M_row][K_comp],float vtread[K_comp][N_col],\
		float vread[N_col][K_comp],float b_u[M_row][K_comp],\
		int ite_maxnum,float  outputuread[M_row][K_comp])
{
#pragma HLS INTERFACE s_axilite port=uread bundle=in
#pragma HLS INTERFACE s_axilite port=vtread bundle=in
#pragma HLS INTERFACE s_axilite port=vread bundle=in
#pragma HLS INTERFACE s_axilite port=b_u bundle=in
#pragma HLS INTERFACE s_axilite port=outputuread bundle=out
//code with pragma brings large usage of bram

    //uread[0][0]=5432; //change one value in binary file to see whether it works by reading bin file
    float a_u[M_row][K_comp];
    float outuread[M_row][K_comp]={0};
    float uvt[M_row][N_col]={0};
    for (int i = 0; i < M_row; i++)
        for (int j = 0; j < K_comp; j++)
        {
            outuread[i][j]=uread[i][j];
            //	outputuread[i][j]=outuread[i][j];
        }//avoid write and read matrix:uread at the same time, which brings error while sync.
    for (int ite = 0; ite < ite_maxnum; ite++)
    {
        for (int i = 0; i < M_row; i++)
            for (int j = 0; j < N_col; j++)
            {
                float tempuvt=0;
                for (int k = 0; k < K_comp; k++) {
                    tempuvt += outuread[i][k] * vtread[k][j];
                }
                uvt[i][j] = tempuvt;
            }
        for (int i = 0; i < M_row; i++)
            for (int j = 0; j < K_comp; j++)
            {
                float tempa_u = 0;
                for (int k = 0; k < N_col; k++)
                {
                    tempa_u += uvt[i][k] * vread[k][j];
                }
                a_u[i][j] = tempa_u;
            }
        for (int i = 0; i < M_row; i++)
            for (int j = 0; j < K_comp; j++)
            {
                //if (a_u[i, j] != 0)
                {

                    outuread[i][j]= outuread[i][j] * b_u[i][j] / (a_u[i][j]+0.000000001);
                    //	uread[i][j]=uread[i][j] * b_u[i][j] / (a_u[i][j]+0.000000001);
                }
            }

    }


    //	uread[0][0]=1010;
}
