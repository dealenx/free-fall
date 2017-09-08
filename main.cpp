﻿#include "./general/general.h"
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

	double *time = new double[n];

	for (int i = 0; i < n; i++) {
		time[i] = i * (b / s);
		//cout << "t = " << time[i] << endl;
	}

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
			f[i] = ( G * (-1) ) + (( ((koef * h) - 1) / (2*h*h)  ) * y[0]);
		}
		if (i == n - 1)
		{
			f[i] = (G * (-1)) - ((((koef * h) + 1) / (2 * h*h))* y[s]);
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
	OutputDescMatr(A, N, M);

	double *yy = new double[k];

	printf("Решение метода Гаусса . . . \n");
	Solve(A, yy, N);

	for (int i = 0; i < N; i++)
	{
		y[i + 1] = yy[i];
	}


	/*
	for (int i = 0; i < n; i++)
	{
		cout << "y[" << time[i] << "] = " << y[i] << " ";
	}*/
	for (int i = 0; i < n; i++)
	{
		j["time"][i] = time[i];
		j["y"][i] = y[i];
	}

	ofstream fout("data.json"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	fout << "data = '" << j << "';"; // запись строки в файл
	fout.close(); // закрываем файл

	//cout << j;


}