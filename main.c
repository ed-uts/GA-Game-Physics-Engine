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

void script(float bx,float by,float bz,
            float fx,float fy,float fz,
            float gx,float gy,float gz,
            float m0,
            float mx,float my,float mz,
            float px,float py,float pz,
            float vx,float vy,float vz){
            
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

        // much of the code is repeated with the same structure 
        // and has not been included
}

int main(int argc, char *argv[]){

	float bx = 5.0, by = 0.0, bz = 10.0;
	float fx = 0.0, fy = 0.0, fz = 0.0;
	float gx = 0.0, gy = 0.0, gz = -9.8;

	float m0 = 1.0;
	float mx = 0.0, my = 0.0, mz = 0.0;
	float px = 0.0, py = 0.0, pz = 20.0;
	float vx = 0.0, vy = 5.0, vz = 0.0;

	script(bx, by, bz, 
                fx, fy, fz, 
                gx, gy, gz, 
                m0, 
                mx, my, mz, 
                px, py, pz, 
                vx, vy, vz);
}
