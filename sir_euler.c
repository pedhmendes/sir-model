////////////////////
////////SIR/////////
//////COM EULER/////
////PEDRO MENDES////
////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 209300000

double S_func(double S, double I, double beta);
double I_func(double S, double I, double beta, double gamma);
double R_func(double I, double gamma);

int main ()
{
	double t, tmax, dt;
	double s, i, r;
	double s_n, i_n, r_n;
	double beta, gamma;

/***********dados de teste**********/	
//	beta = 1.4247;             //
//	gamma = 0.14286;           //

/**********dados do brasil*************/
	beta =  0.357145;
	gamma = 0.071429;
		
	s = N-1;
	i = 1;
	r = 0;

//	dt = 0.001;
	dt = 1.;
	t = 0.;
	tmax = 150.;

	printf("#t, s, i, r, sum\n");

	while(t < tmax)
	{
		s = s + S_func(s, i, beta)*dt;
		i = i + I_func(s, i, beta, gamma)*dt;
		r = r + R_func(i, gamma)*dt;

		printf("%lf  %lf  %lf  %lf %lf\n", t, (s/N), (i/N), (r/N), (s+i+r));
		
		t = t + dt;
	}
	
	return 0;
}

double S_func(double S, double I, double beta)
{
	return -((beta*S*I)/N);
}

double I_func(double S, double I, double beta, double gamma)
{
	return ((beta*S*I)/N) - gamma*I;
}

double R_func(double I, double gamma)
{
	return gamma*I;
}	

/*******************************************************
	N eh a populacao brasileira
	N = 209,3 milhoes	

  	r_0 é pra quantas pessoas uma pessoa infectada pode passar o virus
	supondo que r_0 = 5
  
  	beta eh a taxa de infeccao
	segue que r_0 = beta/gamma
  
  	gamma é a taxa de recuperacao
	eh o inverso de dias para recuperacao
	gamma = 1/dias para curar	
	supondo que leve 14 dias pra curar
********************************************************/

