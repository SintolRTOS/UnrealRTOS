#ifndef _BEHAVORTREE_PATROL_H
#define _BEHAVORTREE_PATROL_H
#include "CBehaviorTreeNode.h"

enum MoveDirection
{
	NONEDIR,
	FOWARD,
	BACK,
	LEFT,
	RIGHT
};

class CBehaviorTreePatrol : public CBehaviorTreeNode
{
public:
	virtual ~CBehaviorTreePatrol();

	virtual void enterState(BehaviorTreeType _prestate);
	virtual void wait(float _waitime);
	virtual void leaveState();
	virtual void pauseState();
	virtual void translateTo(CBehaviorTree* _tree, BehaviorTreeType _nextstate, float translatetime = 0.0f);
	virtual void onEnterState();
	virtual void onLeaveState();
	virtual void update(float deteltime);
	virtual void doLogic();
	virtual void clear();
	virtual void setTargetCharactor(ACharacter* _value);
	static CBehaviorTreePatrol* createInstance(ACharacter* _charactor, BehaviorTreeType _state);
private:
	CBehaviorTreePatrol(ACharacter* _charactor, BehaviorTreeType _state);
	void checkRoad();
	void runRoad();
	float _checkinvervaltime;
	MoveDirection _checkmovedir;
};
#endif // !_BEHAVORTREE_PATROL_H
