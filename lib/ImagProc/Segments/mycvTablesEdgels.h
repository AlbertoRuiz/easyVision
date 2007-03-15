#ifndef _MYCV_TABLES_EDGELS_H
#define _MYCV_TABLES_EDGELS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mycvUtils.h"

/* Para el m�dulo TablesEdgels.c, se declaran las variables como tal. Para el
 * resto de m�dulos (que usan �ste), se declaran como externas:
 */
/*#ifdef _MYCV_TABLE_EDGELS_C
#define EXTERN
#else
#define EXTERN extern
#endif */

/* Maximum radius of local environment for edgel processing: */
#define MAXRADIUS  10 

/* Radio y anchura por defecto del edgel: */
#define DEFAULT_RADIUS 5
#define DEFAULT_WIDTH_EDGEL 1.2

/* ------------------------------------------------------------------------ */
/* Tablas del m�dulo. El usuario las utiliza tras inicializarlas con las    */
/* funciones del m�dulo, y s�lo deben precalcularse si cambia alg�n         */
/* par�metro (por ejemplo, el radio de la m�scara, o el ancho del edgel,    */
/* etc.):                                                                   */
/* ------------------------------------------------------------------------ */
extern float tableAngles[MAXRADIUS*4];
/* Table for theta values corresponding to indexes in the local response test.
 */
 
extern int tableEdgelProc[4*MAXRADIUS][2*MAXRADIUS+1][2*MAXRADIUS+1];
/* Tabla de entornos locales etiquetados con -INT_INFINITY (zona izquierda 
 * del edgel), INT_INFINITY (zona derecha del edgel), y -2,-1,1,2 ... para 
 * los pixels por los que pasa cerca el edgel (a menos de una distancia 
 * igual a thresh_edg_proc), con un n�mero (en valor absoluto) creciente 
 * para la distancia al centro del edgel, y con signo negativo para direcciones
 * hacia arriba y/o izquierda (es decir, que han debido ser procesadas ya si
 * al pixel se ha llegado recorriendo la imagen por filas), y positivo en 
 * caso contrario. As�, a la misma vez se caracteriza un lado y a
 * otro de la l�nea (para extraer informaci�n de colores a ambos lados 
 * del edgel, por ejemplo), y se introduce un orden de procesamiento 
 * para ir haciendo el clustering de segmentos. Por �ltimo, el valor de
 * la entrada de la tabla ser� cero para aquellos puntos a distancia mayor
 * que el radio+0.5 del centro (para hacer las m�scaras redondas, en lugar
 * de cuadradas). Hay 4*MAXRADIUS cuadr�culas (una por cada orientaci�n), 
 * cada una de tama�o [2*MAXRADIUS+1][2*MAXRADIUS+1] (el entorno local del 
 * pixel, cuadrado).
 */

typedef struct {
    int index;
    float value;
} TElementEdgelLineMaskXY;

extern TElementEdgelLineMaskXY tableEdgelLineMaskXY[2*MAXRADIUS+1][2*MAXRADIUS+1]
                      [(2*MAXRADIUS+1)*(2*MAXRADIUS+1)];
/* Tabla para computar r�pido la saliencia local en cada direcci�n. Est� 
 * indexada por:
 * - Primer y segundo �ndices: posiciones Y y X en la m�scara cuadrada.
 * - Tercer �ndice: Un valor por cada contribuci�n del pixel a una m�scara
 *   en una determinada direcci�n.
 * El contenido de cada celda indica:
 *  index: Direcci�n en la que se contribuye. -1 para indicar final.
 *  value: Valor de la contribuci�n (entre 0, para valores a distancia
 *         thresh_edg_proc de la l�nea ideal del edgel, y 1, para valores
 *         a distancia cero (en la l�nea ideal)).
 */


extern float tableEdgelLineMaskProb[4*MAXRADIUS][2*MAXRADIUS+1][2*MAXRADIUS+1];
/* Tabla directa de la anterior. Contiene el valor de la contribuci�n, para
 * cada direcci�n, de cada pixel. Indexada por:
 * - Primer �ndice: Direcci�n del edgel.
 * - Segundo y tercer �ndices: posiciones Y y X en la m�scara cuadrada.
 */

typedef struct {
    int i,j;
    int marcafin;
} TElementEdgelLineIndex;

extern TElementEdgelLineIndex tableEdgelLineIndex[4*MAXRADIUS][2][(2*MAXRADIUS+1)*(2*MAXRADIUS+1)/2];
/* Tabla inversa de la anterior, para recorrer con rapidez el entorno de un
 * pixel usando informaci�n de orientaci�n local, y en orden de menor a mayor
 * distancia del centro (utilizada, por ejemplo, para hacer el cluster de 
 * l�neas). Est� indexada por:
 * - Primer �ndice:  Indice de la direcci�n local (0 indica todo derecha, 
 *                   4*MAXRADIUS-1 indica todo izquierda, un pixel abajo).
 * - Segundo �ndice: Indica una u otra direcci�n a lo largo del edgel. 
 * - Tercer �ndice: Recorre posiciones del array.
 * En cada celda, se encuentra la posici�n (i y j) siguiente a procesar en
 * la direcci�n del edgel (en offset desde el centro). El campo marca fin
 * contiene el valor 0 en todas las posiciones, y 1 en la posici�n siguiente
 * a la �ltima (y que ya no contiene informaci�n �til).
 */

/* ------------------------------------------------------------------------ */
/* ------------ Prototipos de las funciones del m�dulo: --------------------*/
/* ------------------------------------------------------------------------ */
void mycvInitTablesEdgels(int user_radius,float user_width_edgel);
int mycvGetRadiusEdgels();
float mycvGetWidthEdgels();

#ifdef __cplusplus
}
#endif

#endif /* _MYCV_TABLES_EDGELS_H */
