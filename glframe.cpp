#include <QResizeEvent>

#include "glframe.h"

QGLFrame::QGLFrame(QWidget *parent) :
    QGLWidget(parent),
    RenderThread(this)
{
    setAutoBufferSwap(false);
}

QGLFrame::~QGLFrame()
{
}

void QGLFrame::initRenderThread(void)
{
    doneCurrent();
    RenderThread.start();
}

void QGLFrame::stopRenderThread(void)
{
    RenderThread.stop();
    RenderThread.wait();
}

void QGLFrame::resizeEvent(QResizeEvent *evt)
{
    RenderThread.resizeViewport(evt->size());
}

void QGLFrame::paintEvent(QPaintEvent *)
{
    // Do nothing. Let the thread do the work
}

void QGLFrame::closeEvent(QCloseEvent *evt)
{
    stopRenderThread();
    QGLWidget::closeEvent(evt);
}
