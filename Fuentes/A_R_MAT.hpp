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



   /// Arreglo que contiene el nombre de las constantes usas y su valor numerico correspondiente
   const char *Constantes[] = {
      "M_PI",         "3.14159265358979323846",   // Pi
      "M_PI_2",       "1.57079632679489661923",   // Pi/2
      "M_PI_4",       "0.785398163397448309616",  // Pi/4
      "M_1_PI",       "0.318309886183790671538",  // 1/Pi
      "M_2_PI",       "0.636619772367581343076",  // 2/Pi
      "M_1_SQRTPI",   "0.707106781186547524401",  // 1/sqrt(Pi)
      "M_2_SQRTPI",   "1.12837916709551257390",   // 2/sqrt(Pi)
      "M_E",          "2.71828182845904523536",   // e
      "M_LOG2E",      "1.44269504088896340736",   // log(e)
      "M_LOG10E",     "0.434294481903251827651",  // log10(e)
      "M_LN2",        "0.693147180559945309417",  // ln(2)
      "M_LN10",       "2.30258509299404568402",  // ln(10)
      "",""
   };

//////////////////////////////////////////////////////////////////////////////////////////
// Estas son usadas por los programas Analiza expresion y calculadora en notación polaca   
//////////////////////////////////////////////////////////////////////////////////////////

   /// Arreglo que contiene el nombre de las funciones permitidas y su numero de parametros
   const char *Funciones[] = {
      "sinl",   "1",                    // seno
      "cosl",   "1",                    // coseno
      "tanl",   "1",                    // tangente
      "asinl",  "1",                    // arco seno
      "acosl",  "1",                    // arco coseno
      "atanl",  "1",                    // arco tangente
      "sinhl",  "1",                    // seno hiperbolico
      "coshl",  "1",                    // coseno hiperbolico
      "tanhl",  "1",                    // tangente hiperbolico
      "fabsl",  "1",                    // valor absoluto
      "floorl", "1",                    // El mayor entero menor o igual a
      "fmodl",  "2",                    // Calcula el modulo de X/Y
      "expl",   "1",                    // exponencia e a la x
      "ldexpl", "2",                    // Calcula X  por 2 exponente a la Y
      "logl",   "1",                    // logaritmo natural
      "log10l", "1",                    // logaritmo base 10
      "sqrtl",  "1",                    // raiz cuadrada
      "powl",   "2",                    // x a la y
      "pow10l", "1",                    // 10 a la X
//////////////////////////////////////////////////////////////////////////////////
// Funciones agregadas para el evaluador de expresiones no son propias de       //
// Borland.                                                                     //
//                                                                              //
      "factl",  "1",                    // Factorial de x
      "invl",   "1",                    // Inverso de x
      "sigl",   "1",                    // Signo de X (1 si X > 0, -1 si X < 0 y 0 si X es cero)
      "sqrl",   "1",                    // Cuadrado de X
      "trcl",   "1",                    // Parte entera de X
      "decl",   "1",                    // Parte decimal de X
      "maxl",   "2",                    // Maximo entre X e Y
      "minl",   "2",                    // Minimo entre X e Y
//      "gra",   "0",                    // funciones trigonometricas en gradianes
//      "rad",   "0",                    // funciones trigonometricas en radianes
//      "deg",   "0",                    // funciones trigonometricas en grados
      "P",     "2",                    // Se usara para funciones paramétricas
      "F",     "1",                    // Se usara para funciones auxiliares unicamente
//                                                                               //
/////////////////////////////////////////////////////////////////////////////////

#ifdef FUNCIONES_DEFINIDAS_USUARIO
//////////////////////////////////////////////////////////////////////////////////
// Funciones definidas por el usuario                                           //
//                                                                              //
      "F_U01",  "1",                    // Función definida por el usuario
      "F_U02",  "1",                    // Función definida por el usuario
      "F_U03",  "1",                    // Función definida por el usuario
      "F_U04",  "1",                    // Función definida por el usuario
      "F_U05",  "1",                    // Función definida por el usuario
      "F_U06",  "1",                    // Función definida por el usuario
      "F_U07",  "1",                    // Función definida por el usuario
      "F_U08",  "1",                    // Función definida por el usuario
      "F_U09",  "1",                    // Función definida por el usuario
//////////////////////////////////////////////////////////////////////////////////
#endif
      "",""
   };
