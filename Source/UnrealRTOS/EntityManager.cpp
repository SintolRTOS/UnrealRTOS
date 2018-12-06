#include "EntityManager.h"
#include "UnrealRTOSCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CoreMinimal.h"

namespace SintolRTI {
	EntityManager* EntityManager::_instance = NULL;

	EntityManager::~EntityManager()
	{

	}

	EntityManager* EntityManager::GetInstance()
	{
		if (_instance == NULL)
			_instance = new	EntityManager();
		return _instance;
	}

	const std::map<rti1516::ObjectInstanceHandle, AActor*>& EntityManager::GetEnitiyActorMap()
	{
		return EntityActorMap;
	}

	bool EntityManager::addEntityActor(const rti1516::ObjectInstanceHandle& key, AActor* value)
	{
		if (EntityActorMap.find(key) != EntityActorMap.end() || value == nullptr)
		{
			return false;
		}
		EntityActorMap.insert(std::make_pair(key, value));
		return true;
	}

	int EntityManager::deleteEntityActor(const rti1516::ObjectInstanceHandle& key)

	{
		if (EntityActorMap.find(key) == EntityActorMap.end())
		{
			return false;
		}
		EntityActorMap[key]->Destroy();
		return EntityActorMap.erase(key);
	}

	void EntityManager::updateEntityActor(rti1516::ObjectInstanceHandle objhandle, const rti1516::AttributeHandleValueMap& objattribution, const rti1516::VariableLengthData& objtag)
	{
		if (EntityActorMap.find(objhandle) != EntityActorMap.end())
		{
			std::string _multiName = toString(objtag);
			for (rti1516::AttributeHandleValueMap::const_iterator it = objattribution.begin(); it != objattribution.end(); it++)
			{
				std::string jsoninfo = toString(it->second);
				FString _jsonStr(jsoninfo.c_str());
				TSharedPtr<FJsonObject> _jsonObject;
				TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(_jsonStr);
				if (FJsonSerializer::Deserialize(JsonReader, _jsonObject))
				{
					FString _flocation = _jsonObject->GetStringField("location");
					FString _frotation = _jsonObject->GetStringField("rotation");
					FString _fvelocity = _jsonObject->GetStringField("velocity");
					int _movemode = _jsonObject->GetNumberField("movemode");
					FVector _location;
					_location.InitFromString(_flocation);
					FRotator _rotation;
					_rotation.InitFromString(_frotation);
					FVector _veloctiy;
					_veloctiy.InitFromString(_fvelocity);
					EntityActorMap[objhandle]->SetActorLocationAndRotation(_location, _rotation);
					((AEntityCharacter*)EntityActorMap[objhandle])->GetMovementComponent()->Velocity = _veloctiy;
				}
				//std::cout << _multiName << ":" << locationinfo << std::endl;
			}
		}
	}

	void EntityManager::SetTempleEntityCharactor(TSubclassOf<AEntityCharacter>& _temple)
	{
		_TempleCharactor = _temple;
	}

	void EntityManager::createAActorWithTemple(const rti1516::ObjectInstanceHandle& handle,const FVector& birtpos, const FRotator& birthrotate)
	{
		if (_TempleCharactor != nullptr)
		{
			if (_world)
			{
				// if world exists  
				AEntityCharacter* _entity = _world->SpawnActor<AEntityCharacter>(_TempleCharactor, birtpos, birthrotate);
				addEntityActor(handle, _entity);
			}
		}
	}

	void EntityManager::setWolrd(UWorld* world)
	{
		_world = world;
	}

	void EntityManager::Clear()
	{
		for (std::map<rti1516::ObjectInstanceHandle, AActor*>::iterator it = EntityActorMap.begin(); it != EntityActorMap.end(); it++)
		{
			it->second->Destroy();
		}
		EntityActorMap.clear();
	}

	EntityManager::EntityManager()
	{

	}
}
