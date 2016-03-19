#ifndef YUV4MPEG2_H
#define YUV4MPEG2_H
#include "VideoEncoder.h"
#include <thread>
#include <QThread>
#include <vector>

class YUV4MPEG2 : public VideoEncoder {
public:

    YUV4MPEG2(unsigned int width,unsigned int height,double fps);
    YUV4MPEG2(unsigned int width,unsigned int height,double fps,const char fname[]);

    ~YUV4MPEG2();

    void addFrame(const unsigned char *pixelData,unsigned int byteCount);
    void addFrame(const QImage& image);

    void setMultiThreaded(bool setting);
    bool isMultiThreaded();


private:

    unsigned char *buffer;
    bool multiThreaded;

    void tProcess(const unsigned char *input,int offset,int chunk);
    inline void convert(const unsigned char *input,unsigned char *output);
    void createHeader();


};

#endif // YUV4MPEG2_H
