#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "ImportStudyPlan.h"
#include "Registrar.h"
#include <fstream>
#include<sstream>
#include<string>
#include <vector>
#include "Rules.h"
#include "StudyPlan\StudyPlan.h"
#include "StudyPlan\AcademicYear.h"
#include "ActionDeleteCourse.h"
#include "ActionAddNotes.h"
#include "ActionChangeCourseCode.h" 
#include <iostream>
#include "ActionReorderCourses.h"
#include "DisplayCourseInfo.h"
#include "ActionCalculateGPA.h"
Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	load(); //calling course catalog
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case LOAD:   //load study plan
		RequiredAction = new ImportStudyPlan(this);
		break;
	case DELETE_COURSE:
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case CHANGE_COURSE_CODE:
		RequiredAction = new ActionChangeCourseCode(this);
		break;
	case REORDER_COURSES:
		RequiredAction = new ActionReorderCourses(this);
		break;
	case DISPLAY_COURSE_INFO:
		RequiredAction = new DisplayCourseInfo(this);
		break;
	case CALCULATE_GPA:
		RequiredAction = new ActionCalculateGPA(this);
		break;
	//TODO: Add case for each action
	
	/*case EXIT:
		break;
		*/
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

bool Registrar::load() //function to import course catalog
{
	fstream file;
	file.open("FILES\\course_catalog.txt", ios::in);
	//ifstream coursecatalog("course catalog.txt");
	// if (file.fail()) { cout << "open file operation is failed" << endl; }
	CourseInfo Info;
	string tempcrd;
	string data;
	string tempcoreq;  // one course of corequisites
	string temppreq;   // one course of prerequisites
	string Coreq_part;
	string Prereq_part;
	if (file.fail()) {
		return false;
	}
	else
	{
		while (getline(file, data)) {   //to loop the data in lines of the txt file
			stringstream ss(data);
			getline(ss, Info.Code, ',');
			getline(ss, Info.Title, ',');
			getline(ss, tempcrd, ',');
			Info.Credits = stoi(tempcrd); // function to store an integer as a string
			getline(ss, Coreq_part, ':');   //to reed corequisites part
			if (Coreq_part == "Coreq")
			{
				string courses;
				getline(ss, courses, ',');
				while (true) {
					auto end = courses.find("And");
					string coursecode = courses.substr(0, end - 1);
					cout << coursecode << endl;
					Info.CoReqList.push_back(coursecode);
					courses = courses.substr(end + 4, courses.length());
					if (end == -1) {
						break;
					}
				}

			}
			if (Coreq_part == "Prereq")
			{
				string preq = ss.str();
				while (true) {
					auto end = preq.find("And");
					string coursecode = preq.substr(0, end - 1);
					Info.CoReqList.push_back(coursecode);
					preq = preq.substr(end + 4, preq.length());
					if (end == -1) {
						break;
					}
				}

			}
			else {
				string preqc;
				if (getline(ss, preqc, ':'))
				{
					while (true) {
						auto end = preqc.find("And");
						string coursecode = preqc.substr(0, end - 1);
						Info.CoReqList.push_back(coursecode);
						preqc = preqc.substr(end + 4, preqc.length());
						if (end == -1) {
							break;
						}
					}
				}
			}
			RegRules.CourseCatalog.push_back(Info);  // to shift course info into course catalog vector
		}
		return true;
	}
}

/*CourseInfo* Registrar::getcourseinfo(Course_Code code) {

	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			return &RegRules.CourseCatalog[i];
		}

	}
	for (int j = 0; j < RegRules.CourseCatalog.size(); j++) {
		if (RegRules.CourseCatalog[j].Code != code) {
			return nullptr;
			
		}
	}
}*/

CourseInfo* Registrar::getcourseinfo(Course_Code code) {
	int c = 0, num;
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			c += 1;
			num = i;
		}
		if (RegRules.CourseCatalog[i].Code != code) {
			c += 0;
		}
	}
	if (c > 0) {
		return &RegRules.CourseCatalog[num];
	}
	else if (c == 0){
		return nullptr;
	}
}

Registrar::~Registrar()
{
	delete pGUI;
}
