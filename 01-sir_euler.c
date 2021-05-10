/*****************************************************************************
 *                                 Modelo SIR                                *
 *                               Pedro H Mendes                              *
 ****************************************************************************/

/*****************************************************************************
 *                                 INCLUDES                                  *
 ****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*****************************************************************************
 *                                DEFINITIONS                                *
 ****************************************************************************/
#define			N 			1000
#define                 A                       0.25    //contrair
#define                 B                       1.      //contato com pessoas

/*****************************************************************************
 *                                FUNCTIONS                                  *
 ****************************************************************************/
double S_func(double S, double I, double beta);
double I_func(double S, double I, double beta, double gamma);
double R_func(double I, double gamma);

/*****************************************************************************
 *                               MAIN PROGRAM                                *
 ****************************************************************************/
int main(void)
{
	double t, tmax, dt;
	double s, i, r;
	double s_n, i_n, r_n;
	double beta, gamma;
	int i0 = 3;

	beta  = (A*B);
	gamma = (1./14.);
		
	s = N-i0;
	i = i0;
	r = 0;

	dt = 0.001;
	t = 0.;
	tmax = 100.;

	printf("#R0 = %lf\n #t, s, i, r, sum\n", (beta/gamma)*s);

	while(t < tmax)
	{
		s = s + S_func(s, i, beta)*dt;
		i = i + I_func(s, i, beta, gamma)*dt;
		r = r + R_func(i, gamma)*dt;

		printf("%lf  %lf  %lf  %lf %lf\n", t, (s/N), (i/N), (r/N), (s+i+r)/N);
		
		t = t + dt;
	}
	
	return 0;
}

/*****************************************************************************
 *                              SIR EQUATIONS                                *
 ****************************************************************************/
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
