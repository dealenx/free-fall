#include "./general/general.h"
#include "./headers/json.hpp"


using namespace std;
using json = nlohmann::json;



void main() {
	setlocale(LC_CTYPE, "rus");

	
	json j;

	double a = 0; // Левая граница
	double b; // Правая граница (конечное время)
	

	double yFirst; // Значение функции y(a) или высота
	double yLast = 0; // Значение функции y(b)

	printf("Введите время: ");
	scanf_s("%lf", &b);

	printf("\n");
	 
	printf("Введите высоту: ");
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
	cout << "h = " << h << " b = " << b << "a = " << a << endl;

	double *y = new double[n];

	double *yt = new double[n];


	double C1 = ( G * b) - (yFirst / b);
	double C2 = yFirst;

	double *time = new double[n];

	for (int i = 0; i < n; i++) {
		time[i] = i * (b / s);
		//cout << "t = " << time[i] << endl;
	}

	y[0] = yFirst; y[s] = yLast;
	yt[0] = yFirst; yt[s] = yLast;

	for (int i = 1; i < n - 1; i++)
	{
		yt[i] = (G * (-1) * time[i] * time[i]) + (C1 * time[i]) + C2;
	}

	const int N = k, M = s; // Размерность матрицы
	double *approx = new double[N]; // Для аппроксимации

	double *x = new double[n];

	for (int i = 0; i < n; i++)
	{
		x[i] = a + (i*h);
	}
	printf("\n");

	double *f = new double[s];

	for (int i = 0; i < n; i++)
	{
		f[i] = G * (-1);

		if (i == 0)
		{
			f[i] = (G * (-1)) + ( (koef*y[0]) /(2*h) ) - ( y[0]/(h*h) ) ;
		}
		if (i == n - 1)
		{
			f[i] = (G * (-1));
		}
	}


	double** A = new double*[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new double[M];
	}

	printf("Заполнение матрицы . . . \n");
	cout << "h = " << h << endl;
	cout << "a = " << a << " b = " << b << endl;
	cout << "yFirst = " << yFirst << " yLast = " << yLast << endl;

	FillMatrix(A, f, h, N, koef);
	checkFillMatrix(A, yt, f, approx, N);


	OutputDescMatr(A, N, M);

	double *yy = new double[k];

	printf("Решение метода Гаусса . . . \n");
	Solve(A, yy, N);

	//A*yy-f


	for (int i = 0; i < N; i++)
	{
		y[i + 1] = yy[i];
	}


	
	for (int i = 0; i < n; i++)
	{
		cout << "y[" << time[i] << "] = " << y[i] << " ";
	}

	
	for (int i = 0; i < n; i++)
	{
		j["time"][i] = time[i];
		j["y"][i] = y[i];
		j["yt"][i] = yt[i];
	}


	ofstream fout("data.json"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	fout << "data = '" << j << "';"; // запись строки в файл
	fout.close(); // закрываем файл

	cout << j;


}