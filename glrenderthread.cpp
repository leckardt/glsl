#include <QGLShader>
#include <QFileInfo>

#include "glframe.h"

#include "glrenderthread.h"
#include <GL/glu.h>

QGLRenderThread::QGLRenderThread(QGLFrame *parent) :
    QThread(),
    GLFrame(parent)
{
    doRendering = true;
    doResize = false;
    doReloadShader = true;
    FrameCounter=0;

    ShaderProgram = NULL;
    VertexShader = FragmentShader = NULL;

    vshader = "./Basic.vsh";
    fshader = "./Basic.fsh";
    watcher = new QFileSystemWatcher();
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(reloadShader()));
}

void QGLRenderThread::resizeViewport(const QSize &size)
{
    w = size.width();
    h = size.height();
    doResize = true;
}

void QGLRenderThread::stop()
{
    doRendering = false;
}


void QGLRenderThread::run()
{
    GLFrame->makeCurrent();
    GLInit();

    while (doRendering)
        {
        if(doResize)
            {
            GLResize(w, h);
            doResize = false;
            }
	if (doReloadShader)
	{
    		LoadShader();
		doReloadShader = false;
		FrameCounter = 0;
	}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        paintGL(); // render actual frame

        FrameCounter++;
        GLFrame->swapBuffers();

        msleep(16); // wait 16ms => about 60 FPS
        }
}


void QGLRenderThread::GLInit(void)
{
    glClearColor(0.25f, 0.25f, 0.4f, 0.0f);
}


void QGLRenderThread::GLResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.,((GLfloat)width)/((GLfloat)height),0.1f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void QGLRenderThread::paintGL(void)
{
    ShaderProgram->setUniformValue( "frameCounter", FrameCounter );
    ShaderProgram->setUniformValue( "width", w );
    ShaderProgram->setUniformValue( "height", h );

    glTranslatef(0.0f, 0.0f, -1.0f);            // move 5 units into the screen
//    glRotatef(FrameCounter,0.0f,0.0f,0.5f);     // rotate z-axis
    glBegin(GL_QUADS);
        glColor3f(1.,0.,0.);
	glVertex3f(-1.0, -1.0,0.0);
        glVertex3f(1.0, -1.0,0.0);
        glVertex3f(1.0, 1.0,0.0);
        glVertex3f(-1.0, 1.0,0.0);
    glEnd();
}


void QGLRenderThread::LoadShader()
{
    if(ShaderProgram)
        {
        ShaderProgram->release();
        //ShaderProgram->removeAllShaders();
	delete ShaderProgram;
	ShaderProgram = new QGLShaderProgram;
        }
    else ShaderProgram = new QGLShaderProgram;

    if(VertexShader)
        {
        delete VertexShader;
        VertexShader = NULL;
        }

    if(FragmentShader)
        {
        delete FragmentShader;
        FragmentShader = NULL;
        }

    // load and compile vertex shader
    QFileInfo vsh(vshader);
    if(vsh.exists())
        {
        VertexShader = new QGLShader(QGLShader::Vertex);
        if(VertexShader->compileSourceFile(vshader))
            ShaderProgram->addShader(VertexShader);
        else qWarning() << "Vertex Shader Error" << VertexShader->log();
        }
    else qWarning() << "Vertex Shader source file " << vshader << " not found.";


    // load and compile fragment shader
    QFileInfo fsh(fshader);
    if(fsh.exists())
        {
        FragmentShader = new QGLShader(QGLShader::Fragment);
        if(FragmentShader->compileSourceFile(fshader))
            ShaderProgram->addShader(FragmentShader);
        else qWarning() << "Fragment Shader Error" << FragmentShader->log();
        }
    else qWarning() << "Fragment Shader source file " << fshader << " not found.";

    if(!ShaderProgram->link())
        {
        qWarning() << "Shader Program Linker Error" << ShaderProgram->log();
        }
    else ShaderProgram->bind();

    //clear watched files
    watcher->removePaths(watcher->files());
    //watch shader files
    watcher->addPath(vshader);
    watcher->addPath(fshader);
}

void QGLRenderThread::reloadShader()
{
	QFile* vshFile = new QFile(vshader);
	QFile* fshFile = new QFile(fshader);
	while ( !vshFile->exists() || !fshFile->exists() )
		;
	doReloadShader = true;
}
