#include "reflection.h"
#include "glwidget.h"

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

const QString VS_PATH = "/home/mattia/Documents/viewer/plugins/reflection/reflection.vert";
const QString FS_PATH = "/home/mattia/Documents/viewer/plugins/reflection/reflection.frag";

void Reflection::onPluginLoad() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	glwidget() -> resize(IMAGE_WIDTH, IMAGE_HEIGHT);

	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile(VS_PATH);
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile(FS_PATH);
	cout << "FS log:" << fs->log().toStdString() << endl;

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
	cout << "Link log:" << shaderProgram->log().toStdString() << endl;

	// texture setup
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures(1, &textureID);
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	
}

bool Reflection::paintGL() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	// 1. Draw scene
	g.glClearColor(0.0, 0.0, 0.0, 0.0);		// black
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	drawPlugin() -> drawScene();

	// get texture
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
	g.glGenerateMipmap(GL_TEXTURE_2D);

	
	// 2. Draw quad using texture
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	shaderProgram -> bind();
	shaderProgram -> setUniformValue("colorMap", 0);
	shaderProgram -> setUniformValue("SIZE", float(IMAGE_WIDTH));  
 
	// quad covering viewport 
	shaderProgram -> setUniformValue("modelViewProjectionMatrix", QMatrix4x4() );  
	drawRectangle();
	shaderProgram -> release();
	g.glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Reflection::drawRectangle() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	static bool created = false;
	static GLuint VAO_rect;

	// 1. create VBO buffers
	if(!created) {
		created = true;

		// create and bind empty VAO
		g.glGenVertexArrays(1, &VAO_rect);
		g.glBindVertexArray(VAO_rect);

		// Create VBO with (x,y,z) coordinates
		float coords[] = { -1.0, -1.0, 0.0, 
		                    1.0, -1.0, 0.0, 
         		           -1.0,  1.0, 0.0, 
                 		    1.0,  1.0, 0.0 };

		GLuint VBO_coords;
		g.glGenBuffers(1, &VBO_coords);
		g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
		g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
		g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		g.glEnableVertexAttribArray(0);
		g.glBindVertexArray(0);
	}
}
