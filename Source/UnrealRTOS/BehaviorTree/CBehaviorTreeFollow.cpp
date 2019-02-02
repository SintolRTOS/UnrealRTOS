#include "CBehaviorTreeFollow.h"
#include "CBehaviorTree.h"
#include "Public/DrawDebugHelpers.h"


const static float MaxFollowDistance = 2000.0f;

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

	if (_target != NULL)
	{
		FVector _tartLocation = _target->GetActorLocation();
		FVector _localLocation = _aiController->GetActorLocation();
		FVector _followFoword = _tartLocation - _localLocation;

		_aiController->AddMovementInput(_followFoword, 1.0);
		checkJump();
		bool checkFollow = checkMaxFollowDistance();
		if (checkFollow)
		{
			FVector lineTrace = _tartLocation;
			const UWorld* wp = _aiController->GetWorld();
			DrawDebugLine(wp, _localLocation, lineTrace, FColor(0, 255, 0),
				false, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Lost Follow Target!"));
			int randvalue =  FMath::FRand() * 100;
			_runstate = TRANSLATE;
			if (randvalue <= 10)
			{
				_nextstate = IDLE;
			}
			else
			{
				_nextstate = CHECKTASK;
			}
		}
	}
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

bool CBehaviorTreeFollow::checkMaxFollowDistance()
{
	if (NULL == _aiController || _target == NULL)
		return false;
	float _curFollowDis = (_aiController->GetActorLocation() - _target->GetActorLocation()).Size();
	if (_curFollowDis > MaxFollowDistance)
		return false;
	return true;
}

void CBehaviorTreeFollow::checkJump()
{
	if (_aiController == NULL)
		return;
	FVector startLocation = _aiController->GetActorLocation();
	FRotator playerRotation = _aiController->GetActorRotation();
	const float rayLength = 60.0f;
	FVector forward = _aiController->GetActorForwardVector();
	FHitResult hitResult;
	FCollisionQueryParams QueryParams = FCollisionQueryParams("", false, _aiController);
	const UWorld* wp = _aiController->GetWorld();
	FVector lineTrace = startLocation + forward * rayLength;
	wp->LineTraceSingleByObjectType(hitResult, startLocation, lineTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), QueryParams);
	AActor* hitObject = hitResult.GetActor();
	if (hitObject != NULL)
	{
		if (hitObject->Tags.Num() != 0 && hitObject->Tags[0] == "jump")
		{
			_aiController->Jump();
			return;
		}
		return;
	}
}
