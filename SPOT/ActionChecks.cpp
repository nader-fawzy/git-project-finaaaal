#include "ActionChecks.h"
#include "../SPOT/Registrar.h"
#include "../SPOT/Actions/Action.h"
#include "Courses\UnivCourse.h"
#include <string>
#include <iostream>

ActionChecks::ActionChecks(Registrar* p) :Action(p){

}
bool ActionChecks::Execute() {
	return true;
}
void CheckPrereq(){
	GUI* pGUI = pReg->getGUI();
	string mess_check = pReg->getstudyplan()->checkCoursePreq(pReg->getRules());
	pGUI->PrintMsg(mess_check);
	pGUI->PrintMsg("   this is a prerequizete check mess...   ");
}
ActionChecks::~ActionChecks() {

}