#include "VideoEncoder.h"

/* Creates a file with header for the file format */
void VideoEncoder::setOutput(const char fname[]) {

    output.close();

    output.open(fname,std::ios::in | std::ios::binary | std::ios::trunc);

    output.write(header,strlen(header));
}

double VideoEncoder::getFps() const {
    return fps;
}

unsigned int VideoEncoder::getHeight() const {
    return height;
}

unsigned int VideoEncoder::getWidth() const {
    return width;
}


