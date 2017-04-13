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


#ifndef __ANA_EXP_HPP__
#define __ANA_EXP_HPP__

#include "Arbol_binario.hpp"


#define NUN_FUNC_NO_ENCONTRADAS  10
#define LONG_FUNC_NO_ENCONTRADAS 50



/// Arreglo que contiene los errores encontrados durante la revisi�n sintactica
extern const char *Errores_a_s[];


/// Clase Analizador sint�ctico
class Analizador_sintactico: public Arbol_binario
{

   private:
      /// Indica el n�mero m�ximo de errores
      int        Num_max_errores;
      /// Indica el n�mero de errores en el an�lizador
      int        Num_errores;
      /// Indica los errores dentro del an�lizador
      int       *Errores;
      /// Indica el n�mero de funciones no encontradas al revisar la sintaxis  
      int        Num_funciones_no_encontradas;
      /// Matriz que guarda las funciones no encontradas al revisar la sintaxis
      char       Cadena_funcion_no_encontrada[NUN_FUNC_NO_ENCONTRADAS][LONG_FUNC_NO_ENCONTRADAS];
      
      



                 /// Revisa que esten bien balanceados los agrupadores
                 // Si TP es (0) Revisa todos 
                 //          (1) Revisa parentesis 
                 //          (2) Revisa llaves
                 //          (3) Revisa corchetes 
                 // Regresa  (0) Sin errores 
                 //          (1) Parentesis mal balanceados 
                 //          (2) Llaves mal balanceadas 
                 //          (3) Corchetes mal balanceados
     int         Revisa_balance(const char *exp, const int tp);
                 /// Valida expresion primera pasada
     void        Valida_expresion_primera_pasada(const char *exp, const bool tp);
                 /// Separa operador y operandos
     void        Separa_operandos(const char *exp, char *operador, char *nodo_izq, char *nodo_der);
                 /// Valida expresion segunda pasada
     void        Valida_expresion_segunda_pasada(const char *exp);
                 /// Retorna el tipo de nodo del que se trate
                 //   (1)      Variable
                 //   (2)      Constante
                 //   (3)      Operador
                 //   (4)      Numero
                 //   (100+x)  Funcion, donde x es el numero de par�metros de esta
      int        Tipo_nodo(char *xoperd,const char *xn_der);
                 /// Crea la estructura del �rbol apartir de una expresi�n
      NODO      *Crea_estructura_arbol(const char *exp);



      
          
   public:


                 /// Constructor de la clase
                 Analizador_sintactico(void);
                 /// Destructor de la clase
                ~Analizador_sintactico();

                 /// Retorna la cadena de error correspondiente al err_num
     const char *Retorna_error(const int err_num)
                 {return (Errores_a_s[Errores[err_num]]);}
                 /// Retorna el codigo de error correspondiente al err_num
     int         Retorna_codigo_error(const int err_num)
                 {return (Errores[err_num]);}

                 /// Retorna el numero de errores
     int         Numero_errores(void)
                 {return Num_errores;}

                 /// Analiza expresiones del tipo:
                 // (1)  Funci�n auxiliar
                 //      F(x)=...
                 //      F(y)=... 
                 // (2)  Par�metro
                 //      A=10
                 // (3)  Expresi�n aritm�tica
                 //      A=10*sin(x)
                 // (5)  Variable de configuraci�n
                 //      VARIABLEDEFINIDA=0.1
     void        Analiza_expresion_tipo_01(const char *exp);

                 /// Analiza expresiones del tipo:
                 // (4)  Ecuaci�n Diferencial
                 //      x'= ...
                 //      y''...=...        
     void        Analiza_expresion_tipo_02(const char *exp);

                 /// Retorna el n�mero de funciones no encontradas
     int         Retorna_num_funciones_no_encontradas(void)
                 {
                    return (Num_funciones_no_encontradas);
                 }

                 /// Retorna la cadena de la funci�n i-esima no encontrada
     void        Retorna_funcion_no_encontrada(const int i, char *xcad)
                 {
                    if (i < Num_funciones_no_encontradas) strcpy(xcad,Cadena_funcion_no_encontrada[i]);
                     else strcpy(xcad,"");
                 }            


};

#endif

