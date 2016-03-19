#include "YUV4MPEG2.h"

YUV4MPEG2::YUV4MPEG2(unsigned int width, unsigned int height, double fps) {

    this->width = width;
    this->height = height;
    this->fps = fps;

    buffer = new unsigned char[3*width*height + 2*width];
    multiThreaded = true;

    createHeader();

}

YUV4MPEG2::YUV4MPEG2(unsigned int width, unsigned int height, double fps,const char fname[]) {

    this->width = width;
    this->height = height;
    this->fps = fps;

    buffer = new unsigned char[3*width*height + 2*width];
    multiThreaded = true;

    createHeader();
    setOutput(fname);

}

YUV4MPEG2::~YUV4MPEG2() {

    delete buffer;

}

/* Thread execution function. Converts a chunk of frame to YCbCr */
void YUV4MPEG2::tProcess(const unsigned char *input,int offset,int chunk) {
    int i,j;

    for(i=0,j=offset/4 ;i < chunk; i+=4,j++) {
        convert(&input[i],&buffer[j]);
    }

}

/* Adds a single frame from raw BGR32 pixel array */
void YUV4MPEG2::addFrame(const unsigned char *pixelData, unsigned int byteCount) {

    if(!output.is_open()) {
        return;
    }

    int nThreads = QThread::idealThreadCount();

    if(!multiThreaded || nThreads == -1) {
        nThreads = 1;
    }

    int offset = 0;
    int chunk = byteCount / nThreads;

    std::vector<std::thread*> threads;

    /* Split the job into threads */
    for(int i=0;i<nThreads;i++) {
       threads.push_back(new std::thread(&YUV4MPEG2::tProcess,
                                    this,
                                    &pixelData[offset],
                                    offset,chunk));
        offset += chunk;
    }

    /* Wait for all threads to finish before proceding */
    for(std::thread* x: threads) {
        x->join();
        delete x;
    }

    output.write("FRAME\n",6);
    output.write((const char*)buffer,3*width*height);

}

/* Adds a single frame from a QImage object */
void YUV4MPEG2::addFrame(const QImage &image) {

    const unsigned char *pixelData = image.bits();
    int byteCount = image.byteCount();

    addFrame(pixelData,byteCount);

}

/* Converts a single BGR32 pixel to YCbCr 4:4:4 */
inline void YUV4MPEG2::convert(const unsigned char *input, unsigned char *output) {

    int p = width*height;

    /* Y = 0.299*R + 0.587*G + 0.114*B */
    output[0]  = (unsigned char)(0.299*input[2] + 0.587*input[1] + 0.114*input[0]);
    output[p] = (unsigned char)(128 + -0.16874*input[2] - 0.33126*input[1] + 0.5*input[0]);
    output[2*p] = (unsigned char)(128 + 0.5*input[2] - 0.41869*input[1] - 0.08131*input[0]);

}

/* Generate file header metadata */
void YUV4MPEG2::createHeader() {

    sprintf(header,"YUV4MPEG2 W%u H%u F%d:%d Ip A0:0 C444\n",width,height,(int)fps,1);

}

void YUV4MPEG2::setMultiThreaded(bool setting) {
    multiThreaded = setting;
}

bool YUV4MPEG2::isMultiThreaded() {
    return multiThreaded;
}
