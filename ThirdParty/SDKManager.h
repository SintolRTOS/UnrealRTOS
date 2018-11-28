#ifndef _SDKMANAGER_H_
#define _SDKMANAGER_H_

#include <ScopeLock.h>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#pragma warning (disable:4290)

#include <RTI/FederateAmbassador.h>
#include <RTI/RTIambassadorFactory.h>
#include <RTI/RTIambassador.h>
#include <RTI/LogicalTime.h>
#include <RTI/LogicalTimeInterval.h>
#include <RTI/LogicalTimeFactory.h>
#include <RTI/RangeBounds.h>

namespace SintolRTI {
	class SintolRTI_LOCAL SDKManager {
	public:
		static SDKManager* GetInstance();
		static void Clear();
		bool InitSDK(
			rti1516::FederateAmbassador& federaambassador,
			std::wstring const & federationExecutionName,
			std::wstring const & federateType,
			std::wstring const & fullPathNameToTheFDDfile,
			std::wstring const connectaddress,
			std::wstring const localtimefactory = L"HLAinteger64Time");
		virtual ~SDKManager();
		bool insertSyncfedearetionSet(std::wstring label);
		void synchronizationPointAchieved(std::wstring label);
		rti1516::ObjectClassHandle getObjectClassHandle(std::wstring name);
		rti1516::AttributeHandle getAttributeHandle(rti1516::ObjectClassHandle rti1516ObjectClassHandle,
			std::wstring const & attributeName);
		void publishObjectClassAttributes(rti1516::ObjectClassHandle theClass, rti1516::AttributeHandleSet const & rti1516AttributeHandleSet);
		void subscribeObjectClassAttributes(rti1516::ObjectClassHandle theClass, rti1516::AttributeHandleSet const & attributeList, bool active = true);
		rti1516::ObjectInstanceHandle registerObjectInstance(rti1516::ObjectClassHandle rti1516ObjectClassHandle);
		void updateAttributeValues(rti1516::ObjectInstanceHandle rti1516ObjectInstanceHandle, const rti1516::AttributeHandleValueMap& rti1516AttributeValues, const rti1516::VariableLengthData& rti1516Tag);
		void deleteObjectInstance(rti1516::ObjectInstanceHandle rti1516ObjectInstanceHandle,
			const rti1516::VariableLengthData& rti1516Tag);
		void unpublishObjectClass(rti1516::ObjectClassHandle rti1516ObjectClassHandle);
		void unpublishObjectClassAttributes(rti1516::ObjectClassHandle rti1516ObjectClassHandle,
			rti1516::AttributeHandleSet const & rti1516AttributeHandleSet);
		void unsubscribeObjectClass(rti1516::ObjectClassHandle rti1516ObjectClassHandle);
		std::auto_ptr<rti1516::RTIambassador> getRTIambassador()
		{
			return ambassador;
		}
		std::wstring getFedarateType()
		{
			return _federateType;
		}
		std::wstring getFaderateName()
		{
			return _federateName;
		}
		rti1516::FederateHandle getFedarateHandle()
		{
			return _federateHandle;
		}
		const std::set<std::wstring>& getFedarateSet()
		{
			return _federateSet;
		}
		const std::vector<std::wstring>& getFedrateList()
		{
			return _federateList;
		}
		bool StopSDK();
		void Update(double approximateMinimumTimeInSeconds);
	private:
		static SDKManager* _instance;
		bool waitForAllFederates();
		bool _isstarted;
		bool execJoined();
		rti1516::FederateHandle _federateHandle;
		std::wstring _federateType;
		std::wstring _federateName;
		std::auto_ptr<rti1516::RTIambassador> ambassador;
		std::set<std::wstring> _federateSet;
		std::vector<std::wstring> _federateList;
		int _synchronized = 0;
		static Mutex _mutex;
		SDKManager();
	};
}
#endif // !_SDKMANAGER_H_

