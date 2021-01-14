#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "../GUI/GUI.h"
#include <iostream>
ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();	
	
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	
	CourseInfo* cinfo;   //pointer to title,code,prereq,...
	cinfo = pReg->getcourseinfo(code);   //check if course is found in course catalog

	if (cinfo ==NULL) {
		pGUI->PrintMsg("course is not found..press enter to contiue");
		Course_Code code = pGUI->GetSrting();
	}
	else{
		ActionData actData = pGUI->GetUserAction("Select a year to add coures to: ");
		
		int x, y;
		if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
		{
			//get coord where user clicked
			x = actData.x;
			y = actData.y;



			graphicsInfo gInfo{ x, y };
			
			/*int YearW = 270, SemW = 90;
			int x_detectYear = (x / YearW) + 1;
			int X_DetectSem = (x / SemW) ;
			SEMESTER SEMyear;*/

			/*switch (X_DetectSem) {
			case 0: SEMyear = FALL;
				break;
			case 1: SEMyear = SPRING;
				break;
			case 2: SEMyear = SUMMER;
			}*/
			
			string Title = "Test101";
			int crd = cinfo->Credits;
			//int crd = 0;
			Course* pC = new Course(code, Title, crd);
			pC->setGfxInfo(gInfo);

			
			//sem syearsem; // struct include the year and the semesters
			StudyPlan* pS = pReg->getStudyPlay();
			int yearof_course =pS->setYearSem(x);
			SEMESTER SEM = pS->Sem(x);
			//pS->AddCourse(pC, syearsem.year, syearsem.s);
			pS->AddCourse(pC, yearof_course, SEM);
		}
		//TODO:


		return true;

	}
		
	
	
}


ActionAddCourse::~ActionAddCourse()
{
}
