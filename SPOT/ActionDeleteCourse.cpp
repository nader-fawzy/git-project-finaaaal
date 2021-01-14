#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses\Course.h"
#include "Actions\Action.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) : Action(p)
{
}
bool ActionDeleteCourse::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Press on the course you want to Delete");
	int x_point, y_point;
	if (actData.actType == DRAW_AREA) {   //get coord where user clicked
		x_point = actData.x;
		y_point = actData.y; 
		/*int yearWidth = 270, semWidth = 90;
		int x =( x_point / yearWidth)+1;
		int x_sem = (x_point / semWidth)+1;
		int c = (y_point - 150) / 50;*/
		StudyPlan* pS = pReg->getStudyPlay();
		int yearof_course = pS->setYearSem(x_point);
		SEMESTER SEMs= pS->Sem(x_point);
		/*int* point =*/ pS->DeleteCourse(x_point, y_point, yearof_course, SEMs);
		/*pS->DeleteCourse(x,x_sem,c);*/
	}
	return true;
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}
