#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float vector_sum(float *v1, int size);
float dot_product_2(float *v1, float *v2, int size);
float dot_product_3(float *v1, float *v2, float *v3, int size);

float MNew[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float BNew[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float PNew[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void script(float bx,float by,float bz,float fx,float fy,float fz,float gx,float gy,float gz,float m0,float mx,float my,float mz,float px,float py,float pz,float vx,float vy,float vz){
	MNew[0] = m0;
	// MNew[0] = m0

	float ve0[2] = {mx,-0.5};
	float ve1[2] = {1.0,bx};
	float ve2[2] = {1.0,m0};
	MNew[5] = dot_product_3(ve0,ve1,ve2,2);
	// MNew[5] = mx - ((0.5 * bx) * m0)

	float ve3[2] = {my,-0.5};
	float ve4[2] = {1.0,by};
	float ve5[2] = {1.0,m0};
	MNew[6] = dot_product_3(ve3,ve4,ve5,2);
	// MNew[6] = my - ((0.5 * by) * m0)

	float ve6[2] = {mz,-0.5};
	float ve7[2] = {1.0,bz};
	float ve8[2] = {1.0,m0};
	MNew[7] = dot_product_3(ve6,ve7,ve8,2);
	// MNew[7] = mz - ((0.5 * bz) * m0)

	float temp_gcse_2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float ve9[1] = {m0};
	float ve10[1] = {m0};
	temp_gcse_2[0] = dot_product_2(ve9,ve10,1);
	// temp_gcse_2[0] = m0 * m0

	float tempmv11[1] = {0};
	float ve12[2] = {gx,fx};
	tempmv11[0] = vector_sum(ve12,2);
	float ve13[3] = {temp_gcse_2[0],tempmv11[0],bx};
	float ve14[3] = {vx,temp_gcse_2[0],1.0};
	BNew[5] = dot_product_2(ve13,ve14,3);
	// BNew[5] = ((temp_gcse_2[0] * vx) + ((gx + fx) * temp_gcse_2[0])) + bx

	float tempmv15[1] = {0};
	float ve16[2] = {gy,fy};
	tempmv15[0] = vector_sum(ve16,2);
	float ve17[3] = {temp_gcse_2[0],tempmv15[0],by};
	float ve18[3] = {vy,temp_gcse_2[0],1.0};
	BNew[6] = dot_product_2(ve17,ve18,3);
	// BNew[6] = ((temp_gcse_2[0] * vy) + ((gy + fy) * temp_gcse_2[0])) + by

	float tempmv19[1] = {0};
	float ve20[2] = {gz,fz};
	tempmv19[0] = vector_sum(ve20,2);
	float ve21[3] = {temp_gcse_2[0],tempmv19[0],bz};
	float ve22[3] = {vz,temp_gcse_2[0],1.0};
	BNew[7] = dot_product_2(ve21,ve22,3);
	// BNew[7] = ((temp_gcse_2[0] * vz) + ((gz + fz) * temp_gcse_2[0])) + bz

	float temp_gcse_1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float ve23[1] = {2.0};
	float ve24[1] = {MNew[0]};
	temp_gcse_1[0] = dot_product_2(ve23,ve24,1);
	// temp_gcse_1[0] = 2.0 * MNew[0]

	float temp_gcse_3[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float ve25[1] = {MNew[0]};
	float ve26[1] = {MNew[0]};
	temp_gcse_3[0] = dot_product_2(ve25,ve26,1);
	// temp_gcse_3[0] = MNew[0] * MNew[0]

	float ve27[4] = {temp_gcse_1[0],temp_gcse_1[0],temp_gcse_1[0],temp_gcse_3[0]};
	float ve28[4] = {MNew[7],MNew[6],MNew[5],1.0};
	float ve29[4] = {pz,py,px,1.0};
	PNew[1] = dot_product_3(ve27,ve28,ve29,4);
	// PNew[1] = ((((temp_gcse_1[0] * MNew[7]) * pz) + ((temp_gcse_1[0] * MNew[6]) * py)) + ((temp_gcse_1[0] * MNew[5]) * px)) + temp_gcse_3[0]

	float ve30[1] = {temp_gcse_3[0]};
	float ve31[1] = {px};
	PNew[2] = dot_product_2(ve30,ve31,1);
	// PNew[2] = temp_gcse_3[0] * px

	float ve32[1] = {temp_gcse_3[0]};
	float ve33[1] = {py};
	PNew[3] = dot_product_2(ve32,ve33,1);
	// PNew[3] = temp_gcse_3[0] * py

	float ve34[1] = {temp_gcse_3[0]};
	float ve35[1] = {pz};
	PNew[4] = dot_product_2(ve34,ve35,1);
	// PNew[4] = temp_gcse_3[0] * pz
}

void output(){
	printf("M: ");

	printf("%f ", MNew[0]);
	printf("%f ", MNew[5]);
	printf("%f ", MNew[6]);
	printf("%f", MNew[7]);

	printf("\n");

	printf("B: ");

	printf("%f ", BNew[5]);
	printf("%f ", BNew[6]);
	printf("%f", BNew[7]);

	printf("\n");

	printf("P: ");

//	printf("%f ", PNew[1]);
	printf("%f ", PNew[2] / PNew[1]);
	printf("%f ", PNew[3] / PNew[1]);
	printf("%f", PNew[4] / PNew[1]);

	printf("\n");
}

int main(int argc, char *argv[]){

	float bx = 5.0, by = 0.0, bz = 10.0;
	float fx = 0.0, fy = 0.0, fz = 0.0;
	float gx = 0.0, gy = 0.0, gz = -9.8;

	float m0 = 1.0;
	float mx = 0.0, my = 0.0, mz = 0.0;
	float px = 0.0, py = 0.0, pz = 20.0;
	float vx = 0.0, vy = 5.0, vz = 0.0;

	script(bx, by, bz, fx, fy, fz, gx, gy, gz, m0, mx, my, mz, px, py, pz, vx, vy, vz);
}
