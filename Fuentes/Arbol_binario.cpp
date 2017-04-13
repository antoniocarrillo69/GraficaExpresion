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




#include "Arbol_binario.hpp"



///////////////////////////////////////////////////////////////////
//                                                               //
//                     Clase Arbol binario                       //
//                                                               //
///////////////////////////////////////////////////////////////////


// Crea el nodo y copia a este la expresion pasada como par�metro
NODO *Arbol_binario::Crea_nodo (const char *exp, const int tipo)
{
   // Puntero al nodo a ser creado
   NODO *ptr_nodo = NULL;
   // Si la cadena es nula retorna un puntero nulo
   if (!exp[0]) return ptr_nodo;
   // Se solicita la memoria para crear el nodo
   ptr_nodo = new NODO;
   // Los punteros a nodos hijos son puestos a nulos
   ptr_nodo->NODO_DERECHO = ptr_nodo-> NODO_IZQUIERDO = NULL;
   // Solicitud de la memoria necesaria para el contenido del nodo y copia la expresi�n
   ptr_nodo->NODO_CONTENIDO = Asigna_puntero(exp);
   // Copia el tipo de informacion del nodo
   ptr_nodo->NODO_TIPO = tipo;
   // Retorna un puntero al nodo recien creado
   return ptr_nodo;
}


// Borra todo el �rbol
void Arbol_binario::Destruye_arbol(void)
{
   // Borra todo los nodos apartir de la raiz
   Borra_nodos(PTR_RAIZ);
   PTR_RAIZ = NULL;
}

// Borra todos los nodos internos apartir del puntero al nodo pasado como parametro
void Arbol_binario::Borra_nodos(NODO *ptr_nodo)
{
   if (ptr_nodo) {
      // Libera la memoria ocupada por el contenido del nodo
      delete[] (ptr_nodo->NODO_CONTENIDO);
      // Borra en forma recursiva los nodos
      Borra_nodos(ptr_nodo->NODO_DERECHO);
      Borra_nodos(ptr_nodo->NODO_IZQUIERDO);
      // Libera la memoria ocupada por el nodo
      delete ptr_nodo;
   }
}

// Recorrido en preorden
void Arbol_binario::Recorrido_preorden(NODO *ptr_nodo)
{
   if (ptr_nodo) {
      if ((strlen(exp_tmp)+strlen(ptr_nodo->NODO_CONTENIDO)) >= Max_long_cadena) return; 
      strcat(exp_tmp,ptr_nodo->NODO_CONTENIDO);
      strcat(exp_tmp,"|");
      Recorrido_preorden(ptr_nodo->NODO_IZQUIERDO);
      Recorrido_preorden(ptr_nodo->NODO_DERECHO);
   }
}

// Recorrido en inorden
void Arbol_binario::Recorrido_inorden(NODO *ptr_nodo)
{
   if (ptr_nodo) {
      Recorrido_inorden(ptr_nodo->NODO_IZQUIERDO);
      if ((strlen(exp_tmp)+strlen(ptr_nodo->NODO_CONTENIDO)) >= Max_long_cadena) return; 
      strcat(exp_tmp,ptr_nodo->NODO_CONTENIDO);
      strcat(exp_tmp,"|");
      Recorrido_inorden(ptr_nodo->NODO_DERECHO);
   }
}

// Recorrido en postorden
void Arbol_binario::Recorrido_postorden(NODO *ptr_nodo)
{
   if (ptr_nodo) {
      Recorrido_postorden(ptr_nodo->NODO_IZQUIERDO);
      Recorrido_postorden(ptr_nodo->NODO_DERECHO);
      if ((strlen(exp_tmp)+strlen(ptr_nodo->NODO_CONTENIDO)) >= Max_long_cadena) return; 
      strcat(exp_tmp,ptr_nodo->NODO_CONTENIDO);
      strcat(exp_tmp,"|");
   }
}


// Retorna la expresion en el siguiente formato
// Si TP es PREORDEN regresa le expresion en preorden
//          INORDEN regresa le expresion en inorden
//          POSTORDEN regresa le expresion en postorden
void Arbol_binario::Retorna_expresion(char *xexp, const int tp, const int lg)
{
   // Almaceno la m�xima longitud de la cadena esperada
   Max_long_cadena = lg;
   // Solicito espacio en memoria para la cadena 
   exp_tmp = Asigna_puntero(Max_long_cadena+10);
   // Inicializa la cadena
   exp_tmp[0] = 0;
   // Hace el recorido 
   if (tp == PREORDEN)  Recorrido_preorden(PTR_RAIZ);
   if (tp == INORDEN)   Recorrido_inorden(PTR_RAIZ);
   if (tp == POSTORDEN) Recorrido_postorden(PTR_RAIZ);
   // Copia la cadena en el orden especificado
   strcpy(xexp,exp_tmp);
   // Borra la cadena temporal
   delete exp_tmp;
}




