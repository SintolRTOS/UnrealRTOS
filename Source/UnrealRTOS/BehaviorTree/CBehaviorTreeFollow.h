#ifndef _BEHAVIORTREE_FOLLOW_H
#define _BEHAVIORTREE_FOLLOW_H
#include "CBehaviorTreeNode.h"
class CBehaviorTreeFollow : public CBehaviorTreeNode
{
public:
	virtual ~CBehaviorTreeFollow();

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
	static CBehaviorTreeFollow* createInstance(ACharacter* _charactor, BehaviorTreeType _state,ACharacter* _targetcharactor);
private:
	CBehaviorTreeFollow(ACharacter* _charactor, BehaviorTreeType _state, ACharacter* _targetvalue);
	bool checkMaxFollowDistance();
};
#endif
