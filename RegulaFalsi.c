#include <stdio.h>
#include <math.h>

/*	EXERCÍCIO DA DISCIPLINA DE FÍSICA NUCLEAR E DE PARTÍCULAS ELEMENTARES (FSC5528) DA UNIVERSIDADE FEDERAL DE SANTA CATARINA (USFSC)
 				REALIZADO POR MATEUS TOMAZINI KINASZ, MATRÍCULA 08147037  */

long double f(long double E)
{

  /*Ao aproximar o potencial nucleon-nucleon do núcleo do átomo de deuterio para um poço de potencial quadrado de tamanho R 
		e profundidade V0, e resolvendo a equação de Schrodinger para l=0 obtemos uma equação transcendetal em termos de V0 e R.
		Este programa calcula a energia de ligação do núcleo do átomo de deuterio através da equação transcendental k1/tan(k1*R)=-k2
		onde k1=sqrt(2*m*(E+V0))/hc, k2=sqrt(-2*m*E)/hc, hc e m são definidos abaixo*/

  //constante de planck dividido por 2pi vezes a velocidade da luz no vácuo em MeV.fm (retirado de <http://physics.nist.gov/cgi-bin/cuu/Value?hbcmevf> )
	long double hc = 197.3269788;
  
	//massa do proton em MeV (retirado de <http://physics.nist.gov/cgi-bin/cuu/Value?mpc2mev|search_for=atomnuc!> )
	long double mP = 938.2720813;

	//massa do neutron em MeV (retirado de <http://physics.nist.gov/cgi-bin/cuu/Value?mnc2mev|search_for=atomnuc!>)
	long double mN = 939.5654133;

	//raio R do nucleo do átomo de deuteron em fm (retirado de <http://physics.nist.gov/cgi-bin/cuu/Value?rd|search_for=atomnuc!>)
	long double R = 2.1;	

	//massa reduzida do sistema (469.459150959)
	long double m=(mN*mP)/(mN+mP);

	//Potencial em MeV (profundidade do poço)
	long double V0 = 35;
	
   return sqrt(2*m*(E+V0))/(hc*tan(sqrt(2*m*(E+V0))*R/hc)) + sqrt(-2*m*E)/hc;
}


/*Este é o método da posição falsa, tambem chamado de 'regula falsi', método numérico usado para resolver equações lineares definidas em um intervalo finito, partindo do pressuposto de que haja uma solução em um subintervalo contido no intervalo. E assim, diminuindo o subintervalo em partes cada vez menores, a solução estará onde a função tem sinais opostos, segundo o Teorema do Valor Intermediário. A determinação do tamanho do subintervalo é definida pelo critério de exatidão.

o programa foi retirado de <https://en.wikipedia.org/wiki/False_position_method#Example_code> e ajustado para equação transcendetal do deuterio*/

/* s,t: pontos extremos do intervalo a se procurar
   e: erro relativo
   m: número máximo de iterações */
long double RegulaFalsi(long double s, long double t, long double e, int m)
{
   long double r,fr;
   int n, side=0;
   /* começando com os valores inciais e finais do intervalo */
   long double fs = f(s);
   long double ft = f(t);

   for (n = 0; n < m; n++)
   {

       r = (fs*t - ft*s) / (fs - ft);
       if (fabs(t-s) < e*fabs(t+s)) break;
       fr = f(r);

       if (fr * ft > 0)
       {
         /* fr & ft tem o mesmo sinal, copia r para t */
         t = r; ft = fr;
         if (side==-1) fs /= 2;
         side = -1;
       }
       else if (fs * fr > 0)
       {
         /* fr & fs tem o mesmo sinal, copia r para s */
         s = r;  fs = fr;
         if (side==+1) ft /= 2;
         side = +1;
       }
       else
       {
         /* fr * f_ muito pequeto (praticamente zero) */
         break;
       } 
    }
    return r;
}

int main(void)
{
    printf("%0.4Lf\n", RegulaFalsi(-34, 0, 5E-15, 100)); //(Valor encontrado E = -2.713)
    return 0;
}
