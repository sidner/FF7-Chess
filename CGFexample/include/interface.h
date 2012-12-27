#ifndef interface_H
#define interface_H


#include "CGF/CGFinterface.h"
#include "CGF/CGFscene.h"
#include "CGF/CGFapplication.h"
#include "DemoScene.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include "House.h"

class interface : public CGFscene, public CGFinterface {
public:
    interface();
    virtual void processMouse(int button, int state, int x, int y);
    void performPicking(int x, int y);
    void processHits(GLint hits, GLuint buffer[]);
    virtual void initGUI();
    //	virtual void processGUI(GLUI_Control *ctrl);

    //	virtual void processKeyboard(unsigned char key, int x, int y);

    int testVar;

private:
    bool modelPicked;
    House* picked;
};




#endif 
