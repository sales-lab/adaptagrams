/*
 * Bridge for C programs to access solve_VPSC (which is in C++)
 */
#include <iostream>
#include <variable.h>
#include <constraint.h>
#include <generate-constraints.h>
#include <solve_VPSC.h>
#include "csolve_VPSC.h"
extern "C" {
Variable* newVariable(int id, double desiredPos, double weight) {
	return new Variable(id,desiredPos,weight);
}
Constraint* newConstraint(Variable* left, Variable* right, double gap) {
	return new Constraint(left,right,gap);
}
VPSC* newVPSC(int n, Variable* vs[], int m, Constraint* cs[]) {
	return new VPSC(n,vs,m,cs);
}
IncVPSC* newIncVPSC(int n, Variable* vs[], int m, Constraint* cs[]) {
	return new IncVPSC(n,vs,m,cs);
}

int genXConstraints(int n, double minX[], double maxX[], double minY[], double maxY[], Variable** vs, Constraint*** cs) {
	Rectangle* rs[n];
	for(int i=0;i<n;i++) {
		rs[i]=new Rectangle(minX[i],maxX[i],minY[i],maxY[i]);
	}
	int m = generateXConstraints(n,rs,vs,*cs,true);
	for(int i=0;i<n;i++) {
		delete rs[i];
	}
	return m;
}
int genYConstraints(int n, double minX[], double maxX[], double minY[], double maxY[], Variable** vs, Constraint*** cs) {
	Rectangle* rs[n];
	for(int i=0;i<n;i++) {
		rs[i]=new Rectangle(minX[i],maxX[i],minY[i],maxY[i]);
	}
	int m = generateYConstraints(n,rs,vs,*cs);
	for(int i=0;i<n;i++) {
		delete rs[i];
	}
	return m;
}

void deleteConstraint(Constraint* c) {
	delete c;
}
void deleteVariable(Variable* v) {
	delete v;
}
void satisfyVPSC(VPSC* vpsc) {
	vpsc->satisfy();
}
void deleteVPSC(VPSC *vpsc) {
	assert(vpsc!=NULL);
	delete vpsc;
}
void solveVPSC(VPSC* vpsc) {
	vpsc->solve();
}
void splitIncVPSC(IncVPSC* vpsc) {
	vpsc->splitBlocks();
}
void setVariableDesiredPos(Variable *v, double desiredPos) {
	v->desiredPosition = desiredPos;
}
double getVariablePos(Variable *v) {
	return v->position();
}
}
