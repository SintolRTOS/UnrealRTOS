#ifndef _BEHAVIORTREE_NODE_H
#define _BEHAVIORTREE_NODE_H
#include "GameFramework/Character.h"

enum BehaviorTreeType
{
	NONE,
	IDLE,
	MOVE,
	CHECKTASK,
	FOLLOW,
};

enum BehaviorNodeState
{
	READY,
	DOING,
	PAUSE,
	STOP,
	WAIT,
	TRANSLATE,
};

class CBehaviorTree;

class CBehaviorTreeNode
{
public:
	CBehaviorTreeNode(ACharacter* _charactor, BehaviorTreeType _state);
	virtual ~CBehaviorTreeNode();

	virtual void enterState(BehaviorTreeType _prestate);
	virtual void wait(float _waitime);
	virtual void leaveState();
	virtual void pauseState();
	virtual void translateTo(CBehaviorTree* _tree,BehaviorTreeType _nextstate, float translatetime = 0.0f);
	virtual void onEnterState();
	virtual void onLeaveState();
	virtual void update(float deteltime);
	virtual void doLogic();
	virtual void clear();
	virtual void setTargetCharactor(ACharacter* _value);
	BehaviorNodeState getRunState();
	ACharacter* getTargetCharactor();
protected:
	bool _isstarted;
	ACharacter* _aiController;
	ACharacter* _target;
	BehaviorTreeType _nodestate;
	BehaviorTreeType _nextstate;
	BehaviorNodeState _runstate;
	float _timedetal;
	float _invervaltime;
	float _waittime;
};

#endif // !_BEHAVIORTREE_NODE_H

