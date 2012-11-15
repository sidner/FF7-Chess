#include "interface.h"
#include "DemoScene.h"
#include <iostream>
#include <cstring>
interface::interface(){
	testVar=0;
}


void interface::initGUI()
{
int x=0;

	 char l[6];
	 char c[9];
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Luzes", 1);
	addColumn();
	GLUI_Panel *varPanel2 = addPanel("Cameras", 1);
	
	GLUI_Listbox *list = addListboxToPanel(varPanel2,"Cameras", &(((DemoScene*) scene)->nr_cams), 1);
	
	
	for(unsigned int i=0;i< ((DemoScene*) scene)->number; i++){
	sprintf(c,"Camera: %d",i);
	list->add_item(i, c);

}


	for(int i=0; i<((DemoScene *) scene)->nr;i++){


		sprintf(l,"luz: %d",i);
	// You could also pass a reference to a variable from the scene class, if public


	addCheckboxToPanel(varPanel, l,&(((DemoScene *) scene)->lz[x]) , 1);
	x++;
	if(x%2==0)
		addColumnToPanel(varPanel);
	}
	/*addColumnToPanel(varPanel);
	addCheckboxToPanel(varPanel, "Luz 2", &(((DemoScene*) scene)->luzVar1), 2);
	addColumnToPanel(varPanel);
	addCheckboxToPanel(varPanel, "Luz 3", &(((DemoScene*) scene)->luzVar2), 3);
	addColumnToPanel(varPanel);
	addCheckboxToPanel(varPanel, "Luz 4", &(((DemoScene*) scene)->luzVar3), 4);

	addButtonToPanel(varPanel2,"Start/Stop Clock",5);
	addColumnToPanel(varPanel2);
	GLUI_RadioGroup *wired = addRadioGroupToPanel(varPanel2,&(((DemoScene*) scene)->wire),1);
	addRadioButtonToGroup(wired, "Wireframe");
	addRadioButtonToGroup(wired, "Textured");
	addColumnToPanel(varPanel2);
	GLUI_Listbox *list = addListboxToPanel(varPanel2,"robot2", &(((DemoScene*) scene)->texture), 1);
	list->add_item(1, "default");
	list->add_item(2, "circuits");
	list->add_item(3, "squares");*/
	
}
