//
// Created by Kamaldeep Tumkur on 28/08/20.
//

// TODO: COMPLETE THE CONSTRAINT DEFINITIONS.
#ifndef DASHIF_CONFORMANCE_CONFORMANCECONSTRAINTS_H
#define DASHIF_CONFORMANCE_CONFORMANCECONSTRAINTS_H

#include "ConformanceErrorLevels.h"
#include <iostream>

namespace conformance::constraints {

    // for the scheme urn:mpeg:dash:role:2011
    enum MPDRoleDescriptorType : std::size_t {
        CAPTION = 0,
        SUBTITLE,
        MAIN,
        ALTERNATE,
        SUPPLEMENTARY,
        SIGN,
        EMERGENCY,
        DUB
    };

    // for the scheme urn:mpeg:dash:role:2011
    enum MPDAccessibilityDescriptorType : std::size_t {
        DESCRIPTION = 0,
        ENHANCED_AUDIO_INTELLIGIBILITY
    };

    enum MPDAdaptationSetCodecType : std::size_t {
        ID_264 = 264,
        ID_265 = 265
    };

    // Supplemental properties to be recognized by
    // the DASH-IF Clients for enhanced operations.
    enum MPDSupplementalPropertyType : std::size_t {
        ADAPTATION_SET_SWITCHING = 0,
        TRICK_MODE,
        PERIOD_CONTINUITY,
        PERIOD_CONNECTIVITY
    };

    const std::size_t STR_SHORT_DESCRIPTION_LENGTH = 64;
    const std::size_t STR_DETAILED_DESCRIPTION_LENGTH = 256;

    // MPD profile description strings.
    const std::string MPD_PROFILE_STATIC = "static";
    const std::string MPD_PROFILE_DYNAMIC = "dynamic";

    // Live and on-demand profile types.
    const std::string MPD_PROFILE_LIVE_ROLE_SCHEME = "urn:mpeg:dash:profile:isoff-live:2011";
    const std::string MPD_PROFLE_ONDEMAND_ROLE_SCHEME = "urn:mpeg:dash:profile:isoff-ondemand:2011";
    const std::string MPD_ADAPTATION_SET_SWITCHING_ROLE_SCHEME = "urn:mpeg:dash:adaptation-set-switching:2016";

    // Main and alternative content.
    const std::string MPD_ROLE_SCHEME = "urn:mpeg:dash:role:2011";
    const std::string MPD_ROLE_DESC_SCHEME_MAIN = "main";
    const std::string MPD_ROLE_DESC_SCHEME_ALTERNATIVE = "alternative";

    // Caption and sub-title accessibility descriptors.
    const std::string MPD_ACCESSIBILITY_DESCRIPTOR_EAI = "enhanced-audio-intelligibility";

    const std::string MPD_CEA608_ROLE_SCHEME = "urn:scte:dash:cc:cea-608-2015";

    // Audio properties: channel config
    const std::string MPD_AUDIO_CHANNEL_CONFIG_ROLE_SCHEME = "urn:mpeg:dash:23003:3:audio_channel_configuration:2011";
    const std::string MPD_AUDIO_CHANNEL_CICP_ROLE_SCHEME = "urn:mpeg:mpegB:cicp:ChannelConfiguration";
    const std::string DOLBY_AC3_AUDIO_ROLE_SCHEME = "tag:dolby.com,2014:dash:audio_channel_configuration:2011";

    // Max version limit for constraint version.
    const std::string MAX_CONSTRAINT_VERSION = "4.3";

    // Reasonable values for segment durations are between 1 second and 10 seconds.
    // Create strings for entity vals and use the datatypes for reading from the std::pairs later when setting
    // the expected and observed entity vals.
    const std::string MAX_IOP_SEGMENT_DURATION = "10";


    enum ConstraintTypes : std::size_t {
        ContentGenerationConstraints = 0,
        MPDTimelineConstraints,
        StaticMPDConstraints,
        DynamicMPDConstraints,
        CMediaSegmentConstraints,
        VideoAdaptationSetConstraints,
        AudioAdaptationSetConstraints,
        TextAdaptationSetConstraints,
        ClockConstraints, // Packager may drop content for slow timer and insert padding for fast timer.
        MPDUpdateConstraints,
        EndOfLiveConstraints,
        CaptioningMediaConstraints,
        EncryptedMediaConstraints,
        KeyServerConstraints,
        VersionsConstraints,
        HTTPSDownloadConstraints,
        DVBDASHConstraints,
        AkamaiCDNTokenConstraints // Do tokens ever apply to content with other forms of more conventional modern security?
    };

    // Consider segregating the AND and OR and removing the >= and <= as individual operators.
    enum ConstraintOperator : std::int16_t {
        EQUALS = 0,
        GREATER_THAN,
        GREATER_THAN_EQUALS,
        LESS_THAN,
        LESS_THAN_EQUALS,
        BELONGS_TO,
        PRESENT,
        AND_OPERATOR,
        OR_OPERATOR
    };

    enum ConstraintDefEvalStatus : std::int16_t {
        SUCCESS = 0,
        CONDITIONAL_SUCCESS = 1,
        FAILURE = 2,
    };

    enum ConstraintVersions : std::int16_t {
        CLIENT_VERSION = 0,
        IOP_VERSION,
        IOP_ATSC3_VERSION,
        TOKEN_ACCESS_VERSION
        //LIVE_INGEST_VERSION, // Do we ever want a conformance check for ingest constraints? Only client-side checks for now.
    };

    ////////////////////////////////////////////////////////
    // Entity class definition.
    ////////////////////////////////////////////////////////
    //using namespace std;
    class ConstraintEntity {
    private:
        const std::string entityname_;
        const std::string entityID_;
        const std::string entitydesc_;
        std::string entitydatatype_;
        std::list<ConstraintEntity*> *celist = new std::list<ConstraintEntity*>();
        std::map<std::size_t, std::list<ConstraintEntity*>> *subentities_;

        // Make the ConstraintDefinition class a friend class maybe?

    public:
        ConstraintEntity(std::string entityname, std::string entityid, std::string entitydesc, std::string entitydatatype) :
                entityname_(entityname), entitydesc_(entitydesc), entitydatatype_(entitydatatype) {

            std::list<ConstraintEntity*> celist = {};

            // TODO: List subentities. Add/append logic pending.
            //subentities_->insert_or_assign(new std::pair<std::size_t, std::list<ConstraintEntity*>>(conformance::exception::hashnum(entityname), celist));
        };

        const std::string entityName() { return entityname_; }

        const std::string entityID() { return entityID_; }

        const std::string entityDesc() { return entitydesc_; }

        const std::string entityDatatype() { return entitydatatype_; }

        std::map<std::size_t, std::list<ConstraintEntity*>> *listSubEntities() { return subentities_; }

        std::size_t addChildEntityToEntity(ConstraintEntity &);

        ~ConstraintEntity() = default;
    };

    ////////////////////////////////////////////////////////
    // Constraint class definition.
    ////////////////////////////////////////////////////////
    using namespace conformance::exception;

    class ConstraintDefinition {

    private:
        const std::string constraintname_;
        std::string constraintdesc_;

        // Enforcement from error levels: like MUST, SHOULD etc.
        ConstraintEntity *entity_;
        ConformanceEnforcementTypes enforcement_;
        ConstraintOperator coperator_;

        // std::map<entity ID, std::map<expected entity Val, expected entity Type string form>>
        std::map<std::string, std::pair<std::string, const std::string>> *expectedConstraintValAndDatatypeMap_ =
                new std::map<std::string, std::pair<std::string, const std::string>>();
        std::map<std::string, std::pair<std::string, const std::string>> *observedConstraintValAndDatatypeMap_ =
                new std::map<std::string, std::pair<std::string, const std::string>>();

        std::string  expectedConstraintVal_;
        std::string observedConstraintVal_;

        ConstraintDefEvalStatus defStatus_;
        ConstraintDefEvalStatus valForCombinatorialAndDefinition(ConstraintDefEvalStatus result1, ConstraintDefEvalStatus result2);
        ConstraintDefEvalStatus valForCombinatorialOrDefinition(ConstraintDefEvalStatus result1, ConstraintDefEvalStatus result2);

        // Define the conditional eval status return.
        ConstraintDefEvalStatus valForCombinatorialConditionalDefinition(ConstraintDefEvalStatus result1, ConstraintDefEvalStatus result2);

    public:
        ConstraintDefinition(std::string, std::string, ConstraintEntity &);

        std::string constraintName() {return constraintname_; }
        std::string constraintDescription() {return constraintdesc_; }

        ConstraintEntity* constraintEntityFromDefinition() {return entity_; }
        ConformanceEnforcementTypes constraintEnforcementFromDefinition() {return enforcement_; }
        ConstraintOperator constraintOperatorForEntityFromDefinition() {return coperator_; }
        ConstraintDefEvalStatus evaluateConformanceConstraintResult(std::pair<std::string, const std::string>&,
                                                                    std::pair<std::string, const std::string>&, ConstraintOperator);
        ConstraintDefEvalStatus constraintDefEvalStatus() {return defStatus_; }



        void setConstraintDescription (std::string description) {
            constraintdesc_ = std::move(description);
        }

        ConstraintDefEvalStatus operator&(ConstraintDefinition *cdef) {
            // Does cdef and the current definition always have the same entity?
            // Let's assume for now.
            ConstraintEntity *mainentity = this->constraintEntityFromDefinition();
            ConstraintEntity *cdefentity = cdef->constraintEntityFromDefinition();

            if (mainentity != cdefentity) {
                return ConstraintDefEvalStatus::FAILURE;
            }

            ConstraintDefEvalStatus mainresult = this->constraintDefEvalStatus();
            ConstraintDefEvalStatus cdefresult = cdef->constraintDefEvalStatus();
            ConstraintDefEvalStatus result = valForCombinatorialAndDefinition(mainresult, cdefresult);

            return result;
        }

        ConstraintDefEvalStatus operator||(ConstraintDefinition *cdef) {
            // Does cdef and the current definition always have the same entity?
            // Let's assume for now.
            ConstraintEntity *mainentity = this->constraintEntityFromDefinition();
            ConstraintEntity *cdefentity = cdef->constraintEntityFromDefinition();

            if (mainentity != cdefentity) {
                return ConstraintDefEvalStatus::FAILURE;
            }

            ConstraintDefEvalStatus mainresult = this->constraintDefEvalStatus();
            ConstraintDefEvalStatus cdefresult = cdef->constraintDefEvalStatus();
            ConstraintDefEvalStatus result = valForCombinatorialOrDefinition(mainresult, cdefresult);

            return result;
        }

        ConstraintDefEvalStatus operator|(ConstraintDefinition *cdef) {
            // Operator for conditional definition status check.
            // Does cdef and the current definition always have the same entity?
            // Let's assume for now.

            ConstraintDefEvalStatus mainresult = this->constraintDefEvalStatus();
            ConstraintDefEvalStatus cdefresult = cdef->constraintDefEvalStatus();
            ConstraintDefEvalStatus result = valForCombinatorialConditionalDefinition(mainresult, cdefresult);

            return result;
        }

        void setConstraintEnforcementForDefinition(ConformanceEnforcementTypes cetype) {
            enforcement_ = std::move(cetype);
        }

        void setConstraintOperatorForEntity(ConstraintOperator coperator) {
            coperator_ = std::move(coperator);
        }

        void setExpectedConstraintEntityVal(ConstraintEntity& ce, std::string ceval);

        void setObservedConstraintEntityVal(ConstraintEntity& ce, std::string ceval);

        std::string constructDescriptionForConformanceConstraint(ConstraintEntity& );

        void setConstraintDefEvalStatus(ConstraintDefEvalStatus status) {defStatus_ = status; }

        //ConstraintDefEvalStatus findStatusForDefinition() const;

        ~ConstraintDefinition() {};

    };

    ////////////////////////////////////////////////////////
    // Conformance constraint class.
    ////////////////////////////////////////////////////////

    static bool integralTypeCheck(std::string val);
    static bool floatTypeCheck(std::string val);
    static bool containerTypeCheck(std::string val);

    static ConstraintDefEvalStatus compareValues(std::string expectedVal, std::string observedVal,
                                                 std::string valuetype, ConstraintOperator _op);

    class ConformanceConstraint {
    private:
        std::string constraint_short_desc_;
        std::string constraint_detailed_desc_;
        ConstraintTypes cttype_;
        std::list<ConstraintEntity*> *allConstraints_ = new std::list<ConstraintEntity*>();

        // Version? Does this correspond to the IOP version?
        std::size_t constraint_version_ = ConstraintVersions::IOP_VERSION;

        // A conformance constraint may have more than one constraint definition.
        std::map<ConstraintTypes &, ConstraintDefinition &> *constraintDefinitions_;

        // Initialize the constraints mentioned in the constraint types.
        void initializeConstraints();

    public:
        ConformanceConstraint(ConstraintTypes cttype);

        ConstraintTypes ConformanceConstraintType() {
            return cttype_;
        }

        std::map<ConstraintVersions, std::list<std::string>> *constraintVersions =
                new std::map<ConstraintVersions, std::list<std::string>>();

        const std::string &constraintShortDescription() { return constraint_short_desc_; }

        const std::string &constraintDetailedDescription() { return constraint_detailed_desc_; }

        void constraintShortDescription(const std::string &desc);

        void constraintDetailedDescription(const std::string &desc);

        // TODO: Re-implement the destructor.
        ~ConformanceConstraint() {};
    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCECONSTRAINTS_H
