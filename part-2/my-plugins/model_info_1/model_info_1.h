#ifndef _MODEL_INFO_1_H
#define _MODEL_INFO_1_H

#include "plugin.h" 

class Model_info_1: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
	 	void onObjectAdd();
  	
	private:
		void printModelInfo();
};

#endif
