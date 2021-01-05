#pragma once
#include "Registrar.h"
#include <fstream>
#include<sstream>
#include<string>
#include <vector>
#include "Rules.h"
#include "Actions/ActionAddCourse.h"
#include "StudyPlan\StudyPlan.h"
#include "StudyPlan\AcademicYear.h"
#include "ActionDeleteCourse.h"
#include "ActionAddNotes.h"
#include "ActionReorderCourses.h"
#include "DisplayCourseInfo.h"
#include "ActionChangeCourseCode.h"
#include "ActionCalculateGPA.h"
#include "../SPOT/loadstudyplan.h"
#include <iostream>
using namespace std;


Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
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
	case DEL_CRS: //delete course action
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case REDO: //reorder courses action
		RequiredAction = new ActionReorderCourses(this);
		break;
	case NOTE: //add notes action
		RequiredAction = new ActionAddNotes(this);
		break;
	case CHANGE_COURSE_CODE: //change course code action
		RequiredAction = new ActionChangeCourseCode(this);
		break;
	case DISPLAY_COURSE_INFO: //display course info action
		RequiredAction = new DisplayCourseInfo(this);
		break;
	case CALC_GPA:
		RequiredAction = new ActionCalculateGPA(this);
		break;
	/*case LOAD: //load study plan action
		RequiredAction = new loadstudyplan(this);
		break;*/
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

/*void Registrar::loadstudyplan(string filename) {
	pSPlan->studyplan(filename, (this));
}*/
void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

Registrar::~Registrar()
{
	delete pGUI;
}
void Registrar::load() //function to import course catalog
{
	fstream file;
	file.open("course catalog");
	ifstream coursecatalog("files\\course catalog.txt");
	//ifstream coursecatalog("course catalog.txt");
	// if (file.fail()) { cout << "open file operation is failed" << endl; }
	CourseInfo Info;
	string tempcrd;
	string data;
	string tempcoreq;  // one course of corequisites
	string temppreq;   // one course of prerequisites
	string Coreq_part;
	string Prereq_part;
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
}
void Registrar::ProgramRequirements() //function to import 
{
	fstream file;
	file.open("Rules");
	ifstream ProgramRequirements("files\\program_requirments.txt");
	//ifstream coursecatalog("course catalog.txt");
	// if (file.fail()) { cout << "open file operation is failed" << endl; }
	Rules Rule;
	string data;
	string tempTotalCr;
	string tempUniversity_CompulsoryCr;
	string tempUniversity_ElectiveCr;
	string tempTrack_CompulsoryCr;
	string tempTrack_Compulsory;
	string tempMajor_Commom_CompulsoryCr;
	string tempMajor_Commom_ElectiveCr;
	string tempMajor_Common_Compulsory;
	string tempMajor_Common_Elective;
	string tempMajor_Concentration1_Conmulsory;
	string tempMajor_Concentration1_Elective;
	string tempMajor_Concentration2_Conmulsory;
	string tempMajor_Concentration2_Elective;
	string tempMajor_Concentration3_Conmulsory;
	string tempMajor_Concentration3_Elective;
	string tempMajor_Concentration4_Conmulsory;
	string tempMajor_Concentration4_Elective;

	string tempNumber_Of_Concentrations;
	string tempMajor_Concentration_Compulsorycr;
	string tempMajor_Concentration_Electivecr;
	string tempUniversity_Compulsory;
	string tempUniversity_Elective;
	//string tempTrack_Compulsory;
	string tempMajor_Concentration_CompulsoryCr;
	string tempMajor_Concentration_ElectiveCr;
	getline(file, tempTotalCr);
	Rule.TotalCr = stoi(tempTotalCr);

	getline(file, tempUniversity_CompulsoryCr);
	stringstream ss(tempUniversity_CompulsoryCr);
	getline(ss, tempUniversity_CompulsoryCr, ',');
	getline(ss, tempUniversity_ElectiveCr, ',');

	getline(file, tempTrack_CompulsoryCr);

	Rule.Track_CompulsoryCr = stoi(tempTrack_CompulsoryCr);




	getline(file, tempMajor_Commom_CompulsoryCr);
	stringstream sss(tempMajor_Commom_CompulsoryCr);
	getline(sss, tempMajor_Commom_CompulsoryCr, ',');
	getline(sss, tempMajor_Commom_ElectiveCr, ',');



	getline(file, tempNumber_Of_Concentrations);
	Rule.Number_Of_Concentrations = stoi(tempNumber_Of_Concentrations);

	int n = stoi(tempNumber_Of_Concentrations);

	for (int i = 0; i < n; i++)
	{
		getline(ss, tempMajor_Concentration_CompulsoryCr, ',');

		//Rule.Major_Concentration_CompulsoryCr.push_back(tempMajor_Concentration_CompulsoryCr);
		//Rule.Major_Concentration_ElectiveCr.push_back(tempMajor_Concentration_ElectiveCr);


	}

	//while ((getline(file, data)))

		/*/stringstream ss(data);
		getline(ss, Rule.UnivCompulsory, ',');
		Major_Concentration_ElectiveCr.Rule..push_back(tempMajor_Concentration_ElectiveCr);
		/*/
	getline(sss, tempUniversity_Compulsory, ',');
	Rule.UnivCompulsory.push_back(tempUniversity_Compulsory);


	getline(sss, tempUniversity_Elective, ',');
	Rule.UnivElective.push_back(tempUniversity_Elective);


	getline(sss, tempTrack_Compulsory, ',');
	Rule.UnivElective.push_back(tempTrack_Compulsory);


	getline(sss, tempMajor_Common_Compulsory, ',');
	Rule.UnivElective.push_back(tempMajor_Common_Compulsory);


	getline(sss, tempMajor_Common_Elective, ',');
	Rule.UnivElective.push_back(tempMajor_Common_Elective);

	getline(sss, tempMajor_Concentration1_Conmulsory, ',');
	Rule.UnivElective.push_back(tempMajor_Concentration1_Conmulsory);

	getline(sss, tempMajor_Concentration2_Conmulsory, ',');
	Rule.UnivElective.push_back(tempMajor_Concentration2_Conmulsory);

	getline(sss, tempMajor_Concentration3_Conmulsory, ',');
	Rule.UnivElective.push_back(tempMajor_Concentration3_Conmulsory);

	getline(sss, tempMajor_Concentration4_Conmulsory, ',');
	Rule.UnivElective.push_back(tempMajor_Concentration4_Conmulsory);



}
//this function checks if the course is found in course catalog or not
//it takes the input course code from the user and then it compare it with other code courses catalog
CourseInfo* Registrar::getcourseinfo(Course_Code code) {
	
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			return &RegRules.CourseCatalog[i];
		}
		else {
			return nullptr;
		}
	}
	
}

StudyPlan* Registrar::getStudyplan(Course_Code code, StudyPlan &s) {
	getcourseinfo(code);   //check if course is found in course catalog
	
	/*for (int num = 0; num < pSPlan.listofcoursecodes[num].size(); num++) {

	}*/
}
/*CourseInfo* Registrar::checkcourseinfo(Course_Code code) {                  //not needed 
	for (int n = 0; n < RegRules.CourseCatalog.size(); n++) {
		if (RegRules.CourseCatalog[n].Code == code) {
			GUI* pGUI = getGUI();
			pGUI->PrintMsg("enter the new course code");
			Course_Code NewCode = pGUI->GetSrting();
			RegRules.CourseCatalog[n].Code = NewCode;
			return &RegRules.CourseCatalog[n];
		}
		else {
			return nullptr;
		}
	}
	return nullptr;
}*/

/*void Registrar::LoadPlan(ifstream &finput) {
	CourseInfo *cinfo = getcourseinfo(code);
	Course* pc = new Course(code, cinfo.Title, cinfo.Credits);
}*/