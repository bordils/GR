#ifndef _MODEL_INFO_2_H
#define _MODEL_INFO_2_H

#include "plugin.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class Model_info_2: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();
		void onObjectAdd();

	private:
		int nObjects;
		int nPolygons;
		int nTriangles;
		int nVerteces;

		QString nObjects_str;
		QString nPolygons_str;
		QString nTriangles_str;
		QString nVerteces_str;
		QString percentage_str;

		GLuint textureID;

		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;


		void updateModelInfo();
		void drawRectangle();
};

#endif
