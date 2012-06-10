#ifndef GLFRAME_H
#define GLFRAME_H

#include <QGLWidget>
#include "glrenderthread.h"

class QGLFrame : public QGLWidget
{
    Q_OBJECT
public:
    explicit QGLFrame(QWidget *parent = 0);
    ~QGLFrame();
    void initRenderThread(void);
    void stopRenderThread(void);

signals:

public slots:

protected:
    void closeEvent(QCloseEvent *evt);
    void resizeEvent(QResizeEvent *evt);
    void paintEvent(QPaintEvent *);

    QGLRenderThread RenderThread;

private:
};

#endif // GLFRAME_H
