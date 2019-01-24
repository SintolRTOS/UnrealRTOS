#include "CBehaviorTreeFollow.h"
#include "CBehaviorTree.h"
#include "Public/DrawDebugHelpers.h"


const static float MaxFollowDistance = 600.0f;

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
		FVector _localFoword = _aiController->GetActorForwardVector();
		_localFoword.Z = 0;
		_followFoword.Z = 0;
		_localFoword.Normalize();
		_followFoword.Normalize();
		float _cosValue = FVector::DotProduct(_localFoword, _followFoword);
		float rotateAngle = FMath::Acos(_cosValue);
		FRotator _localrotation = _aiController->GetActorRotation();
		_localrotation.Yaw += rotateAngle;
		_aiController->FaceRotation(_localrotation, _timedetal);
		_aiController->AddMovementInput(_aiController->GetActorForwardVector());

		bool checkFollow = checkMaxFollowDistance();
		if (checkFollow)
		{
			FVector lineTrace = _localLocation + _tartLocation;
			const UWorld* wp = _aiController->GetWorld();
			DrawDebugLine(wp, _localLocation, lineTrace, FColor(0, 255, 0),
				false, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Lost Follow Target!"));
			_runstate = TRANSLATE;
			int randvalue =  FMath::FRand() * 100;
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
