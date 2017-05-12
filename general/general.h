#pragma once

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <clocale>


// TODO: 

const double PI = atan(1.0) * 4; //Константа Pi
const double G = 6.67300E-11; //Константа Гравитация

double MaxVector(double *y, int length);
void triangMatr(double** A, double **B, int N);
void Solve(double **A, double *x, int N);
void OutputDescMatr(double** M, int n, int m);
void FillMatrix(
	double **M, //Матрица
	double *f, //заполнения массива f(i)
	double h, // Шаг
	int N,
	double koef // коэффициент
);
void GeneralFunc
(
	double a, // Левая граница
	double b, // Правая граница
	double yFirst,  // Значение функции y(a)
	double yLast, // Значение функции y(b)
	int s // Количество сегментов
);