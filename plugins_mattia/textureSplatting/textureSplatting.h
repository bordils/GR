#ifndef _TEXTURESPLATTING_H
#define _TEXTURESPLATTING_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class TextureSplatting: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void preFrame();
		void postFrame();
	
	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;

		GLuint noiseID;
		GLuint textureID_0;
		GLuint textureID_1;
};

#endif
