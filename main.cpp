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

	double koef; // Коэффициент

	printf("y'' = ((-1)*((G*time[i] * time[i]) / 2)) + C1*time[i] + C2; \n");

	printf("Введите количество сегментов: ");
	scanf_s("%d", &s);

	int k = s - 1; // количество точек, не включая границы

	long int n = s + 1; // Количество всех точек, включая границы

	double *y_full = new double[n]; // полный y(численное решение)-вектор
	double *y_forMatrix = new double[k]; // y(численное решение)-вектор для умножения матрицы


	double *yt_full = new double[n];  // полный y(точное решение)-вектор
	double *yt_forMatrix = new double[k];  // y(точное решение)-вектор для матрицы
	double *approx = new double[k]; // Для аппроксимации

	y_full[s] = 0; // Значение функции y(b) или когда тело уже упало на землю


	cout << "Введите время: ";
	cin >> T;

	double h = (T - a) / s; // Шаг

	cout << endl << "Введите y(" << a << ") (значение высоты): ";
	cin >> y_full[0]; // Значение функции y(a) или высота H

	cout << endl << "Введите коэффициент: ";
	cin >> koef;
	
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
			f[i] = (G * (-1)) - (y_full[0] / (h*h))  + ( (koef*y_full[0] )/(2*h) );
		}
	}

	double** A = new double*[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new double[M];
	}

	printf("Заполнение матрицы . . . \n");
	FillMatrix(A, f, h, N, koef);
	//OutputDescMatr(A, N, M);

	printf("Решение метода Гаусса . . . \n");
	Solve(A, y_forMatrix, N);

	for (int i = 0; i < k; i++)
	{
		y_full[i + 1] = y_forMatrix[i];
	}

	double C1 = (((G*T*T) / 2) - y_full[0]) / T;
	double C2 = y_full[0];

	for (int i = 0; i < n; i++)
	{
		yt_full[i] = ((-1)*((G*time[i] * time[i]) / 2)) + C1*time[i] + C2;
	}
	for (int i = 0; i < k; i++)
	{
		yt_forMatrix[i] = yt_full[i + 1];
	}

	cout << endl;
	double *yDelta = new double[n]; // Практическая погрешность

	for (int i = 0; i < n; i++)
	{
		yDelta[i] = abs(abs(y_full[i]) - abs(yt_full[i]));
	}

	printf("\n Шаг: %lf , практическая погрешность (только при коэффициенте равным 0): %lf \n", h, MaxVector(yDelta, n));

	/*for (int i = 0; i < n; i++)
	{
		cout << "y[" << time[i] << "] = " << y_full[i] << "\t" << "yt[" << time[i] << "] = " << yt_full[i] << endl;
	} cout << endl;*/

	cout << endl << "Проверка численного решения" << endl;
	checkFillMatrix(A, y_forMatrix, f, approx, N);
	double max_approx = MaxVectorAbs(approx, k);
	cout << endl << "Аппроксимация ( max|Ау-f| ): " << max_approx << endl;
	/*cout << endl << "Проверка точного решения (только при коэффициенте равным 0)" << endl;
	checkFillMatrix(A, yt_forMatrix, f, approx, N); cout << endl;*/


	for (int i = 0; i < n; i++)
	{
		j["time"][i] = time[i];
		j["y"][i] = y_full[i];
		j["yt"][i] = yt_full[i];
	}


	ofstream fout("data.json"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	fout << "data = '" << j << "';"; // запись строки в файл
	fout.close(); // закрываем файл

	//cout << j;
}