#ifndef _BEHAVIORTREE_IDLE_H
#define _BEHAVIORTREE_IDLE_H
#include "CBehaviorTreeNode.h"

class CBehaviorTreeIdle :public CBehaviorTreeNode
{
public:
	virtual ~CBehaviorTreeIdle();

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
	static CBehaviorTreeIdle* createInstance(ACharacter* _charactor, BehaviorTreeType _state);
private:
	CBehaviorTreeIdle(ACharacter* _charactor, BehaviorTreeType _state);
	void checkCharactor();
	void thinkTranslate();
	float _thinktimedetal;
};

#endif // !_BEHAVIORTREE_IDLE_H

