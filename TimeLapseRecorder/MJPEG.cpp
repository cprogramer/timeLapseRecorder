#include "MJPEG.h"

MJPEG::MJPEG(unsigned int width, unsigned int height, double fps) {

    this->width = width;
    this->height = height;
    this->fps = fps;

}

MJPEG::MJPEG(unsigned int width, unsigned int height, double fps, const char fname[]) {

    this->width = width;
    this->height = height;
    this->fps = fps;

    setOutput(fname);

}

MJPEG::~MJPEG() {

}

void MJPEG::addFrame(const QImage &image) {

    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);

    image.save(&buffer,"JPG");

    output.write(buffer.buffer().data(),buffer.buffer().size());

}

void MJPEG::addFrame(const unsigned char *pixelData, unsigned int byteCount) {

    QImage data(width,height,QImage::Format_RGB32);
    for(unsigned int i=0;i<byteCount;i++) {
        data.bits()[i] = pixelData[i];
    }
    addFrame(data);

}
