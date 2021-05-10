/*****************************************************************************
 * 				   Modelo SIR				     *
 *	   		         Pedro H Mendes				     *
 ****************************************************************************/

/*****************************************************************************
 *                                 INCLUDES                                  *
 ****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_errno.h>
#include<gsl/gsl_odeiv2.h>

/*****************************************************************************
 *                                DEFINITIONS                                *
 ****************************************************************************/
#define 		N 			1000.   //população
#define			A			0.25    //contrair
#define			B			0.8     //contato com pessoas
#define 		beta 			(A*B)   //definição 
#define 		gamma 			(1./14.)//taxa de recuperar

/*****************************************************************************
 *                                FUNCTIONS                                  *
 ****************************************************************************/
int sir_func(double t, const double y[], double f[], void *params);


/*****************************************************************************
 *                               MAIN PROGRAM                                *
 ****************************************************************************/
int main(void)
{
	const int dim = 3;			 //numero de edos
	const double e_abs = 1.e-8;		 //erro absoluto
	const double e_rel = 1.e-10;		 //erro relativo
	int status; 				 //status da resolucao
	double y[dim]; 				 //solucao
	double pop;  				 //populacao total
	
	double t, tt, tmax; 			 //tempos
	double dt; 				 //dt inicial

	int i0 = 3;				 //i_0

	gsl_odeiv2_system edo_sys; 		 //sistema de edos
	edo_sys.function = sir_func; 		 //eqs a resolver
	edo_sys.dimension = dim; 		 //numero de eqs a resolver
	edo_sys.params = NULL; 			 //parametros para edos

	t = 0.0; 				 //t_0
	tmax = 100.0; 				 //t_f
	dt = 0.001; 				 //dt

	y[0] = N-i0;  				 //ci dos S
	y[1] = i0;  			  	 //ci dos I
	y[2] = 0.0;  				 //ci dos R

	gsl_odeiv2_driver * drv = gsl_odeiv2_driver_alloc_y_new(&edo_sys, gsl_odeiv2_step_rkf45, dt, e_abs, e_rel); 	       //iniciar odeiv

	printf("#r_0 = %lf\n#t  S  I  R  N\n", (beta/gamma)*y[0]);

	while(tt <= tmax)
	{
		status = gsl_odeiv2_driver_apply(drv, &t, tt, y);

		if(status != GSL_SUCCESS) 	 //checando status
		{
			printf("Erro: status = %d\n", status);

			break;
		}

		pop = 0.0;
		pop = y[0]+y[1]+y[2]; 		 //calculando pop

		printf("%lf %lf %lf %lf %lf\n", t, y[0]/N, y[1]/N, y[2]/N, pop/N);  

		tt = tt + dt; 			 //atualiza o tempo
	}
	
	gsl_odeiv2_driver_free(drv); 		 //limpa o odeiv

	return 0;
}

/*****************************************************************************
 * 				SIR EQUATIONS				     *
 ****************************************************************************/
int sir_func(double t, const double y[], double f[], void *params)
{
	f[0] = -(beta*y[0]*y[1])/N; 		 	 //dS/dt
	f[1] = (beta*y[0]*y[1])/N - gamma*y[1]; 	 //dI/dt
	f[2] = gamma*y[1]; 			 	 //dR/dt

	return GSL_SUCCESS;
}


