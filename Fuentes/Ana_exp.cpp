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



#include <stdlib.h>
#include <stdio.h>
#include "Ana_exp.hpp"
#include "A_R_MAT.hpp"



///////////////////////////////////////////////////////////////////
//                                                               //
//                  Clase del Analizador Sintáctico              //
//                                                               //
///////////////////////////////////////////////////////////////////



#define LETRA          1
#define NUMERO         2
#define OPERADOR       3
#define AGRUPADOR      4
#define IGUAL          5
#define SEPARADOR      6 

// Arreglo que contiene la descripcion de los errores
#ifdef _IDIOMA_ESPANOL_
   const char *Errores_a_s[] = {
      "Existen caracteres desconocidos",                            // 0
      "No existe ningun signo de igualdad",                         // 1
      "Existe más de un signo de igualdad",                         // 2
      "Existen operandos dentro de la variable de asisgnación",     // 3
      "Existe un operando sin operador",                            // 4
      "Existe un operador sin operando",                            // 5
      "Error de sintaxis",                                          // 6
      "El punto decimal solo es aplicable a expresiones numericas", // 7
      "La coma se usa solo para separar parametros en la función",  // 8
      "",                                                           // 9
      "No hay expresion despues del signo igual",                   // 10
      "El nombre de la variable debe empezar con una letra",        // 11
      "La expresion numerica debe contener un sólo punto",          // 12
      "Existe más de un indicador de notacion exponencial",         // 13
      "Error en la notación exponencial",                           // 14
      "Parentesis mal balanceados",                                 // 15
      "Llaves mal balanceados",                                     // 16
      "Parentesis cuadrados mal balanceados",                       // 17
      "Error en el numero de parametros de la función",             // 18
      "La funcion no es valida",                                    // 19
      "Expresion no reconocida",                                    // 20
      "Existen demasiados errores en el analizador",                // 21
      "Falta parametro en la función"                               // 22
   };
#else 
   const char *Errores_a_s[] = {
      "There are unknown characters",                               // 0
      "There is none equal symbol",                                 // 1
      "There is more than one equal symbol",                        // 2
      "There are operatives within the designed variable",          // 3
      "There is an operative without operator",                     // 4
      "There is an operator without operative",                     // 5
      "Syntax  error",                                              // 6
      "Decimal dot is only applied to numerical expressions",       // 7
      "A comma is only used to separate parameters in a function",  // 8
      "",                                                           // 9
      "There is no expression after an equal symbol",               // 10
      "A variable name should start with a letter",                 // 11
      "A numerical expression should have only one dot",            // 12
      "There is more than one exponential notation indicator",      // 13
      "Error on the exponential notation",                          // 14
      "Unbalanced parenthesis",                                     // 15
      "Unbalanced keys",                                            // 16
      "Unbalanced brackets",                                        // 17
      "Funtion parameters number error",                            // 18
      "Invalid function",                                           // 19
      "Unknown expression",                                         // 20
      "Too many errors in the analizer",                            // 21
      "Function parameter missing"                                  // 22
   };
#endif

// Indica que se sustituyan las constantes
//#define SUSTITUYE_CONSTANTES

/*
+  Rutina que valide que antes de un espacio hay (1) y despues de un espacio hay (2)
   letra    esp   simbolo ()*-/+,
   numero   esp   simbolo )*+/-,
   simbolo  esp   letra/numero()
+ Aplicar la rutina anterior para analizar la expresion despues de eliminar espacios inecesarios

*/



////////////////////////////////////////////////////////////
//
// No permitir 9e*3 o 9e/2 ni 9e  en notacion exponencial
// 
//
//
////////////////////////////////////////////////////////////




// Constructor del árbol sintáctico
Analizador_sintactico::Analizador_sintactico(void)
{
   // Inicializa el puntero al nodo raiz
   PTR_RAIZ = NULL;
   //Inicializa la variable de estado
   Num_errores = 0, Num_max_errores = 50;
   //Solicita memoria para los errores
   Errores = new int[Num_max_errores];
}


// Destructor del árbol sintáctico
Analizador_sintactico::~Analizador_sintactico()
{
   // Borra todo el árbol
   Destruye_arbol();
   // Borra la estructura que contiene los errores
   delete []Errores;
}


// Analiza expresiones del tipo:
// (1)  Función auxiliar
//      F(x)=...
//      F(y)=... 
// (2)  Parámetro
//      A=10
// (3)  Expresión aritmética
//      A=10*sin(x)
// (5)  Variable de configuración
//      VARIABLEDEFINIDA=0.1
void Analizador_sintactico::Analiza_expresion_tipo_01(const char *exp)
{
   Num_funciones_no_encontradas = 0;
   if (!Lg_cadena_sin_espacios(exp)) return;
   int i, st;

   // inicializa las variables de control de errores
   for (i = 0; i < Num_max_errores; i++) Errores[i] = 0;
   Num_errores = 0;

   // Destruye el árbol binario (si existe este)
   Destruye_arbol();
   

   // Valida que solo contenga caracteres validos
   const char *xexp;
   xexp = exp;
   while (*xexp) {
      if ((*xexp < ' ' || *xexp > 126) || *xexp == '\'') Errores[Num_errores++] = 0;
      xexp++;
   }
   if (Num_errores)  return;  



   // Revisa apareamiento de agrupadores
   st = Revisa_balance(exp,0); 
   if (st) {
      Errores[Num_errores++] = st+14; 
      return; 
   }


   // Prepara la expresion para el resto de las validaciones
   char *expresion = Asigna_puntero(exp); 
   // Elimina los expacios excesivos
   Elimina_espacios_inicesarios(expresion);
   // Hacer validacion tal como viene la cadena buscar
   // caracter_alfabetico espacio caracter_alfabetico
   // caracter_numerico   espacio caracter_numerico
   // caracter_alfabetico espacio caracter_numerico
   // caracter_numerico   espacio caracter_alfabetico
   xexp = expresion;
   while (*xexp) {
      if (*xexp == ' ') {
          if ( Es_caracter_alfabetico(*(xexp-1)) && Es_caracter_alfabetico(*(xexp+1)) ) Errores[Num_errores++] = 6;
          if ( Es_caracter_digito(*(xexp-1))     && Es_caracter_digito(*(xexp+1)) )     Errores[Num_errores++] = 6;
          if ( Es_caracter_alfabetico(*(xexp-1)) && Es_caracter_digito(*(xexp+1)) )     Errores[Num_errores++] = 6;
          if ( Es_caracter_digito(*(xexp-1))     && Es_caracter_alfabetico(*(xexp+1)) ) Errores[Num_errores++] = 6;

      } 
      xexp++;
   }
   if (Num_errores)  {
      delete []expresion;
      return;  
   }
   // Quita todos los espacios
   Quitar_caracter(expresion, ' ', 1);


   // Hace la primera revision
   Valida_expresion_primera_pasada(expresion,false); 
   if (Num_errores) {
      delete []expresion;
      return;
   }

   // Hace la segunda revision
   Valida_expresion_segunda_pasada(expresion);
   if (Num_errores) {
      delete []expresion;
      return;
   }

   // Analiza la espresion formando un árbol binario
   PTR_RAIZ = Crea_estructura_arbol(expresion);

   // Borra variables temporales
   delete []expresion;
}


// Analiza expresiones del tipo:
// (4)  Ecuación Diferencial
//      x'= ...
//      ó
//      x''=...        
void Analizador_sintactico::Analiza_expresion_tipo_02(const char *exp)
{
   Num_funciones_no_encontradas = 0;
   if (!Lg_cadena_sin_espacios(exp)) return;
   int i, st;

   // inicializa las variables de control de errores
   for (i = 0; i < Num_max_errores; i++) Errores[i] = 0;
   Num_errores = 0;

   // Destruye el árbol binario (si existe este)
   Destruye_arbol();

   // Valida que solo contenga caracteres validos
   const char *xexp = exp;
   while (*xexp) {
      if (*xexp < ' ' || *xexp > 126) Errores[Num_errores++] = 0;
      xexp++;
   }
   if (Num_errores)  return;  


   // Revisa apareamiento de agrupadores
   st = Revisa_balance(exp,0); 
   if (st) {
      Errores[Num_errores++] = st+14; 
      return; 
   }

   // Prepara la expresion para el resto de las validaciones
   char *expresion = Asigna_puntero(exp); 
   // Elimina los expacios excesivos
   Elimina_espacios_inicesarios(expresion);
   // Hacer validacion tal como viene la cadena buscar
   // caracter_alfabetico espacio caracter_alfabetico
   // caracter_numerico   espacio caracter_numerico
   // caracter_alfabetico espacio caracter_numerico
   // caracter_numerico   espacio caracter_alfabetico
   xexp = expresion;
   while (*xexp) {
      if (*xexp == ' ') {
          if ( Es_caracter_alfabetico(*(xexp-1)) && Es_caracter_alfabetico(*(xexp+1)) ) Errores[Num_errores++] = 6;
          if ( Es_caracter_digito(*(xexp-1))     && Es_caracter_digito(*(xexp+1)) )     Errores[Num_errores++] = 6;
          if ( Es_caracter_alfabetico(*(xexp-1)) && Es_caracter_digito(*(xexp+1)) )     Errores[Num_errores++] = 6;
          if ( Es_caracter_digito(*(xexp-1))     && Es_caracter_alfabetico(*(xexp+1)) ) Errores[Num_errores++] = 6;

      } 
      xexp++;
   }
   if (Num_errores)  {
      delete []expresion;
      return;  
   }
   // Quita todos los espacios
   Quitar_caracter(expresion, ' ', 1);

   // Revisa que tipo de ecuación diferencial se trata
   int ct = 0;
   int xxi = 0;
   while (expresion[xxi] != '=') {
      if (expresion[xxi] == '\'') ct ++;
      xxi ++;
   }
   // Hace la primera revisión checando si es una ecuación de primer o segundo orden
   if (ct == 1) {
      while (expresion[xxi]) {
         if (expresion[xxi] == '\'') {
            Errores[Num_errores++] = 6;
            delete []expresion;
            return;
         }
         xxi ++;
      }
      Valida_expresion_primera_pasada(expresion, false); 
   } else Valida_expresion_primera_pasada(expresion, true); 
   if (Num_errores) {
      delete []expresion;
      return;
   }

   // Hace la segunda revision
   Valida_expresion_segunda_pasada(expresion);
   if (Num_errores) {
      delete []expresion;
      return;
   }

   // Analiza la espresion formando un árbol binario
   PTR_RAIZ = Crea_estructura_arbol(expresion);

   // Borra variables temporales
   delete []expresion;
}


// Revisa que esten bien balanceados los parentesis, llaves o corchetes 
// Si TP es (0) Revisa todos 
//          (1) Revisa parentesis 
//          (2) Revisa llaves
//          (3) Revisa corchetes 
// Regresa  (0) Sin errores 
//          (1) Parentesis mal balanceados 
//          (2) Llaves mal balanceadas 
//          (3) Corchetes mal balanceados
int Analizador_sintactico::Revisa_balance(const char *exp, const int tp)  
{
   int n_corchetes = 0, n_llaves = 0, n_parentesis = 0, st = 0; 
   int stp = 0, stl = 0, stc = 0;
   while (*exp) {
     switch (*exp) {
        case '[': // Revisa que los corchetes esten apareados
          n_corchetes ++;
          break;
        case ']':
          n_corchetes --;
          break;
        case '{': // Revisa que las llaves esten apareados
          n_llaves ++;
          break;
        case '}':
          n_llaves --;
          break;
        case '(': // Revisa que los parentesis esten apareados
          n_parentesis ++;
          break;
        case ')': 
          n_parentesis --;
          break;
     }
     // Revisa que no exista parentesis, llaves o corchetes de cerradura sin apertura
     if (n_parentesis < 0) stp = 1;
     if (n_llaves < 0)     stl = 2;
     if (n_corchetes < 0)  stc = 3;
     exp++;
   }
   // Revisa si existen parentesis, llaves o corchetes mal apareados
   if (n_parentesis) stp = 1;
   if (n_llaves)     stl = 2;
   if (n_corchetes)  stc = 3;
   // Si TP es (0) entonces reporta que encontro mal en parentesis, llaves o corchetes
   if (tp == 0) {
      if (stp) st = stp;
      if (stl) st = stl;
      if (stc) st = stc;
      return st;
    } else {
      // Si TP es distinto de (0) entonces reporta que encontro mal en parentesis, llaves o corchetes indicados por TP
      if (tp == 1 && stp) st = stp;
      if (tp == 2 && stl) st = stl;
      if (tp == 3 && stc) st = stc;
   }
   return st;
}


// Valida expresion primera pasada
void Analizador_sintactico::Valida_expresion_primera_pasada(const char *exp, const bool tp)
{
   #define NUM_ELEM_ARRAY 7
   int xi, i = 0;
   // Si el actual caracter es igual a ...
   const char *Arr1[] = { 
      "*-+/,",
      ".",
      "=",
      "'",
      "([{",
      "&",
      "|" 
   };
   // El siguiente caracter no debe de ser ...
   const char *Arr2[] = { 
      "*-+/,.=)]}><?:|&",
      "([{eE)]}=*-+/><?:|&",
      "*,./)]}?:&|",              // Se excluye el signo '=' para permitir ==, >=, <=
      "*+-/([{}])><?:|&,.0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "*=/.><?:|&",//      ")]}*=/.><?:|&",
      "?:|*-/+-)]}.,'><=",
      "?:&*-/+-)]}.,'><="
   };

   unsigned int pos;
   // Revisa toda la expresion
   while (exp[i]) {
      if (exp[i+1]) {
         // Revisa todo el contenido del arreglo
         for (xi = 0; xi < NUM_ELEM_ARRAY; xi++) {
             // Excluye revisión si es ecuación de segundo orden 
             if (tp && xi == 3) continue;
             // Busca si el caracter actual esta el en primer arreglo
             if (Busca_caracter(Arr1[xi],exp[i],pos)) {
                // busca si el siguiente caracter esta en el segundo arreglo
                if (Busca_caracter(Arr2[xi],exp[i+1],pos)) {
                   Errores[Num_errores++] = 6;
                }
             }
         }
      }
      i++;
   }
}



// Valida expresion segunda pasada
void Analizador_sintactico::Valida_expresion_segunda_pasada(const char *exp)
{
  int n_s_igual = 0, n_parentesis = 0, Exp_numerica = 0, i = 0;
  char car, car2, car3;
  unsigned int pos, lg = strlen(exp);
  // Revisa la exp
  car = exp[i];
  car2 = exp[i+1];
  if (i) car3 = exp[i-1];
   else car3 = 0;
  while (car) {
     switch (car) {
        case '?':
        case '<':
        case '>':
        case ':':
        case '&':
        case '|':
        case ' ': Exp_numerica = 0; 
          break;
        case ',':
          if (!n_parentesis) Errores[Num_errores++] = 8;
          if (car3 == '(') Errores[Num_errores++] = 22;
        case '+':
        case '-':
        case '*':
        case '/':
          // Valida que no exista otro operador sin operando *+/-.,)
          if (Busca_caracter("*+/,)",car2,pos)) Errores[Num_errores++] = 5;
          // Existen operandos antes del signo de igualdad
          if (!n_s_igual) Errores[Num_errores++] = 3;
          if (Es_caracter_digito(car2)) Exp_numerica = 1;
           else Exp_numerica = 0;
          break;
        case '(': // Revisa que los parentesis esten apareados
          n_parentesis ++;
          // No puede existir (, (* (/  
          if (Busca_caracter("*,/",car2,pos)) Errores[Num_errores++] = 5;
          if (Es_caracter_digito(car2)) Exp_numerica = 1;
           else Exp_numerica = 0;
          break;
        case ')': // Revisa que los parentesis esten apareados
          n_parentesis --,Exp_numerica = 0;;
          // No puede existir )[0-9]
          if (Es_caracter_digito(car2)) Errores[Num_errores++] = 4;
          // No puede existir )(
          if (car2 == '(') Errores[Num_errores++] = 5;
          break;
        case '=':
          n_s_igual ++;
          if (!car2) Errores[Num_errores++] = 10;
          if (Busca_caracter("*,/",car2,pos)) Errores[Num_errores++] = 5;
          if (Es_caracter_digito(car2)) Exp_numerica = 1;
           else Exp_numerica = 0;
          break; // Cuenta el numero de signos igual el la expresion
        case '.': // Valida el uso del punto decimal
          // Verifica que el punto decimal sea precedido y antecedido por un numero
          if (!(Es_caracter_digito(car3) || Busca_caracter("*+=/-,(",car3,pos))) Errores[Num_errores++] = 7;
          if (!Es_caracter_digito(car2)) Errores[Num_errores++] = 7;
          // Error mas de un punto decimal en una misma expresion numerica
          // el punto decimal solo en expresiones numericas
          break;
        case 'e':
        case 'E':
          break;
        default:
          if (Es_caracter_alfabetico(car)) {
             if (Exp_numerica) Errores[Num_errores++] = 11;
             Exp_numerica = 0;
          }
          if (car < 38) Errores[Num_errores++] = 0;
          switch (car) {
             case 59:
             case 64:
             case 96:
               Errores[Num_errores++] = 0;
          }

     }
     // Controla la cantidad maxima de errores en el analizador
     if (Num_errores >= Num_max_errores-5) {
        Errores[Num_max_errores-5] = 21;
        break;
     }
     i++;
     car = exp[i];
     car2 = exp[i+1];
     car3 = exp[i-1];
  }
  // Error caracteres desconocidos al final de la expresion
  if (Busca_caracter("*-/+",exp[lg - 1],pos)) Errores[Num_errores++] = 5;

  // Revisa la existencia unica del signo igual
  if (!n_s_igual) Errores[Num_errores++] = 1;
  if (!Busca_caracter(exp,'?',pos)) {
     if (n_s_igual > 1) Errores[Num_errores++] = 2;
  }
}

// Crea la estructura del árbol apartir de una expresion
NODO *Analizador_sintactico::Crea_estructura_arbol(const char *exp)
{
   NODO *ptr_nodo = NULL;
   // Si cadena es nula retorna un puntero nulo
   if (!exp[0]) return ptr_nodo;

   // No valida si encuentra que es una expresion con comparaciones internas
   unsigned int pos;
   if (Busca_caracter(exp,'?',pos)) return ptr_nodo;

   // Solicita memoria para contener las cadenas temporales
   unsigned int lg = strlen(exp)+1;
   char *xoperd = Asigna_puntero(lg+20);
   char *xn_izq = Asigna_puntero(lg);
   char *xn_der = Asigna_puntero(lg);

   // Se optiene el contenido del operador y sus operandos
   Separa_operandos(exp,xoperd,xn_izq,xn_der);


   // obtiene el tipo de nodo
   int tipo_nodo = Tipo_nodo (xoperd,xn_der);

   // Crea el nodo con la informacion del operador y el tipo de nodo que sera este
   ptr_nodo = Crea_nodo (xoperd,tipo_nodo);
   // Si el puntero es nulo retorna un puntero nulo
   if (ptr_nodo) {
      // Crea de manera recursiva el nodo izquierdo
      ptr_nodo->NODO_IZQUIERDO = Crea_estructura_arbol(xn_izq);
      // Crea de manera recursiva el nodo derecho
      ptr_nodo->NODO_DERECHO = Crea_estructura_arbol(xn_der);
   }
   // Libera la memoria ocupada
   delete []xoperd;
   delete []xn_izq;
   delete []xn_der;
   // retorna un puntero al nodo creado
   return ptr_nodo;
}

// Retorna el tipo de nodo del que se trate
//   (1)      Variable
//   (2)      Constante
//   (3)      Operador
//   (4)      Numero
//   (100+x)  Funcion, donde x es el numero de parametros de esta
int Analizador_sintactico::Tipo_nodo (char *xoperd,const char *xn_der)
{
   int i, tipo_nodo = 0;
   unsigned int pos;
   // Revisa el tipo de nodo

   // El contenido es un numero
   if ((xoperd[0] > '0' && xoperd[0] < '9') || xoperd[0] == '.') {
      tipo_nodo = 4;
      return tipo_nodo;
   }

   // El contenido es un operando
   if (Busca_caracter("*+/-,=",xoperd[0],pos)) {
      tipo_nodo = 3;
      return tipo_nodo;
   }

   // Revisa si es una funcion, y en caso de ser si esta es valida
   if (Es_caracter_alfabetico(xoperd[0]) && xn_der[0] == ',') {
      i = 0, tipo_nodo = 99;
      // Revisa si esta en la tabla de Funciones
      while (Funciones[i][0]) {
         // Si es una Funcion pone en el tipo de nodo 100 + el numero de parametros de esta
         if (!strcmp(Funciones[i],xoperd)) {
            tipo_nodo = atoi(Funciones[i+1])+ 100;
            break;
         }
         i += 2;
      }

      if (tipo_nodo == 99) {
         // Almacena el nombre de la función no encontrada
         if (Num_funciones_no_encontradas < NUN_FUNC_NO_ENCONTRADAS) {
            memccpy(Cadena_funcion_no_encontrada[Num_funciones_no_encontradas],xoperd,0,LONG_FUNC_NO_ENCONTRADAS);
            Num_funciones_no_encontradas++;
         }
       } else {
         // Revisa si su parametro es nulo
         if (xn_der[1] == 0) tipo_nodo = 100;
          else {
            // Revisa el número de parámetros
            int i = 0, par = 0, n_v = 0;
            while (xn_der[i]) {
               if (xn_der[i] == '(') par ++;
               // Busca el siguiente operador segun precedencia definidas
               if (!par) {
                  // Revisa si existe el operador de esa precedencia
                  if (',' == xn_der[i]) n_v++;
               }
               if (xn_der[i] == ')') par --;
               i++;
            }
            // Numero de parametros erroneos
            if ((n_v+100) != tipo_nodo) Errores[Num_errores++] = 18;
         }
      }
   }

   // Revisa si es constante
   if (Es_caracter_alfabetico(xoperd[0]) && !tipo_nodo) {
      i = 0;
      // Revisa si esta en la tabla de Constantes
      while (Constantes[i][0]) {
         // Si es una constante cambia esta por el valor indicado en la tabla Constantes
         if (!strcmp(Constantes[i],xoperd)) {
            #ifdef SUSTITUYE_CONSTANTES
               strcpy(xoperd,Constantes[i+1]);  // Sustituye la constante
            #endif
            tipo_nodo = 2;
            return tipo_nodo;
         } else i += 2;
      }
   }
   return tipo_nodo;
}

// Separa operador y operandos
void Analizador_sintactico::Separa_operandos(const char *exp, char *operador, char *nodo_izq, char *nodo_der)
{
   //  Inicializa las variables a nulos
   operador[0] = nodo_izq[0] = nodo_der[0] = 0;
   const char *Prioridad_operador[] = {"+-","*/",","};
   int st, par, xi, n_e, i;
   unsigned int pos, lg;

   // Si la cadena es nula retorna
   if (!exp[0]) return;

   // Buscar al signo igual y separar la variable de resultado de la expresion
   if (Busca_caracter(exp,'=',pos)) {
      lg = strlen(exp);
      // La variable de asignacion es el nodo izquierdo
      Substr(exp,0,pos,nodo_izq);
      // La expresion es el nodo derecho
      Substr(exp,pos+1,lg,nodo_der);
      // El operador es '='
      operador[0] = '=', operador[1] = 0;
      return;
   }



   
   // Crea espacio para la caden de trabajo
   char *xexp = Asigna_puntero(exp);                              


   // Si el primer caracter es una coma, se tomara como parametros de una funcion
   if (xexp[0] == ',') {
      i = 0;
      // Elimina la coma de la cadena de trabajo
      while (xexp[i]) {
         xexp[i] = xexp[i+1];
         i++;
      }
   }

   
   // Separa la expresion encerrada dentro de parentesis (quita todos los parentesis inecesarios)
   while (xexp[0] == '(') {
      par = 0, i = 0;
      while (xexp[i]) {
         if (xexp[i] == ')') par--;
         if (xexp[i] == '(') par++;
         // Encuentra el final de la expresion encerrada entre parentesis
         if (!par) {
            if (xexp[i+1]) {
               lg = strlen(xexp);
               // Existen otras expresiones
               Substr(xexp,0,i+1,nodo_izq);
               Substr(xexp,i+2,lg,nodo_der);
               operador[0] = xexp[i+1], operador[1] = 0;
               delete []xexp;
               return;
             } else {
               // Expresion unica
               // Retira parentesis externos
               for (xi = 0; xi < i; xi++) xexp[xi] = xexp[xi+1];
               xexp[xi-1] = 0;
            }
            break;
         }
         i++;
      }
   }




   // Si el primer caracter es menos unario (-)
   if (xexp[0] == '-') {
      i = 1;
      while (xexp[i]) {
         nodo_der[i-1]= xexp[i];
         i++;
      }
      nodo_der[i-1]= 0;
      // El segundo caracter es un digito
      if (Es_caracter_digito(xexp[1])) {
         // El resto de la expresion es un numero, se toma como menos unario de una expresion
         if (Es_cadena_numero(nodo_der)) {
            operador[0] = '-', operador[1] = 0;
            delete []xexp;
            return;
         }
       } else { // El segundo caracter es alfabetico
         st = 1;
         // Busca si tiene operadores
         if (Busca_caracteres(nodo_der,"(*+/-),",pos)) {
            i = 0, par = 0;
            while (nodo_der[i]) {
               if (nodo_der[i] == '(') par ++;
               if (nodo_der[i] == ')') par --;
               if (!par) {
                  if (Busca_caracter("+*-/,",nodo_der[i],pos)) st = 0;
               }
               i++;
            }
         }
         if (st) {
            // Si no tiene es una variable o una funcion sola
            operador[0] = '-', operador[1] = 0;
            // El nodo izquierdo tiene un cero
            nodo_izq[0] = '0', nodo_izq[1] = 0;
            delete []xexp;
            return;
         }
      }
      nodo_der[0] = 0;
   }

   // Si el primer caracter es (+)
   if (xexp[0] == '+') {
      i = 0;
      // Elimina el signo mas de la cadena de trabajo
      while (xexp[i]) xexp[i] = xexp[i+1], i++;
   }

   // Si empieza con un caracter numerico
   if (Es_caracter_numerico(xexp[0])) {
      // descarta que sea un menos unario
      if (xexp[0] != '-') {
         // Es un numero ordinario o en notacion exponencial
         if (Es_cadena_numero(xexp)) {
            strcpy(operador,xexp);
            delete []xexp;
            return;
         }
      }
      // Separa la expresion revisando la precedencia de los operadores
      lg = strlen(xexp);
      for (xi = 0; xi < 3; xi++) {
         i = 0, par = 0;
         while (xexp[i]) {
            n_e = 0;
            if (xexp[i] == '(') par ++;
            // Descarta que sea un numero en notacion exponencial
            if (i > 2 && (xexp[i] == '+' || xexp[i] == '-')) {
               if (Es_caracter_digito(xexp[i-2]) && (xexp[i-1] == 'e' || xexp[i-1] == 'E') && Es_caracter_digito(xexp[i+1])) n_e = 1;
            }
            // Busca el siguiente operador segun precedencia definidas
            if (!n_e && !par && i > 0) {
               // Revisa si existe el operador de esa precedencia
               if (Busca_caracter(Prioridad_operador[xi],xexp[i],pos)) {
                  Substr(xexp,0,i,nodo_izq);
                  Substr(xexp,i+1,lg,nodo_der);
                  operador[0] = xexp[i], operador[1] = 0;
                  delete []xexp;
                  return;
               }
            }
            if (xexp[i] == ')') par --;
            i++;
         }
      }
   }


   // Si el primer caracter es alfabetico, o esta antecedido por un menos unario
   if (Es_caracter_alfabetico(xexp[0])) {
      // Revisa si hay operadores
      if (!Busca_caracteres(xexp,"(*+/-),",pos)) {
         // Variable o constante sola
         strcpy(operador,xexp);
         delete []xexp;
         return;
       } else {
         lg = strlen(xexp);
         i = 0, st = 1, par = 0;
         while (xexp[i]) {
            if (xexp[i] == '(') par ++;
            if (xexp[i] == ')') par --;
            if (!par) {
               if (Busca_caracter("*-/+,",xexp[i],pos)) st = 0;
            }
            i++;
         }

         if (st) {
            // Es una función sola
            if (Busca_caracter(xexp,'(',pos)) {
               Substr(xexp,0,pos,operador);
               char *Xexp = Asigna_puntero(strlen(xexp)+10);                              
               if (Xexp) {
                  Substr(xexp,pos+1,lg,Xexp);
                  // Para reconocerlos como parámetro lo inicia con una coma
                  Xexp[strlen(Xexp)-1] = 0;
                  sprintf(nodo_der,",%s",Xexp);
                  delete []Xexp;
               }
               delete []xexp;
               return;
            }
         }

         // Separa la expresion revisando la precedencia de los operadores
         for (xi = 0; xi < 3; xi++) {
            i = 0, par = 0;
            while (xexp[i]) {
               n_e = 0;
               if (xexp[i] == '(') par ++;
               // Descarta que sea un numero en notacion exponencial
               if (i > 2 && (xexp[i] == '+' || xexp[i] == '-')) {
                  if (Es_caracter_digito(xexp[i-2]) && (xexp[i-1] == 'e' || xexp[i-1] == 'E') && (xexp[i+1])) n_e = 1;
               }
               // Busca el siguiente operador segun precedencia definidas
               if (!n_e && !par && i > 0) {
                  // Revisa si existe el operador de esa precedencia
                  if (Busca_caracter(Prioridad_operador[xi],xexp[i],pos)) {
                     Substr(xexp,0,i,nodo_izq);
                     Substr(xexp,i+1,lg,nodo_der);
                     operador[0] = xexp[i], operador[1] = 0;
                     delete []xexp;
                     return;
                  }
               }
               if (xexp[i] == ')') par --;
               i++;
            }
         }
      }
      delete []xexp;
      return;
   }
   // Expresion no reconocida
   Errores[Num_errores++] = 20;
   delete []xexp;
}




































