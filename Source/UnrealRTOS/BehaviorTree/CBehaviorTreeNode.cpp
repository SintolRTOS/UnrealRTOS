#include "CBehaviorTreeNode.h"

CBehaviorTreeNode::CBehaviorTreeNode(ACharacter* _charactor, BehaviorTreeType _state):
	_aiController(_charactor),
	_nodestate(_state),
	_isstarted(false),
	_invervaltime(0)
{

}

CBehaviorTreeNode::~CBehaviorTreeNode()
{

}

void CBehaviorTreeNode::enterState(BehaviorTreeType _prestate)
{
	if (_isstarted)
		return;
	_isstarted = true;
}

void CBehaviorTreeNode::wait(float _waitime)
{
	_invervaltime += _waitime;
}

void CBehaviorTreeNode::leaveState()
{

}

void CBehaviorTreeNode::pauseState()
{

}

void CBehaviorTreeNode::translateTo(BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{

}

void CBehaviorTreeNode::onEnterState()
{

}

void CBehaviorTreeNode::onLeaveState()
{

}

void CBehaviorTreeNode::update(float deteltime)
{
	if (_isstarted)
	{
		_invervaltime += deteltime;
	}
}

void CBehaviorTreeNode::doLogic()
{

}

void CBehaviorTreeNode::clear()
{
	_isstarted = false;
	_invervaltime = 0;
}
