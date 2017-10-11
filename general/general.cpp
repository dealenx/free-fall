#include "../general/general.h"

using namespace std;

// TODO:

double MaxVector(double *y, int length) 
{
	double max = y[0];

	for (int i = 1; i < length; i++)
	{
		if ( max < y[i] )
		{
			max = y[i];
		}
	}

	return max;
}

void triangMatr(double** A, double **B, int N)
{
	int i, j, k;
	double koef;
	for (i = 0; i<N; i++)
		for (j = 0; j<N + 1; j++)
			B[i][j] = A[i][j];

	for (k = 0; k<N; k++)
	{
		for (i = k + 1; i<N; i++)
		{
			koef = -1.0 *B[i][k] / B[k][k];
			for (j = k; j<N + 1; j++)
				B[i][j] = B[i][j] + B[k][j] * koef;
		}
	}
}

void Solve(double **A, double *x, int N)
{
	int i, j, k;
	double res = 0;
	double **B = new double *[N];
	for (i = 0; i<N; i++)
	{
		B[i] = new double[N + 1];
	} cout << endl;

	triangMatr(A, B, N);
	for (i = N - 1; i >= 0; i--)
	{
		res = 0;
		for (j = i + 1; j <= N - 1; j++)
			res -= x[j] * B[i][j];
		res += B[i][N];
		x[i] = res / B[i][i];
		cout << "x[ " << i << "] =" <<  x[i] << endl;

		
	}
	for (i = 0; i<N; i++)  
	{
		delete[] B[i];
	}
	delete[]B;
}

void OutputDescMatr(double** M, int n, int m)
{ // function for output matrix on screen
	int i, j;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
			printf("%g ", M[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

void FillMatrix( /* Заполнение матрицы */
	double **M, //Матрица
	double *f, //заполнения массива f(i)
	double h, // Шаг
	int N,
	double koef // коэффициент
)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{


			if (i == j)
			{
				M[i][j] = ( (-1) * (2)) / (h*h);
			}
			else if (j == i + 1)
			{
				M[i][j] = (1 / (h*h)) + (koef / (2 * h));
			}
			else if (i == j + 1)
			{
				M[i][j] = (1 / (h*h)) - (koef / (2 * h));
			}
			else {
				M[i][j] = 0;
			}
			//printf("%lf ", M[i][j]);
		} //printf("\n ");
	}

	for (int i = 0; i < N; i++)
	{
		M[i][N] = f[i];
	}
}

void GeneralFunc
(	
	double a, // Левая граница
	double b, // Правая граница
	double yFirst,  // Значение функции y(a)
	double yLast, // Значение функции y(b)
	 int s // Количество сегментов
)
{
	
}
void calcMultMatrixVectore(double **A, double *B, double *C, int N, int M) {

	for (int ix = 0; ix < N; ix++)
	{
		C[ix] = 0;
		for (int jx = 0; jx < M; jx++)
			C[ix] += A[ix][jx] * B[jx];
	}
}

void checkFillMatrix(double **A, double *y, double *f, double * approx, int N) {
	double *ny = new double[N]; //для матрицы 
	for (int i = 0; i < N; i++)
	{
		ny[i] = y[i + 1];
	}
	
	double *C = new double[N]; // вектор, результатом где является матрица умноженная на точное решение
	calcMultMatrixVectore(A, ny, C, N, N);
	for (int i = 0; i < N; i++)
	{
		ny[i] = y[i + 1];
		approx[i] = fabs(C[i] - f[i]);
		cout << "A*yt = " << C[i] << " f = " << f[i] << " aprox = " << approx[i] << endl;
	}

}