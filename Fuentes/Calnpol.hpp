//////////////////////////////////////////////////////////////////////////////////////////////
// Evalua expresion en notacion polaca postfija                                             //
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





#ifndef __CALNPOL_HPP__
#define __CALNPOL_HPP__


#include "Cadenas.hpp"
#include "Definiciones.hpp"

#define NUM_MAX_ELEM_MEMORIA  10

/// Clase que funje como una calculadora en notación polaca
class Calculadora_notacion_polaca: public Cadenas
{
   private:
     
      /// Indica el tipo de conversion activa el la calculadora
      int         Tipo_conversion;
      /// Indica si hay error matemático
      int         Error_matematico;
      /// Varibles definidas por el usuario
      ldouble MEM[NUM_MAX_ELEM_MEMORIA];
      
      /// Rutina que recibe un indicador de operacion asi como un numero determinado de operandos para realizar la operacion indicada
      ldouble Calcula(const unsigned int operacion, const ldouble op1, const ldouble op2);
      /// Rutina que recibe un indicador de operacion asi como un numero determinado de operandos para realizar la operacion indicada
      ldouble Calcula(const unsigned int operacion, const ldouble op1);

   
   public:
      /// Constructor de la clase
      Calculadora_notacion_polaca(void)
      {
          Inicializa_valor();
      }
                  
      /// Rutina que calcula el valor numerico de una expresion en notacion polaca con separador de operandos el pipe
      ldouble Evalua(const char *cadena);
      /// Asigna un valor a el elemento de la memoria indicado
      int         Asigna_valor(const unsigned int elem, const ldouble val);
      /// Retorna el valor del elemento de la memoria indicado
      int         Retorna_valor(const unsigned int elem, ldouble &val);
      /// Inicializa la memoria 
      void        Inicializa_valor(void);
};

#endif
