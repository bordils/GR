#include "textureSplatting.h"
#include "glwidget.h"

void TextureSplatting::onPluginLoad() {
	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/textureSplatting/textureSplatting.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/textureSplatting/textureSplatting.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
	cout << "Link log:" << shaderProgram->log().toStdString() << endl;

	
	// load noise texture
	g.glActiveTexture(GL_TEXTURE0);

	QString noiseFileName = QFileDialog::getOpenFileName(0, "Open Noise Image", "/home/mattia/Documents/viewer/Textures", "Image file (*.png *jpg)");
	QImage img3(noiseFileName);
	QImage im3 = QGLWidget::convertToGLFormat(img3);
	
	g.glGenTextures(1, &noiseID);
	g.glBindTexture(GL_TEXTURE_2D, noiseID);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im3.width(), im3.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im3.bits());
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	

	// load texture 1
	g.glActiveTexture(GL_TEXTURE1);

	QString rockFileName = QFileDialog::getOpenFileName(0, "Open Rock Image", "/home/mattia/Documents/viewer/Textures", "Image file (*.png *jpg)");
	QImage img0(rockFileName);
	QImage im0 = QGLWidget::convertToGLFormat(img0);
	
	g.glGenTextures(1, &textureID_0);
	g.glBindTexture(GL_TEXTURE_2D, textureID_0);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glBindTexture(GL_TEXTURE_2D, 0);

	
	// load texture 2
	g.glActiveTexture(GL_TEXTURE2);

	QString grassFileName = QFileDialog::getOpenFileName(0, "Open Grass Image", "/home/mattia/Documents/viewer/Textures", "Image file (*.png *jpg)");
	QImage img1(grassFileName);
	QImage im1 = QGLWidget::convertToGLFormat(img1);
	
	g.glGenTextures(1, &textureID_1);
	g.glBindTexture(GL_TEXTURE_2D, textureID_1);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	shaderProgram -> bind();
	
	// set uniforms
	shaderProgram -> setUniformValue("noise0", 0);		// noise texture unit
	shaderProgram -> setUniformValue("rock1" , 1);		// rock texture unit
	shaderProgram -> setUniformValue("grass2", 2);		// grass texture unit

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	shaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);
	shaderProgram -> setUniformValue("normalMatrix", camera() -> viewMatrix().normalMatrix());

	// bind textures
	g.glActiveTexture(GL_TEXTURE0);
	g.glBindTexture(GL_TEXTURE_2D, noiseID);

	g.glActiveTexture(GL_TEXTURE1);
	g.glBindTexture(GL_TEXTURE_2D, textureID_0);

	g.glActiveTexture(GL_TEXTURE2);
	g.glBindTexture(GL_TEXTURE_2D, textureID_1);
}

void TextureSplatting::postFrame() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	// unbind shader
	shaderProgram -> release();

	// unbind textures
	g.glActiveTexture(GL_TEXTURE0);
	g.glBindTexture(GL_TEXTURE_2D, 0);

	g.glActiveTexture(GL_TEXTURE1);
	g.glBindTexture(GL_TEXTURE_2D, 0);

	g.glActiveTexture(GL_TEXTURE2);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	
}
