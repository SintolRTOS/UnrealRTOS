#ifndef _UNREAL_RTOS_AMBASSADOR_H
#define _UNREAL_RTOS_AMBASSADOR_H
#pragma warning (disable:4290)
#include "../../ThirdParty/SDKManager.h"
#include "EntityManager.h"
#include <Clock.h>
#include <StringUtils.h>

namespace SintolRTI {

	class UnrealRTOSAmbassador : public rti1516::FederateAmbassador {
	public:

		UnrealRTOSAmbassador()
		{ }
		virtual ~UnrealRTOSAmbassador()
			throw ()
		{ }

		void receiveInteraction(rti1516::InteractionClassHandle interactionClassHandle,
			const rti1516::ParameterHandleValueMap& parameterValues,
			const rti1516::VariableLengthData& tag,
			rti1516::OrderType sentOrder,
			rti1516::TransportationType theType)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::FederateInternalError)
		{

		}

		void federationSynchronized(const std::wstring& label)
			throw (rti1516::FederateInternalError)
		{
			SDKManager::GetInstance()->insertSyncfedearetionSet(label);
		}

		virtual void announceSynchronizationPoint(const std::wstring& label, const rti1516::VariableLengthData& tag)
			throw (rti1516::FederateInternalError)
		{
			SDKManager::GetInstance()->synchronizationPointAchieved(label);
		}

		virtual void synchronizationPointRegistrationSucceeded(const std::wstring& label)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void synchronizationPointRegistrationFailed(const std::wstring& label, rti1516::SynchronizationFailureReason reason)
			throw (rti1516::FederateInternalError)
		{
		}


		virtual void initiateFederateSave(const std::wstring& label)
			throw (rti1516::UnableToPerformSave,
				rti1516::FederateInternalError)
		{
		}

		virtual void initiateFederateSave(const std::wstring& label, const rti1516::LogicalTime& logicalTime)
			throw (rti1516::UnableToPerformSave,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
		}

		virtual void federationSaved()
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void federationNotSaved(rti1516::SaveFailureReason theSaveFailureReason)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void federationSaveStatusResponse(const rti1516::FederateHandleSaveStatusPairVector& theFederateStatusVector)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void requestFederationRestoreSucceeded(const std::wstring& label)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void requestFederationRestoreFailed(const std::wstring& label)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void federationRestoreBegun()
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void initiateFederateRestore(const std::wstring& label, rti1516::FederateHandle handle)
			throw (rti1516::SpecifiedSaveLabelDoesNotExist,
				rti1516::CouldNotInitiateRestore,
				rti1516::FederateInternalError)
		{
		}

		virtual void federationRestored()
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void federationNotRestored(rti1516::RestoreFailureReason theRestoreFailureReason)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void federationRestoreStatusResponse(const rti1516::FederateHandleRestoreStatusPairVector& theFederateStatusVector)
			throw (rti1516::FederateInternalError)
		{
		}

		virtual void startRegistrationForObjectClass(rti1516::ObjectClassHandle)
			throw (rti1516::ObjectClassNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void stopRegistrationForObjectClass(rti1516::ObjectClassHandle)
			throw (rti1516::ObjectClassNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void turnInteractionsOn(rti1516::InteractionClassHandle)
			throw (rti1516::InteractionClassNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void turnInteractionsOff(rti1516::InteractionClassHandle)
			throw (rti1516::InteractionClassNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void objectInstanceNameReservationSucceeded(const std::wstring&)
			throw (rti1516::UnknownName,
				rti1516::FederateInternalError)
		{
		}

		virtual void objectInstanceNameReservationFailed(const std::wstring&)
			throw (rti1516::UnknownName,
				rti1516::FederateInternalError)
		{
		}

		virtual void discoverObjectInstance(rti1516::ObjectInstanceHandle objhandle, rti1516::ObjectClassHandle classhandle, const std::wstring&)
			throw (rti1516::CouldNotDiscover,
				rti1516::ObjectClassNotKnown,
				rti1516::FederateInternalError)
		{
			EntityManager::GetInstance()->createAActorWithTemple(objhandle, FVector(0, 0, 0), FRotator(0, 0, 0));
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objhandle, const rti1516::AttributeHandleValueMap& objattribution,
			const rti1516::VariableLengthData& tag, rti1516::OrderType, rti1516::TransportationType)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
			EntityManager::GetInstance()->updateEntityActor(objhandle, objattribution, tag);
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objectInstanceHandle, const rti1516::AttributeHandleValueMap& attributeHandleValueMap,
			const rti1516::VariableLengthData& tag, rti1516::OrderType orderType, rti1516::TransportationType transportationType,
			const rti1516::RegionHandleSet&)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
			reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, tag, orderType, transportationType);
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objectInstanceHandle, const rti1516::AttributeHandleValueMap& attributeHandleValueMap,
			const rti1516::VariableLengthData& tag, rti1516::OrderType orderType, rti1516::TransportationType transportationType,
			const rti1516::LogicalTime&, rti1516::OrderType)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
			reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, tag, orderType, transportationType);
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objectInstanceHandle, const rti1516::AttributeHandleValueMap& attributeHandleValueMap,
			const rti1516::VariableLengthData& tag, rti1516::OrderType orderType, rti1516::TransportationType transportationType,
			const rti1516::LogicalTime& logicalTime, rti1516::OrderType receivedOrder, const rti1516::RegionHandleSet&)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
			reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, tag, orderType, transportationType, logicalTime, receivedOrder);
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objectInstanceHandle, const rti1516::AttributeHandleValueMap& attributeHandleValueMap,
			const rti1516::VariableLengthData& tag, rti1516::OrderType orderType, rti1516::TransportationType transportationType,
			const rti1516::LogicalTime& logicalTime, rti1516::OrderType receivedOrder, rti1516::MessageRetractionHandle)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
			reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, tag, orderType, transportationType, logicalTime, receivedOrder);
		}

		virtual void reflectAttributeValues(rti1516::ObjectInstanceHandle objectInstanceHandle, const rti1516::AttributeHandleValueMap& attributeHandleValueMap,
			const rti1516::VariableLengthData& tag, rti1516::OrderType orderType, rti1516::TransportationType transportationType,
			const rti1516::LogicalTime& logicalTime, rti1516::OrderType receivedOrder, rti1516::MessageRetractionHandle,
			const rti1516::RegionHandleSet& regionHandleSet)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
			reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, tag, orderType, transportationType, logicalTime, receivedOrder, regionHandleSet);
		}

		virtual void receiveInteraction(rti1516::InteractionClassHandle theInteraction, const rti1516::ParameterHandleValueMap& theParameterValues,
			const rti1516::VariableLengthData& theUserSuppliedTag, rti1516::OrderType sentOrder, rti1516::TransportationType theType,
			const rti1516::RegionHandleSet&)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::FederateInternalError)
		{
			receiveInteraction(theInteraction, theParameterValues, theUserSuppliedTag, sentOrder, theType);
		}

		virtual void receiveInteraction(rti1516::InteractionClassHandle theInteraction,
			rti1516::ParameterHandleValueMap const & theParameterValues,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::TransportationType theType,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::FederateInternalError)
		{
			receiveInteraction(theInteraction, theParameterValues, theUserSuppliedTag, sentOrder, theType);
		}

		virtual void receiveInteraction(rti1516::InteractionClassHandle theInteraction,
			rti1516::ParameterHandleValueMap const & theParameterValues,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::TransportationType theType,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder,
			rti1516::RegionHandleSet const & theSentRegionHandleSet)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::FederateInternalError)
		{
			receiveInteraction(theInteraction, theParameterValues, theUserSuppliedTag, sentOrder, theType, theTime, receivedOrder);
		}

		virtual void receiveInteraction(rti1516::InteractionClassHandle theInteraction,
			rti1516::ParameterHandleValueMap const & theParameterValues,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::TransportationType theType,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder,
			rti1516::MessageRetractionHandle theHandle)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
			receiveInteraction(theInteraction, theParameterValues, theUserSuppliedTag, sentOrder, theType, theTime, receivedOrder);
		}

		virtual void receiveInteraction(rti1516::InteractionClassHandle theInteraction,
			rti1516::ParameterHandleValueMap const & theParameterValues,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::TransportationType theType,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder,
			rti1516::MessageRetractionHandle theHandle,
			rti1516::RegionHandleSet const & theSentRegionHandleSet)
			throw (rti1516::InteractionClassNotRecognized,
				rti1516::InteractionParameterNotRecognized,
				rti1516::InteractionClassNotSubscribed,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
			receiveInteraction(theInteraction, theParameterValues, theUserSuppliedTag, sentOrder, theType, theTime, receivedOrder, theSentRegionHandleSet);
		}

		virtual void removeObjectInstance(rti1516::ObjectInstanceHandle theObject,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::FederateInternalError)
		{
			EntityManager::GetInstance()->deleteEntityActor(theObject);
		}

		virtual void removeObjectInstance(rti1516::ObjectInstanceHandle theObject,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::FederateInternalError)
		{
			removeObjectInstance(theObject, theUserSuppliedTag, sentOrder);
		}

		virtual void removeObjectInstance(rti1516::ObjectInstanceHandle theObject,
			rti1516::VariableLengthData const & theUserSuppliedTag,
			rti1516::OrderType sentOrder,
			rti1516::LogicalTime const & theTime,
			rti1516::OrderType receivedOrder,
			rti1516::MessageRetractionHandle theHandle)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::InvalidLogicalTime,
				rti1516::FederateInternalError)
		{
			removeObjectInstance(theObject, theUserSuppliedTag, sentOrder, theTime, receivedOrder);
		}

		virtual void attributesInScope(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
		}

		virtual void attributesOutOfScope(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotSubscribed,
				rti1516::FederateInternalError)
		{
		}

		virtual void provideAttributeValueUpdate(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes,
			rti1516::VariableLengthData const & theUserSuppliedTag)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotOwned,
				rti1516::FederateInternalError)
		{
		}

		virtual void turnUpdatesOnForObjectInstance(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotOwned,
				rti1516::FederateInternalError)
		{
		}

		virtual void turnUpdatesOffForObjectInstance(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotOwned,
				rti1516::FederateInternalError)
		{
		}

		virtual void requestAttributeOwnershipAssumption(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & offeredAttributes,
			rti1516::VariableLengthData const & theUserSuppliedTag)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeAlreadyOwned,
				rti1516::AttributeNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void requestDivestitureConfirmation(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & releasedAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotOwned,
				rti1516::AttributeDivestitureWasNotRequested,
				rti1516::FederateInternalError)
		{
		}

		virtual void attributeOwnershipAcquisitionNotification(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & securedAttributes,
			rti1516::VariableLengthData const & theUserSuppliedTag)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeAcquisitionWasNotRequested,
				rti1516::AttributeAlreadyOwned,
				rti1516::AttributeNotPublished,
				rti1516::FederateInternalError)
		{
		}

		virtual void attributeOwnershipUnavailable(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeAlreadyOwned,
				rti1516::AttributeAcquisitionWasNotRequested,
				rti1516::FederateInternalError)
		{
		}

		virtual void requestAttributeOwnershipRelease(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & candidateAttributes,
			rti1516::VariableLengthData const & theUserSuppliedTag)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeNotOwned,
				rti1516::FederateInternalError)
		{
		}

		virtual void confirmAttributeOwnershipAcquisitionCancellation(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandleSet const & theAttributes)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::AttributeAlreadyOwned,
				rti1516::AttributeAcquisitionWasNotCanceled,
				rti1516::FederateInternalError)
		{
		}

		virtual void informAttributeOwnership(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandle theAttribute,
			rti1516::FederateHandle theOwner)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::FederateInternalError)
		{
		}

		virtual void attributeIsNotOwned(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandle theAttribute)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::FederateInternalError)
		{
		}

		virtual void attributeIsOwnedByRTI(rti1516::ObjectInstanceHandle theObject,
			rti1516::AttributeHandle theAttribute)
			throw (rti1516::ObjectInstanceNotKnown,
				rti1516::AttributeNotRecognized,
				rti1516::FederateInternalError)
		{
		}

		virtual void timeRegulationEnabled(rti1516::LogicalTime const & theFederateTime)
			throw (rti1516::InvalidLogicalTime,
				rti1516::NoRequestToEnableTimeRegulationWasPending,
				rti1516::FederateInternalError)
		{
		}

		virtual void timeConstrainedEnabled(rti1516::LogicalTime const & theFederateTime)
			throw (rti1516::InvalidLogicalTime,
				rti1516::NoRequestToEnableTimeConstrainedWasPending,
				rti1516::FederateInternalError)
		{
		}

		virtual void timeAdvanceGrant(rti1516::LogicalTime const & theTime)
			throw (rti1516::InvalidLogicalTime,
				rti1516::JoinedFederateIsNotInTimeAdvancingState,
				rti1516::FederateInternalError)
		{
		}

		virtual void requestRetraction(rti1516::MessageRetractionHandle theHandle)
			throw (rti1516::FederateInternalError)
		{
		}

	};
}
#endif // !1

