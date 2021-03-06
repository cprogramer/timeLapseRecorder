#include "widget.h"
#include <QApplication>
#include <QScreen>
#include "YUV4MPEG2.h"

bool recording = true;

void run() {

    YUV4MPEG2 *encoder = new YUV4MPEG2(QGuiApplication::primaryScreen()->grabWindow(0).width(),
                                          QGuiApplication::primaryScreen()->grabWindow(0).height(),
                                          24,"/home/petar/test.mpg");

    while(recording) {
        QImage mapa = QGuiApplication::primaryScreen()->grabWindow(0).toImage();
        encoder->addFrame(mapa.bits(),mapa.byteCount());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

}

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Widget w;
    w.show();

    std::thread t(run);

    return a.exec();

}
