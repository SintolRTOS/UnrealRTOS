#include "CBehaviorTreeFollow.h"
#include "CBehaviorTree.h"

CBehaviorTreeFollow::~CBehaviorTreeFollow()
{
	CBehaviorTreeNode::~CBehaviorTreeNode();
}

void CBehaviorTreeFollow::enterState(BehaviorTreeType _prestate)
{
	CBehaviorTreeNode::enterState(_prestate);
}

void CBehaviorTreeFollow::wait(float _waitime)
{
	CBehaviorTreeNode::wait(_waitime);
}

void CBehaviorTreeFollow::leaveState()
{
	CBehaviorTreeNode::onLeaveState();
}

void CBehaviorTreeFollow::pauseState()
{
	CBehaviorTreeNode::pauseState();
}

void CBehaviorTreeFollow::translateTo(CBehaviorTree* _tree, BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{
	CBehaviorTreeNode::translateTo(_tree,_nextstate, translatetime);
}

void CBehaviorTreeFollow::onEnterState()
{
	CBehaviorTreeNode::onEnterState();
}

void CBehaviorTreeFollow::onLeaveState()
{
	CBehaviorTreeNode::onLeaveState();
}

void CBehaviorTreeFollow::update(float deteltime)
{
	CBehaviorTreeNode::update(deteltime);
}

void CBehaviorTreeFollow::doLogic()
{
	CBehaviorTreeNode::doLogic();
}

void CBehaviorTreeFollow::clear()
{
	CBehaviorTreeNode::clear();
}

void CBehaviorTreeFollow::setTargetCharactor(ACharacter* _value)
{
	CBehaviorTreeNode::setTargetCharactor(_value);
}

CBehaviorTreeFollow* CBehaviorTreeFollow::createInstance(ACharacter* _charactor, BehaviorTreeType _state, ACharacter* _targetcharactor)
{
	return new CBehaviorTreeFollow(_charactor, _state, _targetcharactor);
}

CBehaviorTreeFollow::CBehaviorTreeFollow(ACharacter* _charactor, BehaviorTreeType _state, ACharacter* _targetvalue):
	CBehaviorTreeNode(_charactor,_state)
{
	CBehaviorTreeNode::setTargetCharactor(_targetvalue);
}
