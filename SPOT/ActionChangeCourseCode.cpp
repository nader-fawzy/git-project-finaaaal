#include "ActionChangeCourseCode.h"
#include "Registrar.h"
ActionChangeCourseCode::ActionChangeCourseCode(Registrar* p) :Action(p)
{
}

bool ActionChangeCourseCode::Execute(){
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("press on the course you want to change");
	ActionData actData = pGUI->GetUserAction(); //it takes the position of the clicked area to the actdata.
	double x_point, y_point;  //variables to carry the XY points
	if (actData.actType == DRAW_AREA) {  //get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		graphicsInfo gInfo{ x_point, y_point };      
		StudyPlan* pS = pReg->getStudyPlay();   //this function returns a pointer on study plan
		double* point = pS->DeleteCourse(x_point, y_point);
		pGUI->PrintMsg("Enter the new course Code(e.g. CIE202)");
		Course_Code code = pGUI->GetSrting();   // add input validation
		CourseInfo* cinfo;
		cinfo = pReg->getcourseinfo(code);
		ActionData actData = pGUI->GetUserAction("click on year you want to add the new course to");
		int x, y;
		if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
		{
			//get coord where user clicked
			x = actData.x;
			y = actData.y;
			graphicsInfo gInfo{ x, y };
			string Title = cinfo->Title;
			int crd = cinfo->Credits;
			Course* pC = new Course(code, Title, crd);
			pC->setGfxInfo(gInfo);
			StudyPlan* pS = pReg->getStudyPlay();
			pS->AddCourse(pC, 1, FALL);
		}
	}
    return true;
}

ActionChangeCourseCode::~ActionChangeCourseCode()
{
}
