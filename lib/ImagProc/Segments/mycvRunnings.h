#ifndef _MYCV_RUNNINGS_H
#define _MYCV_RUNNINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Tipo de celda elemental de la matriz que devuelve la funci�n createRunLine:*/
typedef struct {
    int y,x;
} TRunPos;

/* --------------- Prototipos de las funciones del m�dulo: ------------------ */
/* Funci�n que crea y devuelve una matriz rectangular para acceder, de modo 
 * ordenado, a los pixels que rodean a una l�nea. En width pasamos la anchura
 * (en direcci�n perpendicular, pero en unidades de pixel, que no tiene porqu�
 * coincidir con la eucl�dea a la l�nea que deseamos. La funci�n devuelve
 * una matriz de dimensiones runWidth x runLength, donde runWidth ser� siempre
 * 2*width+1 (la l�nea estar� en la fila width, los pixels por encima de ella
 * en las filas 0..width-1, y los pixels por debajo en width+1..2*width). La
 * variable runLength ser� el maximo(abs(x1-x2)+1,abs(y1-y2)+1), puesto que
 * la l�nea se recorre con el algoritmo de Bresenham, que genera pixels 
 * 8-conectados. 
 * La funci�n asegura que se devuelve una matriz rectangular de posiciones
 * que recorre de modo denso el rect�ngulo que rodea (sim�tricamente) a la
 * l�nea de entrada. Pero, ojo, porque el par�metro de entrada width no indica
 * distancia eucl�dea (en perpendicular) a la recta, sino simplemente orden
 * de distancia a esta. La distancia coincidir� con la eucl�dea s�lo para
 * rectas horizontales y verticales.
 */
TRunPos **createRunLine(int x1,int y1,int x2,int y2,int width,
                        int *runWidth,int *runLength);
                            
/* Esta funci�n libera una matriz de accesos devuelta por la funci�n 
 * createRunLine anterior: 
 */                            
void freeRunLine(TRunPos **runLine,int width);

/* Esta funci�n crea un array unidimensional de recorrido alrededor de un
 * pixel, hasta un radio m�ximo pedido. Los desplazamientos x e y son
 * relativos a un centro (0,0).
 */
TRunPos *createRunAround(float radius,int *runLength);

/* Esta funci�n libera un vector de accesos devuelto por la funci�n 
 * createRunAround anterior: 
 */                            
void freeRunAround(TRunPos *runAround);

#ifdef __cplusplus
}
#endif

#endif /* _MYCV_RUNNINGS_H */
