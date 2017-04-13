//////////////////////////////////////////////////////////////////////////////////////////////
// Evalua una expresion en notacion polaca postfija                                         //
// Revisión: 20 de Mayo del 2004                                                            //
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



///////////////////////////////////////////////////////////////
// Usar tipo de conversion para funciones trigonometricas
// Aceptar el operador ^ para potencias
///////////////////////////////////////////////////////////////

          
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Calnpol.hpp"
#include "Pila.hpp"



#ifdef FUNCIONES_DEFINIDAS_USUARIO
// Estas funciones las define el usuario
extern ldouble F_U01(const ldouble x);
extern ldouble F_U02(const ldouble x);
extern ldouble F_U03(const ldouble x);
extern ldouble F_U04(const ldouble x);
extern ldouble F_U05(const ldouble x);
extern ldouble F_U06(const ldouble x);
extern ldouble F_U07(const ldouble x);
extern ldouble F_U08(const ldouble x);
extern ldouble F_U09(const ldouble x);
#endif


// Rutina que recibe un indicador de operacion asi como un numero determinado de operandos para realizar la operacion indicada
ldouble Calculadora_notacion_polaca::Calcula(const unsigned int operacion, const ldouble op1)
{
   ldouble res, xres1;
   // operaciones basicas
   switch (operacion) {
     case 52:
        if (op1 != 0.0) res = 1.0 / op1;
         else res = 0.0, Error_matematico = 1;
        break;
     // Funciones trigonometricas
     case 30:   // Seno
#ifdef __Double__
        res = sin(op1);
#else
        res = sinl(op1);
#endif
        break;
     case 31:   // Coseno
#ifdef __Double__
        res = cos(op1);
#else
        res = cosl(op1);
#endif
        break;
     case 32:   // Tangente
#ifdef __Double__
     res = tan(op1);
#else
     res = tanl(op1);
#endif
        break;
     case 33:   // Arco seno
#ifdef __Double__
        if (op1 >= -1.0 && op1 <= 1.0) res = asin(op1);
#else
        if (op1 >= -1.0 && op1 <= 1.0) res = asinl(op1);
#endif
         else res = 0.0, Error_matematico = 1;
        break;
     case 34:   // Arco coseno
#ifdef __Double__
        if (op1 >= -1.0 && op1 <= 1.0) res = acos(op1);
#else
        if (op1 >= -1.0 && op1 <= 1.0) res = acosl(op1);
#endif
        else res = 0.0, Error_matematico = 1;
        break;
     case 35:   // Arco tangente
#ifdef __Double__
        res = atan(op1);
#else
        res = atanl(op1);
#endif
        break;
     case 36:   // Seno hiperbolico
#ifdef __Double__
        res = sinh(op1);
#else
        res = sinhl(op1);
#endif
        break;
     case 37:   // Coseno hiperbolico
#ifdef __Double__
        res = cosh(op1);
#else
        res = coshl(op1);
#endif
        break;
     case 38:   // Tangente hiperbolico
#ifdef __Double__
        res = tanh(op1);
#else
        res = tanhl(op1);
#endif
        break;
     // Otras funciones
     case 39:   // Valor absoluto
#ifdef __Double__
        res = fabs(op1);
#else
        res = fabsl(op1);
#endif
        break;
     case 40:   // Exponencia e a la x
#ifdef __Double__
        res = exp(op1);
#else
        res = expl(op1);
#endif
        break;
     case 41:   // Logaritmo natural
#ifdef __Double__
        if (op1 > 0.0) res = log(op1);
#else
        if (op1 > 0.0) res = logl(op1);
#endif
         else res = 0.0, Error_matematico = 1;
        break;
     case 42:   // Logaritmo base 10
#ifdef __Double__
        if (op1 > 0.0) res = log10(op1);
#else
        if (op1 > 0.0) res = log10l(op1);
#endif
         else res = 0.0, Error_matematico = 1;
        break;
     case 43:   // Raiz cuadrada de X
#ifdef __Double__
        if (op1 >= 0.0) res = sqrt(op1);
#else
        if (op1 >= 0.0) res = sqrtl(op1);
#endif
         else res = 0.0, Error_matematico = 1;
        break;
     case 44:  // Cuadrado de X
        res = op1 * op1;
        break;
     case 47:  // 10 a la X
#ifdef __Double__
        res = pow(10.0,op1);
#else
        res = powl(10.0,op1);
#endif
        break;
     case 51:   // Factorial de x
        res = 1;
        {
          for(int i = 2; i <= op1; i++) res *= i;
        }
        break;
     case 60:  // Signo de X (1 si X > 0, -1 si X < 0 y 0 si X es cero)
        res =  op1 >= 0.0 ? (op1 == 0.0 ? 0.0 : 1.0) : -1.0;
        break;
     case 61:  // El mayor entero menor o igual a X
#ifdef __Double__
        res = floor(op1);
#else
        res = floorl(op1);
#endif
        break;
     case 62:  // Parte entera de X
#ifdef __Double__
        xres1 = modf(op1,&res);
#else
        xres1 = modfl(op1,&res);
#endif
        break;
     case 63:  // Parte decimal de X
#ifdef __Double__
        res = modf(op1,&xres1);
#else
        res = modfl(op1,&xres1);
#endif
        break;
#ifdef FUNCIONES_DEFINIDAS_USUARIO
     // Funciones definidas por el usuario
     case 80: 
        res = F_U01(op1);
        break;
     case 81: 
        res = F_U02(op1);
        break;
     case 82: 
        res = F_U03(op1);
        break;
     case 83: 
        res = F_U04(op1);
        break;
     case 84: 
        res = F_U05(op1);
        break;
     case 85: 
        res = F_U06(op1);
        break;
     case 86: 
        res = F_U07(op1);
        break;
     case 87: 
        res = F_U08(op1);
        break;
     case 88: 
        res = F_U09(op1);
        break;
#endif        
   }
   return res;
}


// Rutina que recibe un indicador de operacion asi como un numero determinado de operandos para realizar la operacion indicada
ldouble Calculadora_notacion_polaca::Calcula(const unsigned int operacion, const ldouble op1, const ldouble op2)
{
   ldouble res, xres1;
   // operaciones basicas
   switch (operacion) {
     case 45:   // Calcula X  por 2 exponente a la Y
#ifdef __Double__
        res = ldexp(op1,(int) op2);
#else
        res = ldexpl(op1,(int) op2);
#endif
        break;
     case 46:   // X ala Y
        if (op1 == 0.0 && op2 <= 0.0) res = 0.0, Error_matematico = 1;
#ifdef __Double__
         else res = pow(op1,op2);
#else
         else res = powl(op1,op2);
#endif
        break;
     case 50:   // Calcula el modulo de X / Y
#ifdef __Double__
        res = fmod(op1,op2);
#else
        res = fmodl(op1,op2);
#endif
        break;
     case 70:  // Maximo entre X e Y
        res = op1 >= op2 ? op1 : op2;
        break;
     case 71:  // Minimo entre X e Y
        res = op1 <= op2 ? op1 : op2;
        break;
   }
   return res;
}


// Rutina que calcula el valor numerico de una expresion en notacion polaca con separador de operandos el pipe
ldouble Calculadora_notacion_polaca::Evalua(const char *cadena)
{
   Error_matematico = 0;
   if (!cadena[0]) return 0;

   int i = 0, xi = 0, tp;
   ldouble res, op1, op2;
   char xcad[100];
   xcad[0] = 0;

   // Crea la pila con 20 elementos 
   PILA pila(20,NUMERICA);
   while (cadena[i+1]) {
      // Almacena los caracteres dentro de la cadena temporal
      if (cadena[i] == ',') i += 2;
      if (cadena[i] != '|') xcad[xi] = cadena[i], xi++, xcad[xi] = 0;
       else {
         xi = tp = 0, op1 = 0.0, op2 = 0.0;

//////////////////////////////////////////////////////////////////////////////
//         // Asume que es una variable
//         if (Es_caracter_alfabetico(xcad[0]) && strlen(xcad) < 3) goto Etiqueta1;
//////////////////////////////////////////////////////////////////////////////
         
         // Descarto la coma como separador de parametros
         if (xcad[0] == ',' && xcad[1] == 0)  {
             xcad[0] = 0;
             goto Etiqueta2;
         }

         // Revisa si es un numero
         if(Es_caracter_digito(xcad[0])) goto Etiqueta1;

         // Operaciones basicas
         if ((xcad[0] == '+' || xcad[0] == '-' || xcad[0] == '*' || xcad[0] == '/') && xcad[1] == 0) {
            pila.Sacar(op2);
            pila.Sacar(op1);
            if (xcad[0] == '+') res = op1 + op2;
             else if (xcad[0] == '-') res = op1 - op2;
             else if (xcad[0] == '*') res = op1 * op2;
             else {
                if (op2 != 0.0) res = op1 / op2;
                 else {
                   Error_matematico = 1;
                   return 0.0;
                }
             }
            pila.Meter(res);
            xcad[0] = 0;
            goto Etiqueta2;
         }


         // Revisa si es una constante 
         if(xcad[0] == 'M') {
           // Sustitucion de valores en memoria y constantes
            if (!strcmp(xcad,"M_PI"))            tp = 100, res = M_PI;
            else if (!strcmp(xcad,"M_PI_2"))     tp = 100, res = M_PI_2;
            else if (!strcmp(xcad,"M_PI_4"))     tp = 100, res = M_PI_4;
            else if (!strcmp(xcad,"M_1_PI"))     tp = 100, res = M_1_PI;
            else if (!strcmp(xcad,"M_2_PI"))     tp = 100, res = M_2_PI;
            else if (!strcmp(xcad,"M_1_SQRTPI")) tp = 100, res = 1.0/sqrtl(M_PI);
            else if (!strcmp(xcad,"M_2_SQRTPI")) tp = 100, res = M_2_SQRTPI;
            else if (!strcmp(xcad,"M_E"))        tp = 100, res = M_E;
            else if (!strcmp(xcad,"M_LOG2E"))    tp = 100, res = M_LOG2E;
            else if (!strcmp(xcad,"M_LOG10E"))   tp = 100, res = M_LOG10E;
            else if (!strcmp(xcad,"M_LN2"))      tp = 100, res = M_LN2;
            else if (!strcmp(xcad,"M_LN10"))     tp = 100, res = M_LN10;
            else if (!strcmp(xcad,"M01"))        tp = 101, res = MEM[0];
            else if (!strcmp(xcad,"M02"))        tp = 101, res = MEM[1];
            else if (!strcmp(xcad,"M03"))        tp = 101, res = MEM[2];
            else if (!strcmp(xcad,"M04"))        tp = 101, res = MEM[3];
            else if (!strcmp(xcad,"M05"))        tp = 101, res = MEM[4];
            else if (!strcmp(xcad,"M06"))        tp = 101, res = MEM[5];
            else if (!strcmp(xcad,"M07"))        tp = 101, res = MEM[6];
            else if (!strcmp(xcad,"M08"))        tp = 101, res = MEM[7];
            else if (!strcmp(xcad,"M09"))        tp = 101, res = MEM[8];
            else if (!strcmp(xcad,"M10"))        tp = 101, res = MEM[9];
           if (tp) {
              pila.Meter(res);
              xcad[0] = 0;
              tp = 0;
              goto Etiqueta2;
           }
         }


         // Funciones que requieren un solo parametro
         if (!strcmp(xcad,"sinl"))   tp = 30;  // Seno
          else if (!strcmp(xcad,"cosl"))   tp = 31;  // Coseno
          else if (!strcmp(xcad,"tanl"))   tp = 32;  // Tangente
          else if (!strcmp(xcad,"asinl"))  tp = 33;  // Arco seno
          else if (!strcmp(xcad,"acosl"))  tp = 34;  // Arco coseno
          else if (!strcmp(xcad,"atanl"))  tp = 35;  // Arco tangente
          else if (!strcmp(xcad,"sinhl"))  tp = 36;  // Seno hiperbolico
          else if (!strcmp(xcad,"coshl"))  tp = 37;  // Coseno hiperbolico
          else if (!strcmp(xcad,"tanhl"))  tp = 38;  // Tangente hiperbolico
          else if (!strcmp(xcad,"absl"))   tp = 39;  // Valor absoluto
          else if (!strcmp(xcad,"expl"))   tp = 40;  // Exponencia e a la X
          else if (!strcmp(xcad,"logl"))   tp = 41;  // Logaritmo natural
          else if (!strcmp(xcad,"log10l")) tp = 42;  // Logaritmo base 10
          else if (!strcmp(xcad,"sqrtl"))  tp = 43;  // Raiz cuadrada
          else if (!strcmp(xcad,"sqrl"))   tp = 44;  // Cuadrado de X
          else if (!strcmp(xcad,"factl"))  tp = 51;  // Factorial de X
          else if (!strcmp(xcad,"invl"))   tp = 52;  // Inverso de X
          else if (!strcmp(xcad,"sigl"))   tp = 60;  // Signo de X (1 si X > 0, -1 si X < 0 y 0 si X es cero)
          else if (!strcmp(xcad,"floorl")) tp = 61;  // El mayor entero menor o igual a X
          else if (!strcmp(xcad,"trcl"))   tp = 62;  // Parte entera de X
          else if (!strcmp(xcad,"decl"))   tp = 63;  // Parde decimal de X
          else if (!strcmp(xcad,"pow10l")) tp = 47;  // X por 10 a la Y
#ifdef FUNCIONES_DEFINIDAS_USUARIO
          else if (!strcmp(xcad,"F_U01"))  tp = 80;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U02"))  tp = 81;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U03"))  tp = 82;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U04"))  tp = 83;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U05"))  tp = 84;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U06"))  tp = 85;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U07"))  tp = 86;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U08"))  tp = 87;  // Función definida por el usuario
          else if (!strcmp(xcad,"F_U09"))  tp = 88;  // Función definida por el usuario
#endif          
         if (tp) {
            pila.Sacar(op1);
            res = Calcula(tp,op1);
            if (Error_matematico) return 0.0;
            pila.Meter(res);
            xcad[0] = 0;
            tp = 0;
            goto Etiqueta2;
         }

         // Funciones que requieren dos parametros
         if (!strcmp(xcad,"fmodl"))  tp = 50;  // Calcula el modulo de X/Y
          else if (!strcmp(xcad,"ldexpl")) tp = 45;  // Calcula X  por 2 exponente a la Y
          else if (!strcmp(xcad,"powl"))   tp = 46;  // X a la Y
          else if (!strcmp(xcad,"maxl"))   tp = 70;  // Maximo entre X e Y
          else if (!strcmp(xcad,"minl"))   tp = 71;  // Minimo entre X e Y
         if (tp) {
            pila.Sacar(op2);
            pila.Sacar(op1);
            res = Calcula(tp,op1,op2);
            if (Error_matematico) return 0.0;
            pila.Meter(res);
            xcad[0] = 0;
            tp = 0;
            goto Etiqueta2;
         }

//////////////////////////////////////////////////////////////////////////////
//         // Funciones que no requieren parametros
//         if (!strcmp(xcad,"gra"))  Tipo_conversion = 1;  // Funciones trigonometricas en gradianes
//         if (!strcmp(xcad,"rad"))  Tipo_conversion = 2;  // Funciones trigonometricas en radianes
//         if (!strcmp(xcad,"deg"))  Tipo_conversion = 3;  // Funciones trigonometricas en grados
//////////////////////////////////////////////////////////////////////////////


      Etiqueta1:

         // Introduce el valor en la pila
         if (xcad[0]) {
            res = atof(xcad);
            pila.Meter(res);
            xcad[0] = 0;
         }

         // Signo igual termina el proceso
         if (cadena[i+1] == '=') break;

      Etiqueta2:
         ;
      }
      i++;
      // Aborta el calculo por error numerico
      if (Error_matematico) return 0.0;
   }
   pila.Sacar(res);
   return res;
}


// Asigna un valor a el elemento de la memoria indicado
int Calculadora_notacion_polaca::Asigna_valor(const unsigned int elem, const ldouble val)
{
   int st = 0;
   if (elem <= NUM_MAX_ELEM_MEMORIA) MEM[elem] = val;
    else st = 1;
   return st;
}

// retorna el valor del elemento de la memoria indicado
int Calculadora_notacion_polaca::Retorna_valor(const unsigned int elem, ldouble &val)
{
   int st = 0;
   val = 0.0;
   if (elem <= NUM_MAX_ELEM_MEMORIA) val = MEM[elem];
    else st = 1;
   return st;
}

// Inicializa la memoria 
void Calculadora_notacion_polaca::Inicializa_valor(void)
{
   for (unsigned int i = 0; i < NUM_MAX_ELEM_MEMORIA; i++) MEM[i] = 0.0;
}



