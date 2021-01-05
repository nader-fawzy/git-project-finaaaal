#include "DisplayCourseInfo.h"
#include "Registrar.h"
#include "Courses\Course.h"
DisplayCourseInfo::DisplayCourseInfo(Registrar* p) :Action(p)
{
}
bool DisplayCourseInfo::Execute() {
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("press on course you want to display it's information");
	ActionData actData = pGUI->GetUserAction();
	double x_point, y_point;
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		graphicsInfo gInfo{ x_point, y_point };
		StudyPlan* pS = pReg->getStudyPlay();
		double* PointerOnFirstCourse = pS->DetectCourse(x_point, y_point);  //detect position of the course selected
		//? m4 3rfa ageb esm el course
		//CourseInfo* CourseInformation;
		//Course_Code COURSEcode;
		//CourseInformation = pReg->getcourseinfo(COURSEcode);
		//CourseInfo* COURSEdetected = pReg->checkcourseinfo(code); 
		
	}
	return true;
}
DisplayCourseInfo::~DisplayCourseInfo() {

}