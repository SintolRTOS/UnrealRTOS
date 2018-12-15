#include "CBehaviorTree.h"

namespace SintolRTI {
	CBehaviorTree::CBehaviorTree():
		_aicontroller(NULL),
		_curnode(NULL)
	{

	}

	CBehaviorTree::~CBehaviorTree()
	{

	}

	void CBehaviorTree::update(float detaltime)
	{
		for (std::map<int, CBehaviorTreeNode*>::iterator it = BehaviorTreeMap.begin();it != BehaviorTreeMap.end(); it++)
		{
			it->second->update(detaltime);
		}
	}

	void CBehaviorTree::setCharactor(ACharacter* _charactor)
	{
		_aicontroller = _charactor;
	}

	void CBehaviorTree::initBehaviorTrees()
	{
		CBehaviorTreeNode* _stateNode = new CBehaviorTreeNode(_aicontroller, IDLE);
		BehaviorTreeMap.insert(std::make_pair(IDLE, _stateNode));
		_stateNode = new CBehaviorTreeNode(_aicontroller, MOVE);
		BehaviorTreeMap.insert(std::make_pair(MOVE, _stateNode));
		_stateNode = new CBehaviorTreeNode(_aicontroller, CHECKTASK);
		BehaviorTreeMap.insert(std::make_pair(CHECKTASK, _stateNode));
		_stateNode = new CBehaviorTreeNode(_aicontroller, FOLLOW);
		BehaviorTreeMap.insert(std::make_pair(FOLLOW, _stateNode));
	}

	void CBehaviorTree::startBehaviorNode(BehaviorTreeType _type)
	{
		if (BehaviorTreeMap.find(_type) != BehaviorTreeMap.end())
		{
			_curnode = BehaviorTreeMap[_type];
			_curnode->enterState(NONE);
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
}
