#include "animateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad() {
	// load and compile vertex shader
	QString vs_source = "#version 330 core\n"
						"layout (location = 0) in vec3 vertex;\n"
						"layout (location = 1) in vec3 normal;\n"
						"layout (location = 2) in vec3 color;\n"
						"out vec4 frontColor;\n"
						"uniform mat4 modelViewProjectionMatrix;\n"
						"uniform mat3 normalMatrix;\n"
						"uniform float pi = 3.14159;\n"
						"uniform float amplitude = 0.1;\n"
						"uniform float freq = 1;\n"
						"uniform float time;\n"
						"void main() {\n"
						"	float dt = amplitude * sin(2 * pi * freq * time);\n"
						"	vec3 N = normalize(normalMatrix * normal);\n"
						"	frontColor = vec4(1.0, 1.0, 1.0, 1.0) * N.z;\n"
						"	gl_Position = modelViewProjectionMatrix * vec4(vertex + normal*dt, 1.0);\n"
						"}\n";
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceCode(vs_source);
	cout << "VS log:" << vs->log().toStdString() << endl;


	// load and compile fragment shader
	QString fs_source = "#version 330 core\n"
						"in vec4 frontColor;\n"
						"out vec4 fragColor;\n"
						"void main() {\n"
						"    fragColor = frontColor;\n"
						"}\n";
	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceCode(fs_source);
	cout << "FS log:" << fs->log().toStdString() << endl;


	// create shader program, add shaders and link
	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
	cout << "Link log:" << shaderProgram->log().toStdString() << endl;


	//start timer
	elapsedTimer.start();
	// keep repainting
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
	timer->start();
}

void AnimateVertices::preFrame() {
	// bind shader
	shaderProgram -> bind();

	// set uniforms
	shaderProgram -> setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));

	QMatrix3x3 NM = camera() -> viewMatrix().normalMatrix();
	shaderProgram -> setUniformValue("normalMatrix", NM);

	QMatrix4x4 MVP = camera() -> projectionMatrix() * camera() -> viewMatrix();
	shaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);
}

void AnimateVertices::postFrame() {
	// unbind shader
	shaderProgram -> release();
}

