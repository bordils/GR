#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad() {
	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/drawBoundingBox/drawBoundingBox.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/drawBoundingBox/drawBoundingBox.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
	cout << "Link log:" << shaderProgram->log().toStdString() << endl;

	created = false;
}


void DrawBoundingBox::postFrame() {
	shaderProgram -> bind();

	GLint polygonMode;	// either GL_LINE, GL_FILL, GL_POINTS

	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);		// saves the current mode
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// paint the box in wireframe mode

	drawBoxes();

	g.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);	// re-establish the previous mode
	shaderProgram -> release();
}

void DrawBoundingBox::drawBoxes() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	// create buffers
	if(!created) {
		created = true;
		createBuffers();
	}

	// set uniforms
	QMatrix4x4 MVP = camera() -> projectionMatrix() * camera() -> viewMatrix();
	shaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);

	
	// paint boxes...
	Scene *scn = scene();
	const vector<Object> allObjects = scn->objects();
	
	// ...for every object in the scene
	for(int i=0; i<(int)allObjects.size(); i++) {
		// set uniforms for the VS to use
		shaderProgram -> setUniformValue("boundingBoxMin", allObjects[i].boundingBox().min());
		shaderProgram -> setUniformValue("boundingBoxMax", allObjects[i].boundingBox().max());
		
		// draw bounding box
		g.glBindVertexArray(cubeVAO);
		g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);	// attention! It's two triangle strips:
													// 1: Front, Bottom, Back, Top
													// 2: Left,  Bottom, Right
		
		g.glBindVertexArray(0);		
	}
}

void DrawBoundingBox::createBuffers() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	// data
	GLfloat cubeVertices[] = {  1.0, 1.0, 1.0,		// 1: Front, Bottom, Back, Top
								0.0, 1.0, 1.0,
								1.0, 0.0, 1.0,
								0.0, 0.0, 1.0,					
								1.0, 0.0, 0.0,
								0.0, 0.0, 0.0,
								1.0, 1.0, 0.0,
								0.0, 1.0, 0.0,
								1.0, 1.0, 1.0,
								0.0, 1.0, 1.0,

								0.0, 1.0, 1.0,		// 2: Left,  Bottom, Right
								0.0, 1.0, 0.0,
								0.0, 0.0, 1.0,
								0.0, 0.0, 0.0,
								1.0, 0.0, 1.0,
								1.0, 0.0, 0.0,
								1.0, 1.0, 1.0,
								1.0, 1.0, 0.0  };


	GLfloat cubeColors[]   = {	1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0,
								1.0, 0.0, 0.0  };

	// box VAO
	g.glGenVertexArrays(1, &cubeVAO);
	g.glBindVertexArray(cubeVAO);

	// box VBOs
	generateVBO(verticesVBO, 18*3, &cubeVertices[0], 0, 3);		// arg1: VBO to be filled
																// arg2: VBO size in terms of elements
																// arg3: data array
																// arg4: location in the shader
																// arg5: # of elements of the attribute (e.g. 3 for the vertex)
	generateVBO(colorVBO,	 18*3, &cubeColors[0]  , 2, 3);
}

void DrawBoundingBox::generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_ID, GLint attributeSize) {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	g.glGenBuffers(1, &vbo_ID);
	g.glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
	g.glVertexAttribPointer(attribute_ID, attributeSize, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(attribute_ID);
}




