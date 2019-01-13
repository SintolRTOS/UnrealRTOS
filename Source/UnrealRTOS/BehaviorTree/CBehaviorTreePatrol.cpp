#include "CBehaviorTreePatrol.h"

CBehaviorTreePatrol::~CBehaviorTreePatrol()
{
	CBehaviorTreeNode::~CBehaviorTreeNode();
}

void CBehaviorTreePatrol::enterState(BehaviorTreeType _prestate)
{
	CBehaviorTreeNode::enterState(_prestate);
}

void CBehaviorTreePatrol::wait(float _waitime)
{
	CBehaviorTreeNode::wait(_waitime);
}

void CBehaviorTreePatrol::leaveState()
{
	CBehaviorTreeNode::leaveState();
}

void CBehaviorTreePatrol::pauseState()
{
	CBehaviorTreeNode::pauseState();
}

void CBehaviorTreePatrol::translateTo(BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{
	CBehaviorTreeNode::translateTo(_nextstate, translatetime);
}

void CBehaviorTreePatrol::onEnterState()
{
	CBehaviorTreeNode::onEnterState();
}

void CBehaviorTreePatrol::onLeaveState()
{
	CBehaviorTreeNode::onLeaveState();
}

void CBehaviorTreePatrol::update(float deteltime)
{
	CBehaviorTreeNode::update(deteltime);
}

void CBehaviorTreePatrol::doLogic()
{
	CBehaviorTreeNode::doLogic();
}

void CBehaviorTreePatrol::clear()
{
	CBehaviorTreeNode::clear();
}

void CBehaviorTreePatrol::setTargetCharactor(ACharacter* _value)
{
	CBehaviorTreeNode::setTargetCharactor(_value);
}

CBehaviorTreePatrol* CBehaviorTreePatrol::createInstance(ACharacter* _charactor, BehaviorTreeType _state)
{
	return new CBehaviorTreePatrol(_charactor, _state);
}

CBehaviorTreePatrol::CBehaviorTreePatrol(ACharacter* _charactor, BehaviorTreeType _state):
	CBehaviorTreeNode(_charactor,_state)
{

}
