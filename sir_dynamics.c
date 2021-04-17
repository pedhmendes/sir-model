//////////////////////
/////////SIR//////////
/////COM DINAMICA/////
/////PEDRO MENDES/////
//////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<gsl/gsl_rng.h>

/*****DEFINICOES*****/
#define L 100
#define L2 (L*L) // tamanho da matriz
#define tmax 100
#define P 750//numero de pessoas na matriz
#define i_0 50//numero inicial de infectados
#define min_recovery_time 20 //tempo minimo para recuperacao
#define max_recovery_time 25 //tempo maximo para recuperação
#define rec_prob 0.5 //probabilidade de recuperacao

/*****VARIAVEIS GLOBAIS*****/
int x[L][L]; //rede quadrada 
int ii[P], jj[P]; //posição de memoria pessoa
int infect_time[P]; //dias de contaminacao
int s_t, i_t, r_t; //soma de todos

/*****FUNCOES*****/
void initialize(unsigned long int seed);
void start_infection(unsigned long int seed);
void counter(void);
void random_walker(int i,int passo);
void gnuplot(void);
void infect(void);
void recovery(void);
void recovery_prob(double prob_rnd);

int main ()
{
	unsigned long int seed = 0;
	int i, t;
	int passo;
	FILE *temp_dat;
	int pop;
	double prob_rnd;

	gsl_rng *mt;
	mt = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(mt, seed);

	initialize(seed);
	counter();
	pop = s_t+i_t+r_t;

	temp_dat = fopen("t_serie.dat", "w");
	fprintf(temp_dat,"#t s i r pop\n");
	fprintf(temp_dat,"0 %d %d %d %d\n", s_t, i_t, r_t, pop);
	
	printf("set palette defined (0.0 'black', 1.0 'blue', 2.0 'red', 4.0 'green')\n");
	printf("set title 't = 0'\n");
	gnuplot();

	for(t=1; t<=tmax; t++)
	{
		printf("set title 't = %d'\n", t);

		for(i=0; i<P; i++)
		{
			passo = gsl_rng_uniform_int(mt, 8);
			random_walker(i,passo);
		}

		prob_rnd = gsl_rng_uniform(mt);

		infect();
//		recovery_prob(prob_rnd);
		recovery();
		gnuplot();
		counter();
		pop = 0;
		pop = s_t+i_t+r_t;

		fprintf(temp_dat,"%d %d %d %d %d\n",t , s_t, i_t, r_t, pop);

		if(t == 15)
		{
			start_infection(seed);
		}
	}

	printf("pause 5\n");

	fclose(temp_dat);
	gsl_rng_free(mt);
	return 0;
}

void initialize(unsigned long int seed)
{
	int i, j;
	int i_aux;

	gsl_rng *mt;
	mt = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(mt, seed);

	for(i=0; i<L; i++)
	{
		for(j=0; j<L; j++)
		{
			x[i][j] = 0;
		}
	}

	for(i=0; i<P; i++)
	{
		infect_time[i] = 0;
	}
	
	for(i=0; i<P; i++)
	{
		ii[i] = gsl_rng_uniform_int(mt, L);
		jj[i] = gsl_rng_uniform_int(mt, L);

		x[ii[i]][jj[i]] = 1; 
	}

/*
	for(i=0; i<i_0; i++)
	{
		i_aux = gsl_rng_uniform_int(mt, P);
		x[ii[i_aux]][jj[i_aux]] = 2;
	}
*/
	gsl_rng_free(mt);

	return;
}

void start_infection(unsigned long int seed)
{
	int i, i_aux;

	gsl_rng *mt;
	mt = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(mt, seed);

	for(i=0; i<i_0; i++)
	{
		i_aux = gsl_rng_uniform_int(mt, P);
		x[ii[i_aux]][jj[i_aux]] = 2;
	}
	
	gsl_rng_free(mt);

	return;
}

void counter(void)
{
	int i;
	int number = 0;

	s_t = 0;
	i_t = 0;
	r_t = 0;

	for(i=0; i<P; i++)
	{
		number = x[ii[i]][jj[i]];

		if(number == 1)
		{
			s_t = s_t + 1;
		}
		else if(number == 2)
		{
			i_t = i_t + 1;
		}
		else if(number == 3)
		{
			r_t = r_t + 1;
		}
	}
	
	return;
}

void random_walker(int i,int passo)
{
	int i_old, j_old;
	int i_aux, j_aux;
	int x_old;

	i_old = ii[i];
	j_old = jj[i];

	i_aux = ii[i];
	j_aux = jj[i];

	x_old = x[i_old][j_old];
	x[i_old][j_old] = 0;

	switch (passo)
	{
		case 0:
			i_aux = (i_aux==0 ? (L-1) : i_aux -1);
			j_aux = (j_aux==0 ? (L-1) : j_aux -1);
		break;
		case 1:
			i_aux = (i_aux==0 ? (L-1) : i_aux -1);
		break;
		case 2:
			i_aux = (i_aux==0 ? (L-1) : i_aux -1);
			j_aux = (j_aux==(L-1) ? 0 : j_aux +1);
		case 3:
			j_aux = (j_aux==0 ? (L-1) : j_aux -1);
		break;
		case 4:
			j_aux = (j_aux==(L-1) ? 0 : j_aux +1);
		break;
		case 5:
			i_aux = (i_aux==(L-1) ? 0 : i_aux +1);
			j_aux = (j_aux==0 ? (L-1) : j_aux -1);
		break;
		case 6:
			i_aux = (i_aux==(L-1) ? 0 : i_aux +1);
		break;
		case 7:	
			i_aux = (i_aux==(L-1) ? 0 : i_aux +1);
			j_aux = (j_aux==(L-1) ? 0 : j_aux +1);
		break;
	}

	if(x[i_aux][j_aux] != 0)
	{
		i_aux = i_old;
		j_aux = j_old;
	}

	ii[i] = i_aux;
	jj[i] = j_aux;

	x[i_aux][j_aux] = x_old;

	return;

/********************
********0|1|2********
********3|*|4********
********5|6|7********
********************/
}

void gnuplot(void)
{
	int i, j;

	printf("set xrange [0:%d]\nset yrange [0:%d]\n", (L-1), (L-1));
	printf("set cbrange [0:3]\n");
	printf("unset xtics\nunset ytics\n");
	printf("unset colorbox\n");
	printf("set size square\n");
	printf("set key off\n");
	printf("plot \"-\" matrix w image\n");

	for(j=0;j<L;j++)
	{
		for(i=0;i<L;i++)
		{
			printf("%d ",x[i][j]);
		}
		printf("\n");
//		fflush(stdout);
	}
	
	printf("\n\n\n");
	printf("e\n");
//	printf("e\npause 0.1\n");
//	fflush(stdout);

	return;
}

void infect(void)
{
	int i, j;
	int i_aux, j_aux;
	int n[8];

	for(i=0; i<P; i++)
	{
		i_aux = ii[i];
		j_aux = jj[i];

		n[0] = x[(i_aux==0 ? (L-1) : i_aux -1)][(j_aux==0 ? (L-1) : j_aux -1)];
		n[1] = x[(i_aux==0 ? (L-1) : i_aux -1)][j_aux];
		n[2] = x[(i_aux==0 ? (L-1) : i_aux -1)][(j_aux==(L-1) ? 0 : j_aux +1)];
		n[3] = x[i_aux][(j_aux==0 ? (L-1) : j_aux -1)];
		n[4] = x[i_aux][(j_aux==(L-1) ? 0 : j_aux +1)];
		n[5] = x[(i_aux==(L-1) ? 0 : i_aux +1)][(j_aux==0 ? (L-1) : j_aux -1)];
		n[6] = x[(i_aux==(L-1) ? 0 : i_aux +1)][j_aux];
		n[7] = x[(i_aux==(L-1) ? 0 : i_aux +1)][(j_aux==(L-1) ? 0 : j_aux +1)];

		if(n[0]==2 || n[1]==2 || n[2]==2 || n[3]==2 || n[4]==2 || n[5]==2 || n[6]==2 || n[7]==2)
		{
			if(x[i_aux][j_aux] != 3)
			{
				x[i_aux][j_aux] = 2;
			}
		}	
	}

	return;

/********************
********0|1|2********
********3|*|4********
********5|6|7********
********************/
}

void recovery(void)
{
	int i, j;

	for(i=0; i<P; i++)
	{
		if(x[ii[i]][jj[i]] == 2)
		{
			infect_time[i] = infect_time[i] + 1;
		
			if(infect_time[i] > max_recovery_time)
			{
				x[ii[i]][jj[i]] = 3;
			}
		}
	}
}

void recovery_prob(double prob_rnd)
{
	int i, j;

	for(i=0; i<P; i++)
	{
		if(x[ii[i]][jj[i]] == 2)
		{
			infect_time[i] = infect_time[i] + 1;
		
			if(infect_time[i] > min_recovery_time && infect_time[i] <= max_recovery_time && prob_rnd > rec_prob)
			{
				x[ii[i]][jj[i]] = 3;
			}

			else if(infect_time[i] > max_recovery_time)
			{
				x[ii[i]][jj[i]] = 0;
			}
		}
	}
}
