#ifndef _INVERTER_H
#define _INVERTER_H

#include "plugin.h" 

class Inverter: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
    void preFrame();
    void postFrame();
    void onPluginLoad();

 private:
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
    int   mousex, mousey;
	int height;
};

#endif
