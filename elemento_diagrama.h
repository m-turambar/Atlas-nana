#ifndef ELEMENTO_DIAGRAMA_H
#define ELEMENTO_DIAGRAMA_H

#include <vector>
#include <opencv2/opencv.hpp>

class elemento_diagrama
{
public:
    elemento_diagrama();
    virtual ~elemento_diagrama();

protected:

private:
    std::vector<cv::Point> puntos_clave;
};

#endif // ELEMENTO_DIAGRAMA_H
