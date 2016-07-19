#include <iostream>

#include <opencv2/opencv.hpp>

#include "datos.hpp"
#include "elemento_diagrama.h"

using namespace std;
using namespace cv;

void determinarPropiedadesUbicacion(Point p){}

void renderizar(Mat& matriz) //No hay pedo si tratamos de dibujar una región que no pertenece a matriz
{
    matriz = Mat(ALTURA_REGION, ANCHO_REGION, CV_8UC3, Scalar(200,200,200));
    //i inicial no debe exceder 15 o -15
    for(unsigned i=15-(desplazamientoOrigen.x % 15); i<matriz.cols; i+=15) //"generamos" un efecto de desplazamiento de la cuadrícula
        line(matriz, Point(i,0), Point(i,matriz.rows), Scalar(255,255,255), 1, 4, 0); //cuadrícula, vertical
    for(unsigned i=15-(desplazamientoOrigen.y % 15); i<matriz.rows; i+=15)
        line(matriz, Point(0,i), Point(matriz.cols,i), Scalar(255,255,255), 1, 4, 0); //cuadrícula, horizontal

    arrowedLine(matriz, Point(400-desplazamientoOrigen.x,400-desplazamientoOrigen.y), Point(500-desplazamientoOrigen.x,100-desplazamientoOrigen.y), Scalar(205,155,25), 2, CV_AA);
    arrowedLine(matriz, Point(400-desplazamientoOrigen.x,600-desplazamientoOrigen.y), Point(300-desplazamientoOrigen.x,300-desplazamientoOrigen.y), Scalar(205,155,25), 2, CV_AA);
    line(matriz, Point(-200-desplazamientoOrigen.x,-200-desplazamientoOrigen.y), Point(5000-desplazamientoOrigen.x,5000-desplazamientoOrigen.y), Scalar(205,155,250), 2, CV_AA);
    rectangle(matriz, Point(300-desplazamientoOrigen.x, -100-desplazamientoOrigen.y), Point(400-desplazamientoOrigen.x,400-desplazamientoOrigen.y), Scalar(123,211,43), 2, CV_AA);
    imshow("Diagrama", matriz);
} //actualizamos el diagrama

void manejarInputTeclado(Mat& matriz, unsigned int k) //necesitas uint, char no sirve
{
    //cout << k << "!\n";
    constexpr unsigned DESPLAZAMIENTO = 5;
    switch (k) {
    case TECLADO_FLECHA_ARRIBA:
        desplazamientoOrigen.y -= DESPLAZAMIENTO;
        break;
    case TECLADO_FLECHA_ABAJO:
        desplazamientoOrigen.y += DESPLAZAMIENTO;
        break;
    case TECLADO_FLECHA_DERECHA:
        desplazamientoOrigen.x += DESPLAZAMIENTO;
        break;
    case TECLADO_FLECHA_IZQUIERDA:
        desplazamientoOrigen.x -= DESPLAZAMIENTO;
        break;
    }
    //cout << desplazamientoOrigen << endl;

    renderizar(matriz);
}

void manejarInputMouse(int event, int x, int y, int, void*)
{
    cout << x <<","<< y <<endl;
    if(event == CV_EVENT_RBUTTONDOWN)
    {
        botonMouseDerechoAbajo = true;
        puntoClickMouseDerecho = cv::Point(x,y);
        puntoInicioDesplazamiento = desplazamientoOrigen;
    }

    if(event == CV_EVENT_RBUTTONUP)
        botonMouseDerechoAbajo = false;

    if(event == CV_EVENT_MOUSEMOVE && botonMouseDerechoAbajo) //si estamos haciendo panning
    {
        desplazamientoOrigen.x = puntoInicioDesplazamiento.x + puntoClickMouseDerecho.x - x;
        desplazamientoOrigen.y = puntoInicioDesplazamiento.y + puntoClickMouseDerecho.y - y;
        renderizar(region);
    }

    determinarPropiedadesUbicacion(Point(x,y));
}

int main()
{
    namedWindow("Diagrama");
    setMouseCallback("Diagrama", manejarInputMouse);
    renderizar(region);

    while (true)
    {
        unsigned int k = waitKey(0);
        if(-1 == k) //de este modo, si cierras la ventana efectivamente sales del ciclo
            break;
        manejarInputTeclado(region, k);
    }

    return 0;
}
