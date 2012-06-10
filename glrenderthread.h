#ifndef GLRENDERTHREAD_H
#define GLRENDERTHREAD_H

#include <QThread>
#include <QGLWidget>
#include <QFileSystemWatcher>

class QGLFrame;
class QSize;
class QGLShaderProgram;
class QGLShader;

class QGLRenderThread : public QThread
{
    Q_OBJECT
public:
    explicit QGLRenderThread(QGLFrame *parent = 0);
    void resizeViewport(const QSize &size);
    void run(void);
    void stop(void);
    void LoadShader();

protected:
    void GLInit(void);
    void GLResize(int width, int height);
    void paintGL(void);

private:
    bool doRendering, doResize, doReloadShader;
    int w, h, FrameCounter;

    QGLFrame *GLFrame;

    QGLShaderProgram *ShaderProgram;
    QGLShader *VertexShader, *FragmentShader;

    QString vshader, fshader;
    QFileSystemWatcher *watcher;

signals:

public slots:
    void reloadShader();

};

#endif // GLRENDERTHREAD_H
