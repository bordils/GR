#include "illuminationPerFragment.h"
#include "glwidget.h"

void IlluminationPerFragment::onPluginLoad() {
	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/illuminationPerFragment/illuminationPerFragment.vert");

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/illuminationPerFragment/illuminationPerFragment.frag");

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
}

void IlluminationPerFragment::preFrame() {
	// use shader program	
	shaderProgram -> bind();

	// set uniforms
	QMatrix3x3 NM = camera() -> viewMatrix().normalMatrix();
	shaderProgram -> setUniformValue("normalMatrix", NM);

	QMatrix4x4 MV = camera() -> viewMatrix();
	shaderProgram -> setUniformValue("modelViewMatrix", MV);

	QMatrix4x4 MVP = camera() -> projectionMatrix() * camera() -> viewMatrix();
	shaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);

	shaderProgram -> setUniformValue("lightAmbient", QVector4D(0.1, 0.1, 0.1, 1.0));
	shaderProgram -> setUniformValue("lightDiffuse", QVector4D(1.0, 1.0, 1.0, 1.0));
	shaderProgram -> setUniformValue("lightSpecular", QVector4D(1.0, 1.0, 1.0, 1.0));
	shaderProgram -> setUniformValue("lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));

	shaderProgram -> setUniformValue("matAmbient",   QVector4D(0.8, 0.8, 0.6, 1.0));
	shaderProgram -> setUniformValue("matDiffuse",   QVector4D(0.8, 0.8, 0.6, 1.0));
	shaderProgram -> setUniformValue("matSpecular",  QVector4D(1.0, 1.0, 1.0, 1.0));
	shaderProgram -> setUniformValue("matShininess", GLfloat(64.0));
}

void IlluminationPerFragment::postFrame() {
	shaderProgram -> release();
}
