//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para manipular una pila                                                            //
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




#ifndef __PILA_HPP__
#define __PILA_HPP__

#include "Cadenas.hpp"
#include "Definiciones.hpp"


#define ALFABETICA  0
#define NUMERICA    1
#define ENTEROS     2

/// Clase PILA permite manipular una pila de longitud variable creada dinamicamente
class PILA: virtual public Cadenas
{
   private:
      unsigned int    NUM_ELEMENTOS_PILA;    // Indica el numero maximo de elementos de la pila
      ldouble        *NBufer;                // Puntero a los elementos de la pila
      char          **CBufer;                // Puntero a los elementos de la pila
      char           *Cxcad;                 // Puntero a una cadena temporal
      int            *EBufer;
      unsigned int    Elemento_actual;       // Indica el elemento actual
      unsigned int    Desbordamiento:  1;    // Indica si existe desbordamineto
      unsigned int    Vacia:           1;    // Indica si la pila esta vacia
      unsigned int    Tipo_pila;             // Indica si es pila numerica (1) o alfabetica

   public:
          // Constructor y destructor de la pila
          PILA(const unsigned int num_elementos_pila, const unsigned int tipo);
         ~PILA();
         
      int Meter(const ldouble cadena);
      int Meter(const int cadena);
      int Meter(const char *cadena);
      int Sacar(ldouble &cad);
      int Sacar(int &cad);
      int Sacar(char *cad);
      int Pila_desbordamiento(void)
          {return Desbordamiento;}
      int Pila_vacia(void)
          {return Vacia;}
};

#endif


