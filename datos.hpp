#define ANCHO_REGION 800
#define ALTURA_REGION 500

#define TECLADO_FLECHA_ARRIBA 2490368
#define TECLADO_FLECHA_ABAJO 2621440
#define TECLADO_FLECHA_IZQUIERDA 2424832
#define TECLADO_FLECHA_DERECHA 2555904

#include <opencv2/opencv.hpp>

/*Esta es de las variables más importantes del diagrama. Todos los "widgets" necesitan conocer su valor
 * para ser dibujados. Ejemplo:
 * arrowedLine(matriz, Point(400-desplazamientoOrigen.x,400-desplazamientoOrigen.y),
 * Point(500-desplazamientoOrigen.x,100-desplazamientoOrigen.y), Scalar(205,155,25), 2, CV_AA);
 * Esta sintaxis genera un efecto visual de desplazamiento sobre la matriz. Realmente los objetos tienen una posición absoluta,
 * pero los redibujamos con una posición relativa diferente (a la matriz de despliegue (región))
*/
cv::Point desplazamientoOrigen(0,0);
cv::Mat region(ALTURA_REGION, ANCHO_REGION, CV_8UC3, cv::Scalar(200,200,200)); //debe tener un scope global

bool botonMouseIzquierdoAbajo=false;
bool botonMouseDerechoAbajo=false;
cv::Point puntoClickMouseDerecho(0,0);
cv::Point puntoInicioDesplazamiento(0,0);

