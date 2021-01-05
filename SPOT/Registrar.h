#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan* pSPlan;
	
public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay()const;
	void load();
	void ProgramRequirements();
	//void loadstudyplan(string filename);
	StudyPlan* getStudyplan(Course_Code code, StudyPlan& s);
	void Run();

	~Registrar();
	//function to check if the course if found in course catalog or not
	CourseInfo* getcourseinfo(Course_Code code);      //check if the course is in the course catalog or not
	//CourseInfo* checkcourseinfo(Course_Code code);    //change course code by asking about the old and the new one(not required)
	//void LoadPlan(ifstream& finput);
	
};

