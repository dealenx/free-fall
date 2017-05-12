#include "./general/general.h"

using namespace std;



void main() {
	setlocale(LC_CTYPE, "rus");
	
									 //y = sin(PI*x)
									 //y'' = (-1)*(PI)*(PI)*sin(PI*x)

	double a; // Левая граница
	double b; // Правая граница
	int n; // Сколько раз вводить сегменты
	

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

	printf("Сколько раз вы будете вводить сегменты: ");
	scanf_s("%d", &n);

	int *s = new int[n]; // Количество сегментов

	for (int i = 0; i < n; i++)
	{
		printf("Введите количество сегментов для s[%d]: ", i);
		scanf_s("%d", &s[i]);
	}

	
	for (int i = 0; i < n; i++)
	{
		printf("\n С сегментом s[%d]:%lf  . . . ", i, s[i]);
		GeneralFunc(a, b, yFirst, yLast, s[i]);
	}
}