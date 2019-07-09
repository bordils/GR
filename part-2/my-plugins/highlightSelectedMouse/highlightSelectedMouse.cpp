#include "highlightSelectedMouse.h"
#include "glwidget.h"

void encodeID(int index, GLubyte *color);
int  decodeID(GLubyte *color);

void HighlightSelectedMouse::onPluginLoad() {
	// create, compile and link shaders
	boxVS = new QGLShader(QGLShader::Vertex, this);
	boxVS -> compileSourceFile("/home/mattia/Documents/viewer/plugins/highlightSelectedMouse/highlightSelectedMouseBox.vert");
	cout << "Box VS log:" << boxVS->log().toStdString() << endl;

	boxFS = new QGLShader(QGLShader::Fragment, this);
	boxFS -> compileSourceFile("/home/mattia/Documents/viewer/plugins/highlightSelectedMouse/highlightSelectedMouseBox.frag");
	cout << "Box FS log:" << boxFS->log().toStdString() << endl;

	boxShaderProgram = new QGLShaderProgram(this);
	boxShaderProgram -> addShader(boxVS);
	boxShaderProgram -> addShader(boxFS);
	boxShaderProgram -> link();
	cout << "Box shader program link log:" << boxShaderProgram->log().toStdString() << endl;

	// create, compile and link shaders
	colorVS = new QGLShader(QGLShader::Vertex, this);
	colorVS -> compileSourceFile("/home/mattia/Documents/viewer/plugins/highlightSelectedMouse/highlightSelectedMouseColor.vert");
	cout << "Color VS log:" << colorVS->log().toStdString() << endl;

	colorFS = new QGLShader(QGLShader::Fragment, this);
	colorFS -> compileSourceFile("/home/mattia/Documents/viewer/plugins/highlightSelectedMouse/highlightSelectedMouseColor.frag");
	cout << "Color FS log:" << colorFS->log().toStdString() << endl;

	colorShaderProgram = new QGLShaderProgram(this);
	colorShaderProgram -> addShader(colorVS);
	colorShaderProgram -> addShader(colorFS);
	colorShaderProgram -> link();
	cout << "Color shader program link log:" << colorShaderProgram->log().toStdString() << endl;

	created = false;
}

void HighlightSelectedMouse::postFrame() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	boxShaderProgram -> bind();

	GLint polygonMode;	// either GL_LINE, GL_FILL, GL_POINTS
	
	g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);		// saves the current mode
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// paint the box in wireframe mode

	drawSelectedBox();

	g.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);	// re-establish the previous mode
	boxShaderProgram -> release();
}

void HighlightSelectedMouse::drawSelectedBox() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	int selected = scene() -> selectedObject();
	if(selected >= 0 && selected<(int)scene() -> objects().size()) {
		if(!created) {
			created = true;
			createBuffers();
		}

		// set uniforms
		QMatrix4x4 MVP = camera() -> projectionMatrix() * camera() -> viewMatrix();
		boxShaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);

		const Object &obj = scene() -> objects()[selected];

		boxShaderProgram -> setUniformValue("boundingBoxMin", obj.boundingBox().min());
		boxShaderProgram -> setUniformValue("boundingBoxMax", obj.boundingBox().max());
	
		// draw bounding box
		g.glBindVertexArray(cubeVAO);
		g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);
		g.glBindVertexArray(0);
	}
}

void HighlightSelectedMouse::createBuffers() {
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

void HighlightSelectedMouse::generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_ID, GLint attributeSize) {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	g.glGenBuffers(1, &vbo_ID);
	g.glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
	g.glVertexAttribPointer(attribute_ID, attributeSize, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(attribute_ID);
}

void HighlightSelectedMouse::mouseReleaseEvent(QMouseEvent *e) {
	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	// check on the appropriate key+click combination
	if(!(e -> button()	  & Qt::LeftButton))		return;		// if it's not the left click return
	if(  e -> modifiers() & Qt::ShiftModifier)		return;		// if it's shift modifier return
	if(!(e -> modifiers() & Qt::ControlModifier))	return;		// if it's not ctrl return

	// clear the buffers with a single background color (white)
	g.glClearColor(1.0, 1.0, 1.0, 1.0);
	g.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorShaderProgram -> bind();		// bind the color shader program
	drawColorScene();					// draw every object of a different color
	colorShaderProgram -> release();	// unbind the color shader program

	int x = e -> x();						// x position of the mouse click
	int y = glwidget()->height() - e->y();	// y position of the mouse click
	GLubyte read[4];
	g.glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);	// read the color (GL_RGBA) of the clicked pixel (1, 1 is the dimension of the pixel rectangle -> 1 pixel)

	int selected = decodeID(&read[0]);
	setSelectedObject(selected);
	glwidget() -> update();					// update the scene and re-paint it
	
}

// paints the scene making sure that every objects is painted with a unique color that allows identifying the object
void HighlightSelectedMouse::drawColorScene() {
	// set uniforms
	QMatrix4x4 MVP = camera() -> projectionMatrix() * camera() -> viewMatrix();
	colorShaderProgram -> setUniformValue("modelViewProjectionMatrix", MVP);

	for(unsigned int i=0; i<scene()->objects().size(); i++) {
		GLubyte color[4];		// a color is a 4byte vector
		encodeID(i, color);
		colorShaderProgram -> setUniformValue("color", QVector4D(color[0]/255., color[1]/255., color[2]/255., 1));
		drawPlugin() -> drawObject(i);
	}
}

void encodeID(int index, GLubyte *color) {
	color[0] = color[1] = color[2] = index;		// RGB values will be: (0/255, 0/255, 0/255) for object 0; (1/255, 1/255, 1/255) for object 1, ... -> max 255 objects
}

int  decodeID(GLubyte *color) {
	if(color[0] == 255)
		return -1;				// no object will be white since the background is white

	return color[0];
}

void HighlightSelectedMouse::setSelectedObject(int selected) {
	if(selected<0 || selected>=(int)scene()->objects().size())
		selected = -1;

	scene() -> setSelectedObject(selected);
}
