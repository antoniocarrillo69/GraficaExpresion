//////////////////////////////////////////////////////////////////////////////////////////////
// Análizador de expresiones                                                                //
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


#ifndef __ANA_EXP_HPP__
#define __ANA_EXP_HPP__

#include "Arbol_binario.hpp"


#define NUN_FUNC_NO_ENCONTRADAS  10
#define LONG_FUNC_NO_ENCONTRADAS 50



/// Arreglo que contiene los errores encontrados durante la revisión sintactica
extern const char *Errores_a_s[];


/// Clase Analizador sintáctico
class Analizador_sintactico: public Arbol_binario
{

   private:
      /// Indica el número máximo de errores
      int        Num_max_errores;
      /// Indica el número de errores en el análizador
      int        Num_errores;
      /// Indica los errores dentro del análizador
      int       *Errores;
      /// Indica el número de funciones no encontradas al revisar la sintaxis  
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
                 //   (100+x)  Funcion, donde x es el numero de parámetros de esta
      int        Tipo_nodo(char *xoperd,const char *xn_der);
                 /// Crea la estructura del árbol apartir de una expresión
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
                 // (1)  Función auxiliar
                 //      F(x)=...
                 //      F(y)=... 
                 // (2)  Parámetro
                 //      A=10
                 // (3)  Expresión aritmética
                 //      A=10*sin(x)
                 // (5)  Variable de configuración
                 //      VARIABLEDEFINIDA=0.1
     void        Analiza_expresion_tipo_01(const char *exp);

                 /// Analiza expresiones del tipo:
                 // (4)  Ecuación Diferencial
                 //      x'= ...
                 //      y''...=...        
     void        Analiza_expresion_tipo_02(const char *exp);

                 /// Retorna el número de funciones no encontradas
     int         Retorna_num_funciones_no_encontradas(void)
                 {
                    return (Num_funciones_no_encontradas);
                 }

                 /// Retorna la cadena de la función i-esima no encontrada
     void        Retorna_funcion_no_encontrada(const int i, char *xcad)
                 {
                    if (i < Num_funciones_no_encontradas) strcpy(xcad,Cadena_funcion_no_encontrada[i]);
                     else strcpy(xcad,"");
                 }            


};

#endif

