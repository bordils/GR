#include "model_info_2.h"
#include "glwidget.h"

void Model_info_2::onPluginLoad() {
	nObjects_str   = "Objects: \t%1";
	nPolygons_str  = "Polygons: \t%1";
	nVerteces_str  = "Vertices: \t%1";
	nTriangles_str = "Triangles: \t%1";
	percentage_str = "Percentage of triangles: \t%1%";

	updateModelInfo();

	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/model_info_2/model_info_2.vert");

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/model_info_2/model_info_2.frag");

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();
}

void Model_info_2::postFrame() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	const int SIZE=1024;
	
	// create and paint a white image
	QImage image(SIZE, SIZE, QImage::Format_RGB32);
	image.fill(Qt::white);
	QPainter painter(&image);

	// set font properties
	QFont font;
	font.setPixelSize(32);
	painter.setFont(font);
	painter.setPen(QColor(50, 50, 50));

	// location where the text will be drawn
	int x = 15;
	int y = 50;

	// draw text
	painter.drawText(x, y, 	   nObjects_str.arg(nObjects));
	painter.drawText(x, y+40,  nPolygons_str.arg(nPolygons));
	painter.drawText(x, y+80,  nVerteces_str.arg(nVerteces));
	painter.drawText(x, y+120, nTriangles_str.arg(nTriangles));
	painter.drawText(x, y+160, percentage_str.arg(100*((float)nTriangles)/nPolygons));
	painter.end();


	// create texture
	const int textureUnit = 5;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	QImage im0 = QGLWidget::convertToGLFormat(image);
	g.glGenTextures(1, &textureID);
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glGenerateMipmap(GL_TEXTURE_2D);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// draw quad using texture
	shaderProgram -> bind();
	shaderProgram -> setUniformValue("colorMap", textureUnit);
	shaderProgram -> setUniformValue("WIDTH",  float(g.width()));
	shaderProgram -> setUniformValue("HEIGHT", float(g.height()));
	drawRectangle();
	shaderProgram -> release();
	g.glBindTexture(GL_TEXTURE_2D, 0);
	g.glDeleteTextures(1, &textureID);
}

void Model_info_2::onObjectAdd() {
	updateModelInfo();
}

// calculates the required info about the scene and stores them
void Model_info_2::updateModelInfo() {
	Scene* s = scene();

	nObjects = s->objects().size();

	// for every object in the scene
	for(int i=0; i<nObjects; i++) {
		// one at the time get a reference to the object
		const Object &obj = s->objects()[i];

		// for every face of that object
		for(int j=0; j<(int)obj.faces().size(); j++) {
			// count a polygon
			nPolygons++;			

			// get a reference to the face
			const Face &face = obj.faces()[j];
			
			int faceVertices = face.numVertices();
			
			// update the total number of vertices
			nVerteces += faceVertices;

			// if the face is a triangle, update the triangle count
			if(faceVertices == 3)
				nTriangles++;
		}
	}
}

void Model_info_2::drawRectangle() {

	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	static bool created = false;
	static GLuint VAO_rectangle;
	
	// 1. create VBO buffers
	if(!created) {
		created = true;
		
		g.glGenVertexArrays(1, &VAO_rectangle);
		g.glBindVertexArray(VAO_rectangle);
		
		float z = -0.99999;
		
		// create VBOs with (x, y, z) coordinates
		float coords[] = { -1, -1, z,
							1, -1, z,
						   -1,  1, z,
							1,  1, z  };

		GLuint VBO_coords;
		g.glGenBuffers(1, &VBO_coords);
		g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
		g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
		g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		g.glEnableVertexAttribArray(0);
		g.glBindVertexArray(0);
	}

	// draw
	g.glBindVertexArray(VAO_rectangle);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	g.glBindVertexArray(0);
}
