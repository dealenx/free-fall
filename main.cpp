#include "./general/general.h"

using namespace std;

void main() {
	setlocale(LC_CTYPE, "rus");

	//y = sin(PI*x)
	//y'' = (-1)*(PI)*(PI)*sin(PI*x)

	double a; // Левая граница
	double b; // Правая граница
	int s; // Количество сегментов


	double yFirst; // Значение функции y(a)
	double yLast; // Значение функции y(b)

	printf("y'' = ((-1)*(PI)^2)*sin(PI*x) \n");

	printf("Введите границы [a;b] в формате 'a b': ");
	scanf_s("%lf %lf", &a, &b);

	printf("\n");

	printf("Введите y(%g): ", a);//ФЫ
	scanf_s("%lf", &yFirst);

	printf("Введите y(%g): ", b);
	scanf_s("%lf", &yLast);

	printf("Введите количество сегментов для s: ");
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
		f[i] = ((PI)*(PI)*sin(PI * x[i + 1])) * (-1);

		if (i == 0)
		{
			f[i] = f[i] - y[0];
		}
		if (i == n - 1)
		{
			f[i] = f[i] - y[s];
		}
	}


	double** A = new double*[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new double[M];
	}

	printf("Заполнение матрицы . . . \n");
	FillMatrix(A, f, h, N);
	OutputDescMatr(A, N, M);

	double *yy = new double[k];

	printf("Решение метода Гаусса . . . \n");
	Solve(A, yy, N);

	for (int i = 0; i < N; i++)
	{
		y[i + 1] = yy[i];
	}

	// Теоритическая 'y'
	double *yTheoretical = new double[n];

	for (int i = 0; i < n; i++)
	{
		yTheoretical[i] = sin(PI*x[i]);
	}

	// Дельта 'y'
	double *yDelta = new double[n];
	for (int i = 0; i < n; i++)
	{
		cout << y[i] << " " << yTheoretical[i] << endl;
	}

	for (int i = 0; i < n; i++)
	{
		yDelta[i] = abs(abs(y[i]) - abs(yTheoretical[i]));
	}

	printf("\n Шаг: %lf , Дельта 'y' максимальное: %lf \n", h, MaxVector(yDelta, n));
}