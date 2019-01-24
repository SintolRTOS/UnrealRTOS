#include "CBehaviorTreePatrol.h"
#include "CBehaviorTree.h"
#include "Public/DrawDebugHelpers.h"

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
	if (_checkmovedir != NONEDIR)
	{
		_checkinvervaltime += deteltime;
	}
}

void CBehaviorTreePatrol::doLogic()
{
	CBehaviorTreeNode::doLogic();

	if (_checkmovedir == NONEDIR)
	{
		checkRoad();
	}
	else
	{
		runRoad();
		findActor();
	}
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
	_checkmovedir(NONEDIR)
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
	_checkmovedir = FOWARD;
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

	if (_checkmovedir != NONEDIR)
	{
		_checkinvervaltime = 0;
	}
}

void CBehaviorTreePatrol::runRoad()
{
	if (_aiController == NULL)
		return;
	if (checkWaitTime < _checkinvervaltime)
	{
		_checkmovedir = NONEDIR;
		_checkinvervaltime = 0;
	}
	if (_checkmovedir == FOWARD)
	{
		// find out which way is forward
		const FRotator Rotation = _aiController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		_aiController->AddMovementInput(Direction, 1.0);
	}
	else if (_checkmovedir == LEFT)
	{
		// find out which way is right
		const FRotator Rotation = _aiController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		_aiController->AddMovementInput(Direction, -1.0f);
	}
	else if (_checkmovedir == RIGHT)
	{
		// find out which way is right
		const FRotator Rotation = _aiController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		_aiController->AddMovementInput(Direction, 1.0f);
	}
	else if (_checkmovedir == BACK)
	{
		// find out which way is forward
		const FRotator Rotation = _aiController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		_aiController->AddMovementInput(Direction, -1.0);
	}
}

void CBehaviorTreePatrol::findActor()
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
