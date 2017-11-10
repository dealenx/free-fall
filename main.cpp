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
	const int N = k, M = s; // Размерность матрицы

	cout << "h = " << h << " b = " << b << "a = " << a << endl;

	double *y_full = new double[n]; // полный y(численное решение)-вектор
	double *y_forMatrix = new double[k]; // y(численное решение)-вектор для умножения матрицы


	double *yt_full = new double[n];  // полный y(точное решение)-вектор
	double *yt_forMatrix = new double[k];  // y(точное решение)-вектор для матрицы


	double C1 = ( G * b) - (yFirst / b);
	double C2 = yFirst;

	double *time = new double[n];

	for (int i = 0; i < n; i++) {
		time[i] = i * (b / s);
		//cout << "t = " << time[i] << endl;
	}

	y_full[0] = yFirst; y_full[s] = yLast;
	yt_full[0] = yFirst; yt_full[s] = yLast;

	for (int i = 1; i < n - 1; i++)
	{
		yt_full[i] = (G * (-1) * time[i] * time[i]) + (C1 * time[i]) + C2;
	}
	for (int i = 0; i < k; i++)
	{
		yt_forMatrix[i] = yt_full[i+1];
	}

	
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
			f[i] = (G * (-1)) + ( (koef*y_full[0]) /(2*h) ) - ( y_full[0]/(h*h) ) ;
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
	

	printf("Решение метода Гаусса . . . \n");
	Solve(A, y_forMatrix, N);
	OutputDescMatr(A, N, M);
	//A*yy-f


	for (int i = 0; i < k; i++)
	{
		y_full[i + 1] = y_forMatrix[i];
	}

	cout << "Проверка численного решения" << endl;
	checkFillMatrix(A, y_forMatrix, f, approx, N);
	cout << "Проверка точного решения" << endl;
	checkFillMatrix(A, yt_forMatrix, f, approx, N);
	for (int i = 0; i < n; i++)
	{
		cout << "y[" << time[i] << "] = " << y_full[i] << " ";
	}

	
	for (int i = 0; i < n; i++)
	{
		j["time"][i] = time[i];
		j["y"][i] = y_full[i];
		j["yt"][i] = yt_full[i];
	}


	ofstream fout("data.json"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	fout << "data = '" << j << "';"; // запись строки в файл
	fout.close(); // закрываем файл

	cout << j;


}