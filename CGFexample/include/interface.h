#ifndef interface_H
#define interface_H


#include "CGF/CGFinterface.h"
#include "CGF/CGFscene.h"

class interface: public CGFscene, public CGFinterface {
	public:
		interface();

		virtual void initGUI();
	//	virtual void processGUI(GLUI_Control *ctrl);

	//	virtual void processKeyboard(unsigned char key, int x, int y);

		int testVar;
};




#endif 
