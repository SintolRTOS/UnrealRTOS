#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include <iostream>
#include "EntityCharacter.h"
#include "GameFramework/Character.h"

namespace SintolRTI {
	class EntityManager {
	private:
		std::map<rti1516::ObjectInstanceHandle, AActor*> EntityActorMap;
		EntityManager();
		static EntityManager* _instance;
		TSubclassOf<AEntityCharacter> _TempleCharactor;
		UWorld* _world;
		std::string
			toString(const rti1516::VariableLengthData& variableLengthData)
		{
			if (!variableLengthData.size())
				return std::string();
			return std::string((const char*)variableLengthData.data(), variableLengthData.size());
		}
	public:
		virtual ~EntityManager();
		static EntityManager* GetInstance();
		const std::map<rti1516::ObjectInstanceHandle, AActor*>& GetEnitiyActorMap();
		bool addEntityActor(const rti1516::ObjectInstanceHandle& key, AActor* value);
		int deleteEntityActor(const rti1516::ObjectInstanceHandle& key);
		void updateEntityActor(rti1516::ObjectInstanceHandle objhandle, const rti1516::AttributeHandleValueMap& objattribution, const rti1516::VariableLengthData& objtag );
		void SetTempleEntityCharactor(TSubclassOf<AEntityCharacter>& _temple);
		void createAActorWithTemple(const rti1516::ObjectInstanceHandle& handle, const FVector& birtpos, const FRotator& birthrotate);
		void setWolrd(UWorld* world);
		void Clear();
	};
}
#endif
