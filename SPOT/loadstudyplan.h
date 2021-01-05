#pragma once
#include "Actions/Action.h"
#include "StudyPlan/StudyPlan.h"
#include "Registrar.h"
//Class responsible for adding course action
class loadstudyplan :public Action
{
public:
	loadstudyplan(Registrar*);
	bool Execute();
	virtual ~loadstudyplan();
	void load_studyplan(string filename);
};

