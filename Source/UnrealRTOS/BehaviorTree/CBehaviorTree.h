#ifndef _BEHAVIRO_TREE_H
#define _BEHAVIRO_TREE_H
#include "../EntityManager.h"
#include "CBehaviorTreeNode.h"
#include "CBehaviorTreeIdle.h"
#include "CBehaviorTreePatrol.h"
#include "CBehaviorTreeFollow.h"
#include "GameFramework/Character.h"

namespace SintolRTI
{
	class CBehaviorTree
	{
	public:
		CBehaviorTree();
		~CBehaviorTree();
		void update(float detaltime);
		void setCharactor(ACharacter* _charactor);
		void initBehaviorTrees();
		void startBehaviorNode(BehaviorTreeType _type);
		void clear();
		void addBehaviorTreeNode(BehaviorTreeType _type);
		void addBehaviorTreeNode(BehaviorTreeType _type, ACharacter* _target);
	private:
		ACharacter* _aicontroller;
		std::map<int,CBehaviorTreeNode*> BehaviorTreeMap;
		CBehaviorTreeNode* _curnode;
	};
}

#endif // _BEHAVIRO_TREE_H
