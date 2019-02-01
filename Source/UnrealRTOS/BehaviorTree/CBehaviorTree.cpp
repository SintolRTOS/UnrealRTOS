#include "CBehaviorTree.h"


CBehaviorTree::CBehaviorTree() :
	_aicontroller(NULL),
	_curnode(NULL)
{

}

CBehaviorTree::~CBehaviorTree()
{

}

void CBehaviorTree::update(float detaltime)
{
	//for (std::map<int, CBehaviorTreeNode*>::iterator it = BehaviorTreeMap.begin();it != BehaviorTreeMap.end(); it++)
	//{
	//	it->second->update(detaltime);
	//}
	if (_curnode != NULL)
	{
		_curnode->update(detaltime);
		if (_curnode->getRunState() == TRANSLATE)
		{
			if (_curnode->getNextNodeType() == FOLLOW)
			{
				translateTo(FOLLOW, 0, _curnode->getTargetCharactor());
			}
			else if (_curnode->getNextNodeType() == CHECKTASK)
			{
				translateTo(CHECKTASK, 1);
			}
		}
	}
}

void CBehaviorTree::setCharactor(ACharacter* _charactor)
{
	_aicontroller = _charactor;
}

void CBehaviorTree::initBehaviorTrees()
{
	//CBehaviorTreeNode* _stateNode = new CBehaviorTreeNode(_aicontroller, IDLE);
	//BehaviorTreeMap.insert(std::make_pair(IDLE, _stateNode));
	//_stateNode = new CBehaviorTreeNode(_aicontroller, MOVE);
	//BehaviorTreeMap.insert(std::make_pair(MOVE, _stateNode));
	//_stateNode = new CBehaviorTreeNode(_aicontroller, CHECKTASK);
	//BehaviorTreeMap.insert(std::make_pair(CHECKTASK, _stateNode));
	//_stateNode = new CBehaviorTreeNode(_aicontroller, FOLLOW);
	//BehaviorTreeMap.insert(std::make_pair(FOLLOW, _stateNode));
	addBehaviorTreeNode(IDLE);
	addBehaviorTreeNode(FOLLOW);
	addBehaviorTreeNode(CHECKTASK);
}

void CBehaviorTree::startBehaviorNode(BehaviorTreeType _type)
{
	if (BehaviorTreeMap.find(_type) != BehaviorTreeMap.end())
	{
		_curnode = BehaviorTreeMap[_type];
		_curnode->enterState(NONE);
		_curnode->onEnterState();
	}
}

void CBehaviorTree::translateTo(BehaviorTreeType _nextstate, float translatetime)
{
	_curnode->onLeaveState();
	if (BehaviorTreeMap.find(_nextstate) != BehaviorTreeMap.end())
	{
		_curnode = BehaviorTreeMap[_nextstate];
		_curnode->onEnterState();
		_curnode->wait(translatetime);
	}
}

void CBehaviorTree::translateTo(BehaviorTreeType _nextstate, float translatetime, ACharacter* _targetCharactor)
{
	_curnode->onLeaveState();
	if (BehaviorTreeMap.find(_nextstate) != BehaviorTreeMap.end())
	{
		_curnode = BehaviorTreeMap[_nextstate];
		_curnode->wait(translatetime);
		_curnode->setTargetCharactor(_targetCharactor);
		_curnode->onEnterState();
	}
}

void CBehaviorTree::clear()
{
	for (std::map<int, CBehaviorTreeNode*>::iterator it = BehaviorTreeMap.begin();
		it != BehaviorTreeMap.end(); it++)
	{
		it->second->clear();
		delete it->second;
	}
	BehaviorTreeMap.clear();
	_curnode = NULL;
}

void CBehaviorTree::addBehaviorTreeNode(BehaviorTreeType _type)
{
	if (_type == CHECKTASK)
	{
		if (BehaviorTreeMap.find(_type) == BehaviorTreeMap.end())
		{
			CBehaviorTreeNode* _stateNode = CBehaviorTreePatrol::createInstance(_aicontroller, CHECKTASK);
			BehaviorTreeMap.insert(std::make_pair(CHECKTASK, _stateNode));
		}
	}
	else if (_type == IDLE)
	{
		if (BehaviorTreeMap.find(_type) == BehaviorTreeMap.end())
		{
			CBehaviorTreeNode* _stateNode = CBehaviorTreeIdle::createInstance(_aicontroller, IDLE);
			BehaviorTreeMap.insert(std::make_pair(IDLE, _stateNode));
		}
	}
	else if (_type == FOLLOW)
	{
		if (BehaviorTreeMap.find(_type) == BehaviorTreeMap.end())
		{
			CBehaviorTreeNode* _stateNode = CBehaviorTreeFollow::createInstance(_aicontroller, FOLLOW, NULL);
			BehaviorTreeMap.insert(std::make_pair(FOLLOW, _stateNode));
		}
	}
}

void CBehaviorTree::addBehaviorTreeNode(BehaviorTreeType _type, ACharacter* _target)
{
	if (_type == FOLLOW)
	{
		if (BehaviorTreeMap.find(_type) == BehaviorTreeMap.end())
		{
			CBehaviorTreeNode* _stateNode = CBehaviorTreeFollow::createInstance(_aicontroller, FOLLOW, _target);
			BehaviorTreeMap.insert(std::make_pair(FOLLOW, _stateNode));
		}
	}
}


