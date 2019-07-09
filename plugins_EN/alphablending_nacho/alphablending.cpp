#include "alphablending.h"
#include "glwidget.h"

void AlphaBlending::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("alphablending.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("alphablending.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
    timer->start();
}

void AlphaBlending::preFrame() 
{
    glDisable(GL_DEPTH_TEST);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}

void AlphaBlending::postFrame() 
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

void AlphaBlending::mouseMoveEvent(QMouseEvent * e)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Llegir posicio del cursor
    int x = e->x();
    int y = glwidget()->height()-e->y();

    program->bind();
    program->setUniformValue("mouse", QVector2D(x, y));
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(alpha-blending, AlphaBlending)   // plugin name, plugin class
#endif

