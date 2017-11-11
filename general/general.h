﻿#pragma once

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <clocale>

using namespace std;


// TODO: 

const double PI = atan(1.0) * 4; //Константа Pi

double MaxVector(double *y, int length);
void triangMatr(double** A, double **B, int N);
void Solve(double **A, double *x, int N);
void OutputDescMatr(double** M, int n, int m);
void FillMatrix(
	double **M, 
	double *f, 
	double h, 
	int N
);
void GeneralFunc
(
	double a, // Левая граница
	double b, // Правая граница
	double yFirst,  // Значение функции y(a)
	double yLast, // Значение функции y(b)
	int s // Количество сегментов
);