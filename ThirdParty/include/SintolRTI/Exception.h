/* -*-c++-*- SintolRTI - Copyright (C) 2009-2012 Mathias Froehlich
 *
 * This file is part of SintolRTI.
 *
 * SintolRTI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * SintolRTI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SintolRTI.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SintolRTI_Exception_h
#define SintolRTI_Exception_h

#include <exception>
#include <string>

#include "Export.h"

namespace SintolRTI {

class SintolRTI_API Exception : public std::exception {
public:
  virtual ~Exception() throw();

  const char* what() const throw();
  const std::string& getReason() const throw();

protected:
  Exception(const char* type, const char* reason);
  Exception(const char* type, const std::string& reason);

private:
  std::string _reason;
};

class SintolRTI_API RTIinternalError : public Exception {
public:
  RTIinternalError(const char* reason = 0);
  RTIinternalError(const std::string& reason);
  virtual ~RTIinternalError() throw();

  static void assertMessage(const char* file, unsigned line, const char* reason = 0);
};

#if defined(NDEBUG) || defined(_NDEBUG)
#define SintolRTIAssert(expr) do { } while(0)
#else
#define SintolRTIAssert(expr) do { if (!(expr)) SintolRTI::RTIinternalError::assertMessage(__FILE__, __LINE__, #expr); } while(0)
#endif

#define RTI_EXCEPTION(name) \
class SintolRTI_API name : public Exception { \
public: \
  name(const char* reason = 0) : Exception( #name, reason) { }  \
  name(const std::string& reason) : Exception( #name, reason) { } \
  virtual ~name() throw() { } \
};

// SintolRTI exceptions
RTI_EXCEPTION(ResourceError) // unrecoverable errors when we run out of resources
RTI_EXCEPTION(TransportError) // unrecoverable errors on sockets or other transports
RTI_EXCEPTION(HTTPError) // unrecoverable errors on http connects
RTI_EXCEPTION(MessageError) // Inconsistent messages reaching a server

// rti ambassador type exceptions, this is the list in rti1516e as this is the most advanced
RTI_EXCEPTION(AlreadyConnected)
RTI_EXCEPTION(AsynchronousDeliveryAlreadyDisabled)
RTI_EXCEPTION(AsynchronousDeliveryAlreadyEnabled)
RTI_EXCEPTION(AttributeAcquisitionWasNotCanceled)
RTI_EXCEPTION(AttributeAcquisitionWasNotRequested)
RTI_EXCEPTION(AttributeAlreadyBeingAcquired)
RTI_EXCEPTION(AttributeAlreadyBeingChanged)
RTI_EXCEPTION(AttributeAlreadyBeingDivested)
RTI_EXCEPTION(AttributeAlreadyOwned)
RTI_EXCEPTION(AttributeDivestitureWasNotRequested)
RTI_EXCEPTION(AttributeNotDefined)
RTI_EXCEPTION(AttributeNotOwned)
RTI_EXCEPTION(AttributeNotPublished)
RTI_EXCEPTION(AttributeNotRecognized)
RTI_EXCEPTION(AttributeNotSubscribed)
RTI_EXCEPTION(AttributeRelevanceAdvisorySwitchIsOff)
RTI_EXCEPTION(AttributeRelevanceAdvisorySwitchIsOn)
RTI_EXCEPTION(AttributeScopeAdvisorySwitchIsOff)
RTI_EXCEPTION(AttributeScopeAdvisorySwitchIsOn)
RTI_EXCEPTION(BadInitializationParameter)
RTI_EXCEPTION(CallNotAllowedFromWithinCallback)
RTI_EXCEPTION(ConnectionFailed)
RTI_EXCEPTION(CouldNotCreateLogicalTimeFactory)
RTI_EXCEPTION(CouldNotDecode)
RTI_EXCEPTION(CouldNotDiscover)
RTI_EXCEPTION(CouldNotEncode)
RTI_EXCEPTION(CouldNotOpenFDD)
RTI_EXCEPTION(CouldNotOpenMIM)
RTI_EXCEPTION(CouldNotInitiateRestore)
RTI_EXCEPTION(DeletePrivilegeNotHeld)
RTI_EXCEPTION(DesignatorIsHLAstandardMIM)
RTI_EXCEPTION(RequestForTimeConstrainedPending)
RTI_EXCEPTION(NoRequestToEnableTimeConstrainedWasPending)
RTI_EXCEPTION(RequestForTimeRegulationPending)
RTI_EXCEPTION(NoRequestToEnableTimeRegulationWasPending)
RTI_EXCEPTION(NoFederateWillingToAcquireAttribute)
RTI_EXCEPTION(ErrorReadingFDD)
RTI_EXCEPTION(ErrorReadingMIM)
RTI_EXCEPTION(FederateAlreadyExecutionMember)
RTI_EXCEPTION(FederateHandleNotKnown)
RTI_EXCEPTION(FederateHasNotBegunSave)
RTI_EXCEPTION(FederateInternalError)
RTI_EXCEPTION(FederateIsExecutionMember)
RTI_EXCEPTION(FederateNameAlreadyInUse)
RTI_EXCEPTION(FederateNotExecutionMember)
RTI_EXCEPTION(FederateOwnsAttributes)
RTI_EXCEPTION(FederateServiceInvocationsAreBeingReportedViaMOM)
RTI_EXCEPTION(FederateUnableToUseTime)
RTI_EXCEPTION(FederatesCurrentlyJoined)
RTI_EXCEPTION(FederationExecutionAlreadyExists)
RTI_EXCEPTION(FederationExecutionDoesNotExist)
RTI_EXCEPTION(IllegalName)
RTI_EXCEPTION(IllegalTimeArithmetic)
RTI_EXCEPTION(InconsistentFDD)
RTI_EXCEPTION(InteractionClassAlreadyBeingChanged)
RTI_EXCEPTION(InteractionClassNotDefined)
RTI_EXCEPTION(InteractionClassNotPublished)
RTI_EXCEPTION(InteractionClassNotRecognized)
RTI_EXCEPTION(InteractionClassNotSubscribed)
RTI_EXCEPTION(InteractionParameterNotDefined)
RTI_EXCEPTION(InteractionParameterNotRecognized)
RTI_EXCEPTION(InteractionRelevanceAdvisorySwitchIsOff)
RTI_EXCEPTION(InteractionRelevanceAdvisorySwitchIsOn)
RTI_EXCEPTION(InTimeAdvancingState)
RTI_EXCEPTION(InvalidAttributeHandle)
RTI_EXCEPTION(InvalidDimensionHandle)
RTI_EXCEPTION(InvalidFederateHandle)
RTI_EXCEPTION(InvalidInteractionClassHandle)
RTI_EXCEPTION(InvalidLocalSettingsDesignator)
RTI_EXCEPTION(InvalidLogicalTime)
RTI_EXCEPTION(InvalidLogicalTimeInterval)
RTI_EXCEPTION(InvalidLookahead)
RTI_EXCEPTION(InvalidObjectClassHandle)
RTI_EXCEPTION(InvalidOrderName)
RTI_EXCEPTION(InvalidOrderType)
RTI_EXCEPTION(InvalidParameterHandle)
RTI_EXCEPTION(InvalidRangeBound)
RTI_EXCEPTION(InvalidRegion)
RTI_EXCEPTION(InvalidResignAction)
RTI_EXCEPTION(InvalidRegionContext)
RTI_EXCEPTION(InvalidMessageRetractionHandle)
RTI_EXCEPTION(InvalidServiceGroup)
RTI_EXCEPTION(InvalidTransportationName)
RTI_EXCEPTION(InvalidTransportationType)
RTI_EXCEPTION(InvalidUpdateRateDesignator)
RTI_EXCEPTION(JoinedFederateIsNotInTimeAdvancingState)
RTI_EXCEPTION(LogicalTimeAlreadyPassed)
RTI_EXCEPTION(MessageCanNoLongerBeRetracted)
RTI_EXCEPTION(NameNotFound)
RTI_EXCEPTION(NameSetWasEmpty)
RTI_EXCEPTION(NoAcquisitionPending)
RTI_EXCEPTION(NotConnected)
RTI_EXCEPTION(ObjectClassNotDefined)
RTI_EXCEPTION(ObjectClassNotKnown)
RTI_EXCEPTION(ObjectClassNotPublished)
RTI_EXCEPTION(ObjectClassRelevanceAdvisorySwitchIsOff)
RTI_EXCEPTION(ObjectClassRelevanceAdvisorySwitchIsOn)
RTI_EXCEPTION(ObjectInstanceNameInUse)
RTI_EXCEPTION(ObjectInstanceNameNotReserved)
RTI_EXCEPTION(ObjectInstanceNotKnown)
RTI_EXCEPTION(OwnershipAcquisitionPending)
// RTI_EXCEPTION(RTIinternalError)
RTI_EXCEPTION(RegionDoesNotContainSpecifiedDimension)
RTI_EXCEPTION(RegionInUseForUpdateOrSubscription)
RTI_EXCEPTION(RegionNotCreatedByThisFederate)
RTI_EXCEPTION(RestoreInProgress)
RTI_EXCEPTION(RestoreNotInProgress)
RTI_EXCEPTION(RestoreNotRequested)
RTI_EXCEPTION(SaveInProgress)
RTI_EXCEPTION(SaveNotInProgress)
RTI_EXCEPTION(SaveNotInitiated)
RTI_EXCEPTION(SpecifiedSaveLabelDoesNotExist)
RTI_EXCEPTION(SynchronizationPointLabelNotAnnounced)
RTI_EXCEPTION(TimeConstrainedAlreadyEnabled)
RTI_EXCEPTION(TimeConstrainedIsNotEnabled)
RTI_EXCEPTION(TimeRegulationAlreadyEnabled)
RTI_EXCEPTION(TimeRegulationIsNotEnabled)
RTI_EXCEPTION(UnableToPerformSave)
RTI_EXCEPTION(UnknownName)
RTI_EXCEPTION(UnsupportedCallbackModel)
RTI_EXCEPTION(InternalError)
#undef RTI_EXCEPTION

} // namespace SintolRTI

#endif
