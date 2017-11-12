#include "./general/general.h"
#include "./headers/json.hpp"


using namespace std;
using json = nlohmann::json;

void main() {
	setlocale(LC_CTYPE, "rus");

	json j;

	//y = sin(PI*x)
	//y'' = -G

	double a = 0; // Левая граница
	double T; // Правая граница
	int s; // Количество сегментов

	printf("y'' = ((-1)*(PI)^2)*sin(PI*x) \n");

	printf("Введите количество сегментов: ");
	scanf_s("%d", &s);

	int k = s - 1; // количество точек, не включая границы

	long int n = s + 1; // Количество всех точек, включая границы

	double *y = new double[n];

	y[s] = 0; // Значение функции y(b) или когда тело уже упало на землю


	cout << "Введите время: ";
	cin >> T;

	double h = (T - a) / s; // Шаг

	cout << endl << "Введите y(" << a << ") (значение высоты): ";
	cin >> y[0]; // Значение функции y(a) или высота H
	
	double *time = new double[n];

	const int N = k, M = s; // Размерность матрицы

	double *x = new double[n];

	for (int i = 0; i < n; i++)
	{
		x[i] = a + (i*h);
	}

	for (int i = 0; i < n; i++) {
		time[i] = i * (T / s);
	}
	printf("\n");

	double *f = new double[s];

	for (int i = 0; i < k; i++)
	{
		f[i] = G * (-1);

		if (i == 0)
		{
			f[i] = (G * (-1)) - (y[0] / (h*h));
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

	for (int i = 0; i < k; i++)
	{
		y[i + 1] = yy[i];
	}

	double C1 = (((G*T*T) / 2) - y[0]) / T;
	double C2 = y[0];

	double *yt = new double[n]; // Теоритическая 'y'

	for (int i = 0; i < n; i++)
	{
		yt[i] = ((-1)*((G*time[i] * time[i]) / 2)) + C1*time[i] + C2;
	}

	cout << endl;
	double *yDelta = new double[n]; // Практическая погрешность

	for (int i = 0; i < n; i++)
	{
		yDelta[i] = abs(abs(y[i]) - abs(yt[i]));
	}
	cout << endl;
	printf("\n Шаг: %lf , Дельта 'y' максимальное: %lf \n", h, MaxVector(yDelta, n));

	for (int i = 0; i < n; i++)
	{
		cout << "y[" << time[i] << "] = " << y[i] << " " << "yt[" << time[i] << "] = " << yt[i] << " ";
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