#pragma once
#include "Registrar.h"
#include "Actions\Action.h"
#include "Actions\ActionAddCourse.h"
class ActionChecks : public Action
{
public:
	ActionChecks(Registrar*);
	bool virtual Execute();
	void CheckPrereq() ;
	void CheckCorreq() ;
	void CheckTotalCreditsPerSem() ;
	~ActionChecks();
};

