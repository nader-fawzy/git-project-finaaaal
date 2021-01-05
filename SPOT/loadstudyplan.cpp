#include "loadstudyplan.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include "GUI/GUI.h"
#include "StudyPlan/StudyPlan.h"
#include <iostream>

loadstudyplan::loadstudyplan(Registrar* p) :Action(p)
{
}
bool loadstudyplan::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add file path :");
	string filename = pGUI->GetSrting();
	//pReg->loadstudyplan(filename);

	return true;
}



loadstudyplan::~loadstudyplan()
{
}
