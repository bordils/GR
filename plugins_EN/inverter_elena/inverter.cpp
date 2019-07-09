#include "inverter.h"
#include "glwidget.h"

void Inverter::onPluginLoad()
{
    // Carregar shader, compile & link 

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(QString("inverter.vert"));
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(QString("inverter.frag"));
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
     
}

void Inverter::preFrame()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	mousex = g.mapFromGlobal(QCursor::pos()).x();
	mousey = g.mapFromGlobal(QCursor::pos()).y();
	height= g.size().height();
	program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    
    program->setUniformValue("mouseX", mousex); 
    program->setUniformValue("mouseY", mousey); 
	program->setUniformValue("height", height); 
 

    
	glDisable(GL_DEPTH_TEST);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}  
 
void Inverter::postFrame()
{ 
	program->release();
	 
	glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
