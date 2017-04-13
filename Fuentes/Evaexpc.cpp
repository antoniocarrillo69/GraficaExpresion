//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para la evalución la expresión puesta como una cadena                              //
// Revisión: 3 de Noviembre del 2003                                                        //
//                                                                                          //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.dynamics.unam.edu                                                      //
// Página:   http://www.dynamics.unam.edu/acl                                               //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

         
#include <stdio.h>
#include "Evaexpc.hpp"
#include "Calnpol.hpp"
#include "Cadenas.hpp"


// Expresion a revisar y evualuar
int Evalua_expresion_cadena::Expresion_cadena(const char *exp)
{ 
   Analizador_sintactico as;
   if (exp_not_pol) delete []exp_not_pol;
      
   exp_not_pol = as.Asigna_puntero(1001);
   Error = 0;

   // Realiza el analisis sintactico de la expresion
   as.Analiza_expresion_tipo_01(exp);
   if (!as.Numero_errores()) 
   {
      char xcad1[1001], xcad2[1001];
      unsigned int pos;
      // Retorna la cadena en notacion polaca
      as.Retorna_expresion(exp_not_pol,POSTORDEN,1000);
      // Remplaza la variable x por la variable de memoria uno
      while(as.Busca_cadena(exp_not_pol,"|x|",pos)) {
         as.Substr(exp_not_pol,0,pos,xcad1);
         as.Substr(exp_not_pol,pos+3,1000,xcad2);
         sprintf(exp_not_pol,"%s|M01|%s",xcad1,xcad2);
      }
   } else Error = as.Retorna_codigo_error(0);
   return Error;   
}


// Evalua la expresion tomando como datos los elementos del arreglo ARR que son NUM
int Evalua_expresion_cadena::Evalua_expresion(ldouble *arr, long int num)
{
   if (Error) return Error;
   long int i; 
   
   Calculadora_notacion_polaca cnp;
   
   // Obtiene el resultado de la expresion polaca
   for (i = 0; i < num ; i++) {
       // Actualiza el valor a calcular
       cnp.Asigna_valor(0,*arr);
       // Evalua la expresion en notacion polaca
       *arr = cnp.Evalua(exp_not_pol);
       arr++;
   } 

   return Error;
}



// Evalua una expresion EXP regresando el valor numerico de esta y la cadena con dicho valor en RES
ldouble Evalua_expresion_cadena::Evalua_expresion(const char *exp, char *res)
{
   ldouble nres = 0;
   res[0] = 0;
   nres = Evalua_expresion(exp);
   sprintf(res,"%1.16Lg",nres);
   return nres;
}


// Evalua una expresion EXP regresando el valor numerico de esta
ldouble Evalua_expresion_cadena::Evalua_expresion(const char *exp)
{
   ldouble nres = 0;
   Expresion_cadena(exp);
   if (!Error)
   {
      // Obtiene el resultado de la expresion polaca
      Calculadora_notacion_polaca cnp;
      nres = cnp.Evalua(exp_not_pol);
   }
   return nres;
}

/*
int main(void)
{
   ldouble a;
   ldouble b[]={1.0,2.0,3.0,4.0,5.0};
   Evalua_expresion_cadena ev;
   ev.Expresion_cadena("X=x*x");
   ev.Evalua_expresion(b, 5);
   for (int i=0;i<5;i++) printf("%Lf\n",b[i]);
   a = ev.Evalua_expresion("X=32");
   printf("%Lf",a);
   return 0;
}
*/

