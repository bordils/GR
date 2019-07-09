#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>

class Reflection: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		bool paintGL();

	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;

		GLuint textureID;

		void drawRectangle();
};

#endif
