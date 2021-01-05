#include "ActionReorderCourses.h"
#include "Actions\Action.h"
#include "Registrar.h"
#include <string>

ActionReorderCourses::ActionReorderCourses(Registrar* p) :Action(p)
{
}
void ActionReorderCourses::swapFunction(double *PointerOnFirstCourse, double *PointerOnSecCourse) {
	double* tempPoint = NULL;
	tempPoint = PointerOnFirstCourse;
	PointerOnFirstCourse = PointerOnSecCourse;
	PointerOnSecCourse = tempPoint;
	
}
bool ActionReorderCourses::Execute() {
	GUI* pGUI = pReg->getGUI(); 
	pGUI->PrintMsg("Press on the course you want to re-order");
	ActionData actData = pGUI->GetUserAction();
	double x_point, y_point, xpoint, ypoint;
	double* PointerOnFirstCourse = NULL; 
	double* PointerOnSecCourse = NULL;
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		graphicsInfo gInfo{ x_point, y_point };
		StudyPlan* pS = pReg->getStudyPlay();
		PointerOnFirstCourse = pS->DetectCourse(x_point, y_point);
	}
	pGUI->PrintMsg("Press on the second course you want to re-order");
	actData = pGUI->GetUserAction();
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		xpoint = actData.x;
		ypoint = actData.y;
		graphicsInfo gInfo{ xpoint, ypoint };
		StudyPlan* pS = pReg->getStudyPlay();
		PointerOnSecCourse = pS->Detect_Course(xpoint, ypoint);
	}
	
	swapFunction(PointerOnFirstCourse,PointerOnSecCourse);
	return true;
}
ActionReorderCourses::~ActionReorderCourses()
{
}
