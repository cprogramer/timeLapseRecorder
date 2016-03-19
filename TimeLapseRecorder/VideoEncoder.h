#ifndef VIDEOENCODER_H
#define VIDEOENCODER_H
#define MAX_HEADER 100
#include <iostream>
#include <fstream>
#include <QImage>

class VideoEncoder {
public:

    virtual void addFrame(const unsigned char *pixelData,unsigned int byteCount) {}
    virtual void addFrame(const QImage& image) {}

    ~VideoEncoder() {
        output.close();
    }

    void setOutput(const char fname[]);

    double getFps() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

protected:

    std::ofstream output;

    char header[MAX_HEADER];

    double fps;

    unsigned int byteCount;
    unsigned int width;
    unsigned int height;

};

#endif // VIDEOENCODER_H
