#include "CBehaviorTreeNode.h"
#include "CBehaviorTree.h"

CBehaviorTreeNode::CBehaviorTreeNode(ACharacter* _charactor, BehaviorTreeType _state):
	_aiController(_charactor),
	_nodestate(_state),
	_isstarted(false),
	_invervaltime(0),
	_waittime(0),
	_timedetal(0),
	_runstate(READY)
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
	_waitime = _invervaltime;
	_runstate = WAIT;
}

void CBehaviorTreeNode::leaveState()
{
	_runstate = STOP;
}

void CBehaviorTreeNode::pauseState()
{
	_runstate = PAUSE;
}

void CBehaviorTreeNode::translateTo(CBehaviorTree* _tree, BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{
	if (NULL != _tree)
	{
		_tree->translateTo(_nextstate, translatetime);
	}
}

void CBehaviorTreeNode::onEnterState()
{
	_isstarted = true;
	_timedetal = 0;
	_runstate = DOING;
}

void CBehaviorTreeNode::onLeaveState()
{
	_isstarted = false;
	_invervaltime = 0;
	_runstate = STOP;
	_waittime = 0;
	_timedetal = 0;
}

void CBehaviorTreeNode::update(float deteltime)
{
	if (!_isstarted)
		return;
	_invervaltime += deteltime;
	_timedetal = deteltime;
	if (_runstate == READY)
	{
		return;
	}
	else if (_runstate == DOING)
	{
		doLogic();
	}
	else if (_runstate == PAUSE)
	{
		return;
	}
	else if (_runstate == STOP)
	{
		return;
	}
	else if (_runstate == WAIT)
	{
		if (_waittime <= _invervaltime)
		{
			_runstate = DOING;
		}
	}
}

void CBehaviorTreeNode::doLogic()
{
	
}

void CBehaviorTreeNode::clear()
{
	_isstarted = false;
	_invervaltime = 0;
	_waittime = 0;
	_runstate = READY;
}

void CBehaviorTreeNode::setTargetCharactor(ACharacter* _value)
{
	_target = _value;
}
