#include "CBehaviorTreePatrol.h"
#include "CBehaviorTree.h"

const float checkWaitTime = 3.0f;
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

void CBehaviorTreePatrol::translateTo(CBehaviorTree* _tree, BehaviorTreeType _nextstate, float translatetime /*= 0.0f*/)
{
	CBehaviorTreeNode::translateTo(_tree,_nextstate, translatetime);
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
	if (_checkmovedir != NONE)
		_checkinvervaltime += deteltime;
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
	CBehaviorTreeNode(_charactor,_state),
	_checkinvervaltime(0),
	_checkmovedir(NONE)
{

}

void CBehaviorTreePatrol::checkRoad()
{
	if (_aiController == NULL)
		return;
	FVector startLocation = _aiController->GetActorLocation();
	FRotator playerRotation = _aiController->GetActorRotation();
	const float rayLength = 300.0f;
	FVector forward = _aiController->GetActorForwardVector();
	FVector back = -forward;
	FVector right = _aiController->GetActorRightVector();
	FVector left = -right;
	FHitResult hitResult;
	FCollisionQueryParams QueryParams = FCollisionQueryParams("", false, _aiController);
	const UWorld* wp = _aiController->GetWorld();
	FVector lineTrace = startLocation + forward * rayLength;
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
	AActor* hitObject = hitResult.GetActor();
	_checkmovedir = NONE;
	float minDistance = 300.0f;
	float fowardDistance = 300.0f;
	if (hitObject != NULL)
	{
		fowardDistance = hitResult.Distance;
		if (fowardDistance < minDistance)
		{
			minDistance = fowardDistance;
			_checkmovedir = FOWARD;
		}
	}

	float backDistance = 300.0f;
	lineTrace = startLocation + back * rayLength;
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
	hitObject = hitResult.GetActor();
	if (hitObject != NULL)
	{
		backDistance = hitResult.Distance;
		if (backDistance < minDistance)
		{
			minDistance = backDistance;
			_checkmovedir = BACK;
		}
	}

	float rightDistance = 300.0f;
	lineTrace = startLocation + right * rayLength;
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
	hitObject = hitResult.GetActor();
	if (hitObject != NULL)
	{
		rightDistance = hitResult.Distance;
		if (rightDistance < minDistance)
		{
			minDistance = rightDistance;
			_checkmovedir = RIGHT;
		}
	}

	float leftDistance = 300.0f;
	lineTrace = startLocation + left * rayLength;
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
	hitObject = hitResult.GetActor();
	if (hitObject != NULL)
	{
		leftDistance = hitResult.Distance;
		if (leftDistance < minDistance)
		{
			minDistance = leftDistance;
			_checkmovedir = LEFT;
		}
	}

	if (_checkmovedir != NONE)
	{
		_checkinvervaltime = 0;
	}
}
