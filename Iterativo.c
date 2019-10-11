#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/*	EXERCÍCIO DA DISCIPLINA DE FÍSICA NUCLEAR E DE PARTÍCULAS ELEMENTARES (FSC5528) DA UNIVERSIDADE FEDERAL DE SANTA CATARINA (USFSC)
 				REALIZADO POR MATEUS TOMAZINI KINASZ, MATRÍCULA 08147037  */

main(void){
	
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

//==========================================================================================	
	//input do E em MeV
  long double E=10;
//==========================================================================================  

  //Altera o valor da energia para ficar dentro do poço 
  if (E <= -V0 || E > 0){
  	E = -V0 + 0.00001;
  }

	long double k1=sqrt(2*m*(E+V0))/hc;
  long double k2=sqrt(-2*m*E)/hc;

		  
	if ( k1/tan(k1*R) + k2 > 0.000001 ){
  	do { 
  		
  		E = E + 0.0001;
  		k1=sqrt(2*m*(E+V0))/hc;
  		k2=sqrt(-2*m*E)/hc;
 		
  	} while( k1/tan(k1*R) + k2  >= 1e-13 );
  }	else {
  	do {
  	
  		E = E - 0.0001;
  		k1=sqrt(2*m*(E+V0))/hc;
  		k2=sqrt(-2*m*E)/hc;
  		
  	} while( k1/tan(k1*R) + k2  <= 1e-13 );
  }
  	
  printf("\n\nA energia de ligação dos nucleons do núcleo de deutério é %.4Lf MeV\n\n",E); //(valor encontrado -2.713

}
