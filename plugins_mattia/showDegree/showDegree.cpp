#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad() {
	// calculate average degree
	calculateAvgDeg();

	// create, compile and link shaders
	vs = new QGLShader(QGLShader::Vertex, this);
	vs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/showDegree/showDegree.vert");

	fs = new QGLShader(QGLShader::Fragment, this);
	fs -> compileSourceFile("/home/mattia/Documents/viewer/plugins/showDegree/showDegree.frag");

	shaderProgram = new QGLShaderProgram(this);
	shaderProgram -> addShader(vs);
	shaderProgram -> addShader(fs);
	shaderProgram -> link();	
}

void ShowDegree::postFrame() {
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
	painter.drawText(x, y, QString("%1").arg(averageDeg));
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

void ShowDegree::calculateAvgDeg() {
	const Object &obj = scene() -> objects()[0];
	const vector<Vertex> &ver = obj.vertices();

	// counter vector
	int cnt[ver.size()];
	// initialize counter vector
	memset(cnt, 0, sizeof cnt);

	// for every face
	for(int i=0; i<(int)obj.faces().size(); i++) {
		// get a reference to it		
		const Face &face = obj.faces()[i];

		// for every vertex of that face
		for(int j=0; j<face.numVertices(); j++) {
			// update counter for that vertex
			cnt[face.vertexIndex(j)]++;
		}
	}

	double t=0;
	for(int i=0; i<(int)ver.size(); i++) {
		t += cnt[i];
	}
	
	averageDeg = t/ver.size();
}

void ShowDegree::drawRectangle() {
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
