#include "CBehaviorTreeIdle.h"
#include "CBehaviorTree.h"
#include "../EntityManager.h"

CBehaviorTreeIdle::~CBehaviorTreeIdle()
{
	CBehaviorTreeNode::~CBehaviorTreeNode();
}

void CBehaviorTreeIdle::enterState(BehaviorTreeType _prestate)
{
	CBehaviorTreeNode::enterState(_prestate);
}

void CBehaviorTreeIdle::wait(float _waitime)
{
	CBehaviorTreeNode::wait(_waitime);
}

void CBehaviorTreeIdle::leaveState()
{
	CBehaviorTreeNode::leaveState();
}

void CBehaviorTreeIdle::pauseState()
{
	CBehaviorTreeNode::pauseState();
}

void CBehaviorTreeIdle::translateTo(CBehaviorTree* _tree, BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{
	CBehaviorTreeNode::translateTo(_tree,_nextstate, translatetime);
}

void CBehaviorTreeIdle::onEnterState()
{
	CBehaviorTreeNode::onEnterState();
}

void CBehaviorTreeIdle::onLeaveState()
{
	CBehaviorTreeNode::onLeaveState();
}

void CBehaviorTreeIdle::update(float deteltime)
{
	CBehaviorTreeNode::update(deteltime);
}

void CBehaviorTreeIdle::doLogic()
{
	CBehaviorTreeNode::doLogic();
	std::map<rti1516::ObjectInstanceHandle, AActor*> entityActorMap = SintolRTI::EntityManager::GetInstance()->GetEnitiyActorMap();
	for (std::map<rti1516::ObjectInstanceHandle, AActor*>::const_iterator it = entityActorMap.begin();
		it != entityActorMap.end(); it++)
	{
		AActor* entity = it->second;
	}
}

void CBehaviorTreeIdle::clear()
{
	CBehaviorTreeNode::clear();
}

void CBehaviorTreeIdle::setTargetCharactor(ACharacter* _value)
{
	CBehaviorTreeNode::setTargetCharactor(_value);
}

CBehaviorTreeIdle* CBehaviorTreeIdle::createInstance(ACharacter* _charactor, BehaviorTreeType _state)
{
	return new CBehaviorTreeIdle(_charactor, _state);
}

CBehaviorTreeIdle::CBehaviorTreeIdle(ACharacter* _charactor, BehaviorTreeType _state):
	CBehaviorTreeNode(_charactor,_state)
{

}
