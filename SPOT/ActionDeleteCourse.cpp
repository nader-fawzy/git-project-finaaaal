#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses\Course.h"
#include "Actions\Action.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :Action(p)
{
}
bool ActionDeleteCourse::Execute() {
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Press on the course you want to Delete");
	ActionData actData = pGUI->GetUserAction();
	double x_point, y_point;
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		graphicsInfo gInfo{ x_point, y_point };
		StudyPlan* pS = pReg->getStudyPlay();
		double* point = pS->DeleteCourse(x_point, y_point);
	}
	return true;
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}
