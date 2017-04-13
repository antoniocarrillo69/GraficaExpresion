#include "Evaexpc.hpp"
#include "Calnpol.hpp"
#include <stdio.h>


/*
int main(void)
{
   const char *Exp[] = {
      "X=4554*(4/3)+3233",
      "X=32723832*3223*2323*233232*23",
      "X=sinl(M_PI_4)",
      "X=43232+32323+232323+2323+232323",
      "X=23+23232*(1221-3232)*121/4"
   };

   
   double l;
   int i;
   
   Evalua_expresion_cadena a;
   for(i = 0; i < 5; i++)
   {      
      l = a.Evalua_expresion(Exp[i]);
      printf("\nEvaluacion de la %s es %lf\n",Exp[i],l);
   }
   return 0;
}
*/


// Programa para graficar una función solicitada al usurio en modo texto
// Por ejemplo: y=2*x+x*x
// Autor Antonio Carrillo Ledesma
// http://www.mmc.igeofcu.unam.mx/acl/


#include <stdio.h>

#define Ren 20
#define Col 80



int main(void)
{
   double lim=10.0;
   // Limites de la ventana de graficación
   double a = -lim, b = -lim, c = lim, d = lim;
   // Divisiones a la ventana
   double npv = 200;

   int i, j, px, py;
   double x,y;
   
   Analizador_sintactico as;
   Calculadora_notacion_polaca cp;
      
   char *exp_not_pol = as.Asigna_puntero(1001);
   char cad[1000], xcad1[1000], xcad2[1000];
   const char *bus="|x|";
   unsigned int pos;
   
   printf("\nDame la expresion a graficar, por ejemplo: y=x*x*x+2*x\n");
   scanf("%s",cad);
   printf("Expesion: %s\n",cad);
   


   // Realiza el analisis sintactico de la expresion
   as.Analiza_expresion_tipo_01(cad);
   if (as.Numero_errores()) {
      printf("\n\nError en la expresion\n");
      return 1;
   }      
   
   
   // Calculos de escalas
   double escx = Col / npv;
   double escy = Ren / npv;
   double escrx = npv / (c - a);
   double escry = npv / (d - b);
   // Arreglo de visualizacion en modo textto
   char v[Ren][Col];
   for (i = 0; i < Ren; i++)
      for (j = 0; j < Col; j++) v[i][j] = ' ';

   // Calculo de la funcion en cada punto de la malla
   for (x = a; x <= c; x += ((c - a) / npv) )
   {
      // Retorna la expresion en notacion polaca
      as.Retorna_expresion(exp_not_pol,POSTORDEN,1000);
      // Remplaza la variable x por el valor de x
      while(as.Busca_cadena(exp_not_pol,bus,pos)) {
         as.Substr(exp_not_pol,0,pos,xcad1);
         as.Substr(exp_not_pol,pos+3,1000,xcad2);
         sprintf(exp_not_pol,"%s|%lf|%s",xcad1,x,xcad2);
      }
      // Visualiza la expresion despues de remplazar el valor de x
      //printf("\n%s",exp_not_pol);
      // Evalua la expresion en notacion polaca
      y=cp.Evalua(exp_not_pol);
      
      
      px = (int) ((x - a) * escrx * escx);
      py = (int) (Ren - (((y - b) * escry) * escy));
      // Grafica el punto si esta dentro de la ventana
      if (px >= 0 && px < Col && py >= 0 && py < Ren) v[py][px] = '*';
   }
   // Visualiza el grafico en modo texto
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) printf ("%c", v[i][j]);
      printf("\n");
   }

}
