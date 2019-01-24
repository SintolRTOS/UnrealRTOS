#include "CoreMinimal.h"
#include "CBehaviorTreeIdle.h"
#include "CBehaviorTree.h"
#include "Public/DrawDebugHelpers.h"
#include "../EntityManager.h"

const float _thinkwaittime = 5.0f;

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
	_thinktimedetal += deteltime;
}

void CBehaviorTreeIdle::doLogic()
{
	CBehaviorTreeNode::doLogic();
	checkCharactor();
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
	CBehaviorTreeNode(_charactor,_state),
	_thinktimedetal(0)
{

}

void CBehaviorTreeIdle::checkCharactor()
{
	FVector startLocation = _aiController->GetActorLocation();
	FRotator playerRotation = _aiController->GetActorRotation();
	const float rayLength = 300.0f;
	FVector endLocation = playerRotation.Vector()*rayLength;
	FVector lineTrace = startLocation + endLocation;
	const UWorld* wp = _aiController->GetWorld();
	DrawDebugLine(wp, startLocation, lineTrace, FColor(255, 0, 0),
		false, 0.0f, 0.0f, 1.0f);
	FHitResult hitResult;
	FCollisionQueryParams QueryParams = FCollisionQueryParams("", false, _aiController);
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
	AActor* hitObject = hitResult.GetActor();
	if (hitObject != NULL)
	{
		for (std::map<rti1516::ObjectInstanceHandle, AActor*>::const_iterator it = SintolRTI::EntityManager::GetInstance()->GetEnitiyActorMap().begin();
			it != SintolRTI::EntityManager::GetInstance()->GetEnitiyActorMap().end(); it++)
		{
			if (hitObject == it->second)
			{
				UE_LOG(LogTemp, Warning, TEXT("HitActor Name: %s"), *(hitObject->GetName()));
				_nextstate = FOLLOW;
				_runstate = TRANSLATE;
				break;
			}
		}
	}
}

void CBehaviorTreeIdle::thinkTranslate()
{
	if (_thinktimedetal < _thinkwaittime)
		return;
	_runstate = TRANSLATE;
	int randvalue = FMath::FRand() * 100;
	if (randvalue <= 10)
	{
		_nextstate = CHECKTASK;
	}
	_thinktimedetal = 0;
}
