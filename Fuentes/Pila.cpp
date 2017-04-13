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



#include <string.h>
#include "Pila.hpp"



// Constructor de la pila
PILA::PILA(const unsigned int num_elementos_pila, const unsigned int tipo)
{
   // Inicializa el indicador de la pila
   Desbordamiento = 0;
   Vacia = 1;
   Elemento_actual = 0;
   Tipo_pila = tipo;
   // Define la longitud de la pila y el numero de elementos de esta
   NUM_ELEMENTOS_PILA = num_elementos_pila;
   if (Tipo_pila == NUMERICA) {
      // Solicita la memoria para la pila
      NBufer = new ldouble[NUM_ELEMENTOS_PILA+1];
      // Solicita la memoria para la cadena temporal de trabajo
      for (unsigned int i = 0; i < NUM_ELEMENTOS_PILA; i++) NBufer[i] = 0.0;
   } 
   if (Tipo_pila == ENTEROS) {
      // Solicita la memoria para la pila
      EBufer = new int[NUM_ELEMENTOS_PILA+1];
      // Solicita la memoria para la cadena temporal de trabajo
      for (unsigned int i = 0; i < NUM_ELEMENTOS_PILA; i++) EBufer[i] = 0;
   } 
   if (Tipo_pila == ALFABETICA) {
      // Solicita la memoria para la pila
      CBufer = new char *[NUM_ELEMENTOS_PILA+1];
      // Solicita la memoria para la cadena temporal de trabajo
      for (unsigned int i = 0; i < NUM_ELEMENTOS_PILA; i++) CBufer[i] = NULL;
   }
}


// Destructor de la pila
PILA::~PILA()
{
   // Libera la memoria solicitada para la pila
   if (Tipo_pila == NUMERICA) delete[] NBufer;
   if (Tipo_pila == ENTEROS)  delete[] EBufer;
   if (Tipo_pila == ALFABETICA) {
      for (unsigned int i = 0; i < NUM_ELEMENTOS_PILA; i++) delete CBufer[i];
      delete[] CBufer;
   }
}


// Mete un numero en la pila
int PILA::Meter(const ldouble cadena)
{
   if (Elemento_actual < NUM_ELEMENTOS_PILA) {
      NBufer[Elemento_actual] = cadena;
      Elemento_actual ++;
      Desbordamiento = 0;
   } else Desbordamiento = 1;
   Vacia = 0;
   return Desbordamiento;
}


// Mete un numero en la pila
int PILA::Meter(const int cadena)
{
   if (Elemento_actual < NUM_ELEMENTOS_PILA) {
      EBufer[Elemento_actual] = cadena;
      Elemento_actual ++;
      Desbordamiento = 0;
   } else Desbordamiento = 1;
   Vacia = 0;
   return Desbordamiento;
}

// Mete la cadena en la pila
int PILA::Meter(const char *cadena)
{
   if (Elemento_actual < NUM_ELEMENTOS_PILA) {
      Cxcad = Asigna_puntero(cadena);
      strcpy(Cxcad,cadena);
      CBufer[Elemento_actual] = Cxcad;
      Elemento_actual ++;
      Desbordamiento = 0;
   } else Desbordamiento = 1;
   Vacia = 0;
   return Desbordamiento;
}

// Saca de la pila un numero
int PILA::Sacar(ldouble &cad)
{
   cad = 0;
   if (Elemento_actual > 0) {
      Elemento_actual --;
      cad = NBufer[Elemento_actual];
      NBufer[Elemento_actual] = 0.0;
   } 
   if (Elemento_actual) Vacia = 0;
    else Vacia = 1;
   return Vacia;
}

// Saca de la pila un numero
int PILA::Sacar(int &cad)
{
   cad = 0;
   if (Elemento_actual > 0) {
      Elemento_actual --;
      cad = EBufer[Elemento_actual];
      EBufer[Elemento_actual] = 0;
   } 
   if (Elemento_actual) Vacia = 0;
    else Vacia = 1;
   return Vacia;
}


// Saca de la pila una cadena
int PILA::Sacar(char *cad)
{
   cad[0] = 0;
   if (Elemento_actual > 0) {
      Elemento_actual --;
      strcpy(cad,CBufer[Elemento_actual]);
      delete CBufer[Elemento_actual];
      CBufer[Elemento_actual] = NULL;
   } 
   if (Elemento_actual) Vacia = 0;
    else Vacia = 1;
   return Vacia;
}


