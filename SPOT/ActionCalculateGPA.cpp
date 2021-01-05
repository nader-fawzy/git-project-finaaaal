#include "ActionCalculateGPA.h"
#include "../SPOT/Registrar.h"
#include "../SPOT/Courses/UnivCourse.h"
#include "../SPOT/Actions/Action.h"
#include <iostream>
#include <string>
#include <sstream>
ActionCalculateGPA::ActionCalculateGPA(Registrar* p) :Action(p) {

}
bool ActionCalculateGPA::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Enter number of courses to calculate the GPA: ");
	//TODO: add input validation
	/*int x_plan, y_plan;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x_plan = actData.x;
		y_plan = actData.y;
		graphicsInfo gInfo{ x_plan, y_plan };
	}*/
	string get_num_of_courses = pGUI->GetSrting();
	int num_of_courses;
	istringstream(get_num_of_courses) >> num_of_courses;  //string -> int and put it in num_of_courses 
	CourseInfo* Course_data_credits; //to get credits of the course entered by the user
	Course_Code course_code_entered;
	int credits_of_course;
	double result, Final_GPA, totalResult=0;
	
	for (int num = 0; num < num_of_courses; num++) {
		pGUI->PrintMsg("Enter the course name: ");
		course_code_entered = pGUI->GetSrting(); //get course code name
		Course_data_credits = pReg->getcourseinfo(course_code_entered); //check if the course is in the course catalog and return its data
		//credits_of_course = Course_data_credits->Credits;
		pGUI->PrintMsg("Enter the course grade: ");
		string grades = pGUI->GetSrting();
		if (grades == "A") {
			result = 4;
		}
		else if (grades == "A-") {
			result = 3.7;
		}
		else if (grades == "B+") {
			result = 3.3;
		}
		else if (grades == "B") {
			result = 3;
		}
		else if (grades == "B-") {
			result = 2.7;
		}
		else if (grades == "C+") {
			result = 2.3;
		}
		else if (grades == "C") {
			result = 2;
		}
		else if (grades == "C-") {
			result = 1.7;
		}
		else if (grades == "D+") {
			result = 1.3;
		}
		else if (grades == "D") {
			result = 1;
		}
		else if (grades == "D-") {
			result = 0.7;
		}
		else if (grades == "F") {
			result = 0;
		}
		else {
			pGUI->PrintMsg("invalid input");
		}
		totalResult += result;
	}
	pGUI->PrintMsg("Final GPA is: ");
	
	Final_GPA = totalResult / num_of_courses;
	string Calculated_GPA= to_string(Final_GPA);
	pGUI->PrintMsg(Calculated_GPA);
	return true;
}
ActionCalculateGPA::~ActionCalculateGPA() {

}
