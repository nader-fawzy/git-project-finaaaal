#include "ActionAddNotes.h"
#include "Actions\Action.h"
#include "Registrar.h"
#include <string>
#include <fstream>

ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute() {
	
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("write note you want to add");
	string notes = pGUI->GetSrting();      //take note from the user
	ofstream AddedNote;                    
	AddedNote.open("notefile.txt");
	if (!AddedNote)     //check if the file is opened or not (if it's found)
	{
		pGUI->PrintMsg("Error opening Note file");
		return false;
	}
	AddedNote << notes << endl;     //add note in the file
	AddedNote.close();                //close the file
	return true;
}
ActionAddNotes::~ActionAddNotes()
{ 
}