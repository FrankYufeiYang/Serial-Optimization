#include <math.h>

// Yufei Yang yqy5271@psu.edu
// complex algorithm for evaluation
void myfunc(double *s, double *mat, int *v, int length)
{
	// this assumes that the two dimensional vector is square 

	int val;
	
	#define everything
	
		//origin
	#ifdef origin
	for (int j = 0; j < length; j ++)
	{
		for (int i = 0; i < length; i++)
		{
			val = round(fmod(v[i],256)); 
			mat[i + j * length] = s[i + j * length]*(sin(val)*sin(val)-cos(val)*cos(val));
		}
	}
	#endif

	#ifdef temp
		//temp1
		int temp1;
	for (int j = 0; j < length; j ++)
	{	
		temp1= j*length;
		for (int i = 0; i < length; i++)
		{
			val = round(fmod(v[i],256));
			mat[i + temp1] = s[i + temp1]*(sin(val)*sin(val)-cos(val)*cos(val));
		}
	}
	#endif

	#ifdef table
		// table

	double valTable[length];
	for(int i = 0; i<length; i++){

		valTable[i]= v[i] % 256;
	
		valTable[i] = (sin(valTable[i])*sin(valTable[i])-cos(valTable[i])*cos(valTable[i]));
	
	}
	for (int j = 0; j < length; j ++)
	{	
		for (int i = 0; i < length; i++)
		{
			mat[i + j * length] = s[i + j * length]*valTable[i];
		}
	}
	#endif

	#ifdef unroll
	int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
	for (int j = 0; j < length; j ++)
	{	
		temp1= j*length;
		temp2= (j+1)*length;
		temp3= (j+2)*length;
		temp4= (j+3)*length;
		temp5= (j+4)*length;
		temp6= (j+5)*length;
		temp7= (j+6)*length;
		temp8= (j+7)*length;

		for (int i = 0; i < length; i++)
		{	
			val = round(fmod(v[i],256)); 
			mat[i + temp1] = s[i + temp1]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp2] = s[i + temp2]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp3] = s[i + temp3]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp4] = s[i + temp4]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp5] = s[i + temp5]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp6] = s[i + temp6]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp7] = s[i + temp7]*(sin(val)*sin(val)-cos(val)*cos(val));
			mat[i + temp8] = s[i + temp8]*(sin(val)*sin(val)-cos(val)*cos(val));
			
			//mat[i + j * length] = s[i + j * length]*(sin(val)*sin(val)-cos(val)*cos(val));
		}
	}
	#endif

	#ifdef everything
		//everything
	double valTable[length];
	for(int i = 0; i<length; i++){

		valTable[i]= v[i] % 256;
	
		valTable[i] = (sin(valTable[i])*sin(valTable[i])-cos(valTable[i])*cos(valTable[i]));
	
	}
	int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
	for (int j = 0; j < length ; j+=8)
	{	
		temp1= j*length;
		temp2= (j+1)*length;
		temp3= (j+2)*length;
		temp4= (j+3)*length;
		temp5= (j+4)*length;
		temp6= (j+5)*length;
		temp7= (j+6)*length;
		temp8= (j+7)*length;

		for (int i = 0; i < length; i++)
		{
			mat[i + temp1] = s[i + temp1]*valTable[i];
			mat[i + temp2] = s[i + temp2]*valTable[i];
			mat[i + temp3] = s[i + temp3]*valTable[i];
			mat[i + temp4] = s[i + temp4]*valTable[i];
			mat[i + temp5] = s[i + temp5]*valTable[i];
			mat[i + temp6] = s[i + temp6]*valTable[i];
			mat[i + temp7] = s[i + temp7]*valTable[i];
			mat[i + temp8] = s[i + temp8]*valTable[i];
		}
		if(length%8){
			do{
				temp1 = j*length;
				for (int i = 0; i < length; i++)
				{
					mat[i + temp1] = s[i + temp1]*valTable[i];
				}
			}while(++j<length);
		}
	}
	
	#endif
}

