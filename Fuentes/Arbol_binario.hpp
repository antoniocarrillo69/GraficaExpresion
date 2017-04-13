//////////////////////////////////////////////////////////////////////////////////////////////
// An�lizador de expresiones                                                                //
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


#ifndef __ARBOL_BINARIO_HPP__
#define __ARBOL_BINARIO_HPP__



#include <string.h>
#include "Cadenas.hpp"


#define PREORDEN                  0
#define INORDEN                   1
#define POSTORDEN                 2
                                  


/// Estructura del nodo
typedef struct nodo_arbol
{
   // Apuntador al nodo hijo izquierdo
   nodo_arbol *NODO_IZQUIERDO;
   // Apuntador al nodo hijo derecho   
   nodo_arbol *NODO_DERECHO;
   // Apuntador al contenido (El espacio se obtendra dinamicamente)
   char       *NODO_CONTENIDO;
   // Indica el tipo de informacion que contendra el nodo   
   int         NODO_TIPO;          
} NODO;



/// Clase que maneja la estructura de un arbol binario
class Arbol_binario: public Cadenas 
{
   private:
      /// Variable de uso general
      char          *exp_tmp;                      
      /// Define el tama�o de la m�xima cadena que se soportara al retornar la expresi�n
      unsigned int   Max_long_cadena;                

      
   protected:
      /// Puntero al nodo raiz
      NODO          *PTR_RAIZ;                           

      
      /// Crea el nodo y copia a este la expresion pasada como parametro
      NODO *Crea_nodo(const char *exp, const int tipo);
      /// Destruye el arbol
      void  Destruye_arbol(void);
      /// Borra los nodos internos apartir de PTR_NODO
      void  Borra_nodos(NODO *ptr_nodo);
      /// Recorrido en preorden
      void  Recorrido_preorden(NODO *ptr_nodo);
      /// Recorrido en inorden
      void  Recorrido_inorden(NODO *ptr_nodo);
      /// Recorrido en postorden
      void  Recorrido_postorden(NODO *ptr_nodo);


   public:

      /// Retorna la expresion en el siguiente formato
      // Si TP es PREORDEN regresa le expresion en preorden
      //          INORDEN regresa le expresion en inorden
      //          POSTORDEN regresa le expresion en postorden
      void  Retorna_expresion(char *xexp, const int tp, const int lg);
};


#endif

