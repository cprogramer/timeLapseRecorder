#ifndef MJPEG_H
#define MJPEG_H
#include "VideoEncoder.h"
#include <QBuffer>

class MJPEG : public VideoEncoder {
public:
    MJPEG(unsigned int width,unsigned int height,double fps);
    MJPEG(unsigned int width,unsigned int height,double fps,const char fname[]);

    ~MJPEG();

    void addFrame(const unsigned char *pixelData,unsigned int byteCount);
    void addFrame(const QImage& image);

private:

};

#endif // MJPEG_H
