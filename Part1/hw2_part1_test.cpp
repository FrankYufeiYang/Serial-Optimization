#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <hw2_part1.hpp>

void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}

// complex algorithm for evaluation
void myfunc_orig(double *s, double *mat, int *v, int length)
{
	// this assumes that the two dimensional vector is square 

	double val;

	for (int j = 0; j < length; j ++)
	{
		for (int i = 0; i < length; i++)
		{
			val = round(fmod(v[i],256)); 
			mat[i + j * length] = s[i + j * length]*(sin(val)*sin(val)-cos(val)*cos(val));
		}
	}
}

void compareOutputs(double *output1, double *output2, int length)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
		{
			if (output1[i * length + j] != output2[i * length + j])
			{
				printf("Outputs do not match! (%f, %f)\n", 
					output1[i * length + j], output2[i * length + j]);
				return;
			}
		}
	
	printf("Output match, test passed!\n");
						
}


int main(int argc, char *argv[])
{

	int N = 500;

	double d_S, d_E;

	// some declarations
	double *input1 = new double[N * N];
	int *input2 = new int[N];
	
	double *output = new double[N * N];
	double *orig_output = new double[N * N];

	// populate memory with some random data
	for (int i = 0; i < N; i++)
	{
		input2[i] = i * i;
		for (int j = 0; j < N; j++)
			input1[i * N + j] = j + i;
	}

	// run the original for functional verification
	myfunc_orig(input1, orig_output, input2, N);

	// start benchmark
	get_walltime(&d_S);

	// iterative test loop
	myfunc(input1, output, input2, N);

	// end benchmark
	get_walltime(&d_E);

	// check the two matrices
	compareOutputs(orig_output, output, N);
		
	// report results
	printf("Elapsed time: %f\n", d_E - d_S);



	return 0;
}
