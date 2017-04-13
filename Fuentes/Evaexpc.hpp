//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para la evaluci�n la expresi�n puesta como una cadena                              //
// Con la forma X=(5+(6*8))+4
// Revisi�n: 3 de Noviembre del 2003                                                        //
//                                                                                          //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.dynamics.unam.edu                                                      //
// P�gina:   http://www.dynamics.unam.edu/acl                                               //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los t�rminos de la Licencia P�blica General de GNU seg�n es                         //
// publicada por la Free Software Foundation, bien de la versi�n 2 de                       //
// dicha Licencia o bien (seg�n su elecci�n) de cualquier versi�n                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea �til, pero SIN                   //
// NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. V�ase la                        //
// Licencia P�blica General de GNU para m�s detalles.                                       //
//                                                                                          //
// Deber�a haber recibido una copia de la Licencia P�blica General junto                    //
// con este programa. Si no ha sido as�, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#ifndef __EVAEXPC_HPP__
#define __EVAEXPC_HPP__


#include "Ana_exp.hpp"
#include "Definiciones.hpp"


/// Evalua una expresion que no contenga variables, del tipo X=5+sinl(3.14)+18.0
class Evalua_expresion_cadena
{
   private:
      /// Expresion en notacion polaca
      char          *exp_not_pol;

   public:

      /// Puntero al analizador sintactico
      Analizador_sintactico *Ev;
                     
      /// Indica si hay error en la evaluacion de la expresion de cadena
      int            Error;
                  
                     /// Constructor de la clase
                     Evalua_expresion_cadena(void)
                     { exp_not_pol = NULL;}
                     
                     /// Desructor de la clase
                    ~Evalua_expresion_cadena(void)
                     { delete []exp_not_pol;}
   
                     /// Expresion a revisar y evualuar
      int            Expresion_cadena(const char *exp);
                     
                     /// Evalua la expresion en tomando como dato los elementos del arreglo
      int            Evalua_expresion(ldouble *arr, long int num);
   
                     /// Evalua una expresion EXP regresando el valor numerico de esta y la cadena con dicho valor en RES
      ldouble        Evalua_expresion(const char *exp, char *res);
   
                     /// Evalua una expresion EXP regresando el valor numerico de esta
      ldouble        Evalua_expresion(const char *exp);
   
                     /// Regresa cero si la expresion es correcta en caso contrario regresa el codigo de error encontrado
      int            Expresion_correcta(void)
                     {
                        return Error;
                     }
};

#endif
