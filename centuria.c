#include "main.h"
#include "tgmath.h"

void cMove();
void cTranslate();
void cSetPosition();
void cPoint();
void cTurn();
void cSetAngle();

struct movexy getmovement();

struct movexy{
	double x, y;
};

//moves unit forward
void cMove(struct centuria * p){
	struct movexy xy = getmovement((p->angle + 180) * -1);
	p->x += xy.x * unitspeed;
	p->y += xy.y * unitspeed;
}

//moves units regardless of its angle
void cTranslate(struct centuria * p, int x, int y){
	p->x += x * unitspeed;
	p->y += y * unitspeed;
}

//moves unit to a position
void cSetPosition(struct centuria * p, int x, int y){
	p->x = x;
	p->y = y;
}
//points unit towards another unit
void cPoint(struct centuria * p, struct centuria * t){
	int x = p->x - t->x;
	int y = p->y - t->y;	
	double angle = atan2(x, y) * 180 / PI;
	p->angle = angle * -1;
}

//turns object x degrees
void cTurn(struct centuria * p, double angle){
	p->angle += angle;
}
//set unit angle
void cSetAngle(struct centuria * p, double angle){
	p->angle = angle;
}

struct movexy getmovement(double angle){
	struct movexy xy;
	xy.x = sin(PI/180*angle);
	xy.y = cos(PI/180*angle);
	
	return xy;
}
