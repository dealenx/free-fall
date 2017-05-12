#include "./general/general.h"

using namespace std;



void main() {
	setlocale(LC_CTYPE, "rus");

	double a = 0; // Левая граница
	double b; // Правая граница
	

	double yFirst; // Значение функции y(a)
	double yLast = 0; // Значение функции y(b)

	printf("Введите время: ");
	scanf_s("%lf", &b);

	printf("\n");
	 
	printf("Введите высоту: ", a);
	scanf_s("%lf", &yFirst);

	double koef; // Коэффициент

	printf("Введите коэффициент: ");
	scanf_s("%lf", &koef);
	

	int s; // Количество сегментов

	printf("Введите количество сегментов: ");
	scanf_s("%d", &s);

	
	int k = s - 1; // количество точек, не включая границы

	long int n = s + 1; // Количество всех точек, включая границы
	double h = (b - a) / s; // Шаг

	double *y = new double[n];
	y[0] = yFirst; y[s] = yLast;

	const int N = k, M = s; // Размерность матрицы

	double *x = new double[n];

	for (int i = 0; i < n; i++)
	{
		x[i] = a + (i*h);
		//printf("x[%d]=%g ", i, x[i]);
	}
	printf("\n");

	double *f = new double[s];

	for (int i = 0; i < n; i++)
	{
		f[i] = G * (-1);

		if (i == 0)
		{
			f[i] = ( G * (-1) ) - ( y[0] / (h * h) ) + ( (y[0] * k) / (2 * h) );
		}
		if (i == n - 1)
		{
			f[i] = (G * (-1)) - (y[s] / (h * h)) + ((y[s] * k) / (2 * h));
		}
	}


	double** A = new double*[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new double[M];
	}

	printf("Заполнение матрицы . . . \n");
	FillMatrix(A, f, h, N, koef);

	double *yy = new double[k];

	printf("Решение метода Гаусса . . . \n");
	Solve(A, yy, N);

	for (int i = 0; i < N; i++)
	{
		y[i + 1] = yy[i];
	}



	for (int i = 0; i < n; i++)
	{
		cout << "y[" << i << "] = " << y[i] << " ";
	}
	//cout << "y = " << y[s];

}