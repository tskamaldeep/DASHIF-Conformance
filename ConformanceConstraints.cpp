//
// Created by Kamaldeep Tumkur on 28/08/20.
//

#include <type_traits>
#include <string>
#include <cstdlib>
#include "ConformanceConstraints.h"

using namespace std;
using namespace conformance::constraints;
using namespace conformance::exception;

ConformanceConstraint::ConformanceConstraint(ConstraintTypes cttype) : cttype_(cttype), constraint_short_desc_(""),
                                                                       constraint_detailed_desc_("") {

    // Define a few stack vars.
    std::string entityName;
    std::string entityDesc;
//    const char *entityType;

    // TODO: Implement the switch handling.
    switch (cttype) {
        case ConstraintTypes::ContentGenerationConstraints:
        case ConstraintTypes::MPDTimelineConstraints:
        case ConstraintTypes::StaticMPDConstraints: {
            ConstraintEntity mpdtype = ConstraintEntity("mpdtype", "MPD@type", "Dynamic or static type",
                                                        std::string(typeid(std::string).name()));
            ConstraintEntity ast = ConstraintEntity("availabilityStartTime", "MPD@availabilityStartTime",
                                                    "Time at which the advertised media is available to start playback",
                                                    std::string(typeid(std::size_t).name()));
            ConstraintEntity mediapresDuration = ConstraintEntity("mediaPresentationDuration",
                                                                  "MPD@mediaPresentationDuration",
                                                                  "Duration of the media entity reserved for playback",
                                                                  std::string(typeid(std::size_t).name()));
            ConstraintEntity availabilityTimeOffset = ConstraintEntity("availabilityTimeOffset",
                                                                       "MPD@availabilityTimeOffset",
                                                                       "Offset in available time of the representation",
                                                                       std::string(typeid(std::string).name()));
            ConstraintEntity minBufferTime = ConstraintEntity("minBufferTime", "MPD@minBufferTime",
                                                              "How long to buffer the media",
                                                              std::string(typeid(std::size_t).name()));
            ConstraintEntity mpdprofiles = ConstraintEntity("mpdprofiles", "MPD@profiles",
                                                            "Inclusion of the mpd profile type",
                                                            std::string(typeid(std::string).name()));
            ConstraintEntity segmentAligned = ConstraintEntity("segmentAlignment", "@segmentAlignment",
                                                               "Is the segment aligned across adaptation sets",
                                                               std::string(typeid(bool).name()));
            ConstraintEntity subsegmentAligned = ConstraintEntity("subSegmentAlignment", "@subSegmentAlignment",
                                                                  "Is the subsegment boundary aligned across adaptation sets",
                                                                  std::string(typeid(bool).name()));

            // Add all constraints.
            allConstraints_->push_back(&mpdtype);
            allConstraints_->push_back(&ast);
            allConstraints_->push_back(&mediapresDuration);
            allConstraints_->push_back(&availabilityTimeOffset);
            allConstraints_->push_back(&minBufferTime);
            allConstraints_->push_back(&mpdprofiles);
            allConstraints_->push_back(&segmentAligned);
            allConstraints_->push_back(&subsegmentAligned);

            break;
        }

        case ConstraintTypes::DynamicMPDConstraints: {
            ConstraintEntity tsb = ConstraintEntity("timeShiftBufferDepth", "MPD@timeShiftBufferDepth",
                                                    "Suitable time shift for content rendering at the live edge",
                                                    std::string(typeid(std::string).name()));

            ConstraintEntity minUpdatePeriod = ConstraintEntity("minimumUpdatePeriod", "MPD@minimumUpdatePeriod",
                                                                "Service controlled MPD refresh polling for updated segments",
                                                                std::string(typeid(std::string).name()));

            allConstraints_->push_back(&tsb);
            allConstraints_->push_back(&minUpdatePeriod);
            break;
        }

        case ConstraintTypes::SegmentTemplateConstraints: {
            ConstraintEntity segmedia = ConstraintEntity("media", "SegmentTemplate@media", "The template for a media segment assigned "
                                                                                           "to a representation", std::string(typeid(std::string).name()));

            ConstraintEntity segstartnum = ConstraintEntity("startnumber", "SegmentTemplate@startNumber", "Number of the first segment assigned to a representation",
                                                            std::string(typeid(std::size_t).name()));

            ConstraintEntity segtimescale = ConstraintEntity("timescale", "SegmentTemplate@timeScale",
                                                             "time scale of the representation", std::string(typeid(std::string).name()));

            ConstraintEntity segduration = ConstraintEntity("segduration", "SegmentTemplate@duration", "Duration of each segment in units of time",
                                                            std::string(typeid(std::size_t).name()));

            // What is the data type of a segment timeline?
            ConstraintEntity segTimeline = ConstraintEntity("segTimeline", "SegmentTemplate@SegmentTimeline",
                                                            "Indicator of a segment timeline", std::string(typeid(std::string).name()));


            allConstraints_->push_back(&segmedia);
            allConstraints_->push_back(&segstartnum);
            allConstraints_->push_back(&segtimescale);
            allConstraints_->push_back(&segduration);
            allConstraints_->push_back(&segTimeline);
            break;

        }

        case ConstraintTypes::CMediaSegmentConstraints:
            // Define the constraint around segment formats.
            // Comply with ISO/IEC 23009-1, section 7.3
            // 1. 'moof' box precedes the 'sidx' and the 'ssix' boxes
            break;
        case ConstraintTypes::VideoAdaptationSetConstraints: {
            // 1. maxWidth
            // 2. maxHeight
            // 3. maxFrameRate

            ConstraintEntity mimeType = ConstraintEntity("mimeType", "@mimeType",
                                                         "Supported mimetypes for the video adaptation set",
                                                         std::string(typeid(std::string).name()));
            ConstraintEntity vMaxWidth = ConstraintEntity("vMaxWidth", "@maxWidth",
                                                          "Maximum frame width across representations",
                                                          std::string(typeid(std::size_t).name()));
            ConstraintEntity vMaxHeight = ConstraintEntity("vMaxHeight", "@maxHeight",
                                                           "Maximum frame height across representations",
                                                           std::string(typeid(std::size_t).name()));
            ConstraintEntity vMinWidth = ConstraintEntity("vMinWidth", "@minWidth",
                                                          "Minimum frame width across representations",
                                                          std::string(typeid(std::size_t).name()));
            ConstraintEntity vMinHeight = ConstraintEntity("vMinHeight", "@minHeight",
                                                           "Minimum frame height across representations",
                                                           std::string(typeid(std::size_t).name()));
            ConstraintEntity vMaxFrameRate = ConstraintEntity("vMaxFrameRate", "@maxFrameRate",
                                                              "Max frame rate across representations",
                                                              std::string(typeid(std::size_t).name()));
            ConstraintEntity videoCodecs = ConstraintEntity("videoCodecs", "@codecs",
                                                            "Supported codecs in the video adaptation set",
                                                            std::string(typeid(std::string).name()));
            ConstraintEntity par = ConstraintEntity("par", "@par", "Pixel Aspect Ratio constraint",
                                                    std::string(typeid(double).name()));
            ConstraintEntity sar = ConstraintEntity("sar", "@sar", "Screen Aspect Ratio constraint",
                                                    std::string(typeid(double).name()));
            ConstraintEntity scanType = ConstraintEntity("scanType", "@scanType", "Image scan ordering or type",
                                                         std::string(typeid(std::string).name()));

            allConstraints_->push_back(&mimeType);
            allConstraints_->push_back(&vMaxWidth);
            allConstraints_->push_back(&vMaxHeight);
            allConstraints_->push_back(&vMinWidth);
            allConstraints_->push_back(&vMinHeight);
            allConstraints_->push_back(&vMaxFrameRate);
            allConstraints_->push_back(&videoCodecs);
            allConstraints_->push_back(&par);
            allConstraints_->push_back(&sar);
            allConstraints_->push_back(&scanType);
            break;
        }

        case ConstraintTypes::AudioAdaptationSetConstraints: {
            ConstraintEntity audioSamplingRate = ConstraintEntity("audioSamplingRate", "@audioSamplingRate",
                                                                  "Maximum Audio Sampling rate of the rendition",
                                                                  std::string(typeid(std::size_t).name()));
            ConstraintEntity audioCodecs = ConstraintEntity("audioCodecs", "@codecs", "Supported audio codecs",
                                                            std::string(typeid(std::string).name()));

            ConstraintEntity lang = ConstraintEntity("lang", "@lang",
                                                     "Dominant Language attribute associated with the adaptation set",
                                                     std::string(typeid(std::string).name()));

            allConstraints_->push_back(&audioCodecs);
            allConstraints_->push_back(&audioSamplingRate);
            allConstraints_->push_back(&lang);
            break;
        }

        case ConstraintTypes::TextAdaptationSetConstraints:
        case ConstraintTypes::ClockConstraints:
        case ConstraintTypes::MPDUpdateConstraints:
        case ConstraintTypes::EndOfLiveConstraints:
        case ConstraintTypes::CaptioningMediaConstraints:
        case ConstraintTypes::EncryptedMediaConstraints:
        case ConstraintTypes::KeyServerConstraints:
        case ConstraintTypes::HTTPSDownloadConstraints:
        case ConstraintTypes::DVBDASHConstraints: {
            // TODO: Add DVB constraints support
            break;
        }
        case ConstraintTypes::VersionsConstraints: {
            // Define a custom constraint for version restrictions.
            ConstraintEntity version2Constraint = ConstraintEntity("version2Constraint", "IOP@v2",
                                                                   "IOP constraints for v2 vs. previous versions.",
                                                                   std::string(typeid(std::string).name()));
            ConstraintEntity version3Constraint = ConstraintEntity("version3Constraint", "IOP@v3",
                                                                   "IOP constraints for v3 vs. previous versions",
                                                                   std::string(typeid(std::string).name()));

            // Skipping v3.1 - v3.3 for now, except for inclusions/exclusions.
            ConstraintEntity version4_0_Constraint = ConstraintEntity("version4Constraint", "IOP@v4",
                                                                      "IOP constraints for v4.0 vs the previous versions",
                                                                      std::string(typeid(std::string).name()));
            ConstraintEntity version4_1_Constraint = ConstraintEntity("version41Constraint", "IOP@v4_1",
                                                                      "IOP constraints for v4.1 vs the previous versions",
                                                                      std::string(typeid(std::string).name()));
            ConstraintEntity version4_2_Constraint = ConstraintEntity("version42Constraint", "IOP@v4_2",
                                                                      "IOP constraints for v4.2 vs the previous versions",
                                                                      std::string(typeid(std::string).name()));
            ConstraintEntity version4_3_Constraint = ConstraintEntity("version43Constraint", "IOP@v4_3",
                                                                      "IOP constraints for v4.3 vs the previous versions",
                                                                      std::string(typeid(std::string).name()));

            allConstraints_->push_back(&version2Constraint);
            allConstraints_->push_back(&version3Constraint);
            allConstraints_->push_back(&version4_0_Constraint);
            allConstraints_->push_back(&version4_1_Constraint);
            allConstraints_->push_back(&version4_2_Constraint);
            allConstraints_->push_back(&version4_3_Constraint);

            break;
        }
        case ConstraintTypes::AkamaiCDNTokenConstraints:
            // Outline any definitions.
            break;
    }

    // Now initialize the constraints through each of the entity definitions.
    // Initialize the constraints first.
    this->initializeConstraints();
}

void ConformanceConstraint::initializeConstraints() {
    /////////////////////////////////////////////////
    // Define and initialize all constraints.
    /////////////////////////////////////////////////

    // Set the constraint versions map first.
    // Add versions for client and IOP versions first, ATSC later.
    std::list<std::string> clientversions = {
            "1.0", "2.0"
    };

    std::list<std::string> iopversions = {
            "1.0", "2.0", "2.1", "2.2", "3.0", "4.0", "4.1", "4.2", "4.3"
    };

    // TODO: Add in the ATSC, Token, CPIX and related versioning information in related data structures.

    this->constraintVersions->insert(std::make_pair(ConstraintVersions::CLIENT_VERSION, clientversions));
    this->constraintVersions->insert(std::make_pair(ConstraintVersions::IOP_VERSION, iopversions));

    // Go through the constraint types and initialize each constraint with the definition
    // for the corresponding entity.
    // A constraint could have more than one definition.

    ConstraintDefinition *astPresenceDefn;
    ConstraintDefinition *mpdStaticTypeDefn;
    ConstraintDefinition *mpdDynamicTypeDefn;
    ConstraintDefinition *mpdProfilesLiveDefn;
    ConstraintDefinition *mpdProfilesOndemandDefn;
    ConstraintDefinition *mediaPresDurationDefn;
    ConstraintDefinition *periodStartDefn;
    ConstraintDefinition *atoffsetPresenceDefn;
    ConstraintDefinition *minBufferTimeDefn;
    ConstraintDefinition *minBufferTimeLimitDefn;
    ConstraintDefinition *liveSegmentAlignedDefn;
    ConstraintDefinition *ondemandSegmentAlignedDefn;
    ConstraintDefinition *staticTSBAbsenceDefn;
    ConstraintDefinition *minUpdatePeriodDefn;
    ConstraintDefinition *minUpdatePeriodLiveDefn;
    ConstraintDefinition *videoMimeTypeDefn;
    ConstraintDefinition *audioMimeTypeDefn;
    ConstraintDefinition *subtitleMimeTypeDefn1;
    ConstraintDefinition *subtitleMimeTypeDefn2;
    ConstraintDefinition *subtitleMimeTypeDefn;
    ConstraintDefinition *widthTagPresenceDefn;
    ConstraintDefinition *maxWidthTagPresenceDefn;
    ConstraintDefinition *widthDefinition;
    ConstraintDefinition *maxWidthLimitDefn;
    ConstraintDefinition *minWidthPresenceDefn;
    ConstraintDefinition *minWidthLimitDefn;
    ConstraintDefinition *heightPresenceDefn;
    ConstraintDefinition *maxHeightLimitDefn;
    ConstraintDefinition *minHeightPresenceDefn;
    ConstraintDefinition *minHeightLimitDefn;
    ConstraintDefinition *vFrameRateDefn;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Initial definitions.
    std::string conformanceEntityID = "";
    ConformanceEnforcementTypes enforcementType = conformance::exception::ConformanceEnforcementTypes::MUST;
    ConstraintOperator operatorType = conformance::constraints::ConstraintOperator::PRESENT;
    std::string conditionalFormat = "If %s is ";
    // Entity ID + operator + value
    ////////////////////////////////////////////////////////////////////////////////////////

    std::list<ConstraintEntity *> *allconstraints = allConstraints_;
    std::list<ConstraintEntity *>::iterator *ctiter = new std::list<ConstraintEntity *>::iterator();
    for (*ctiter = allconstraints->begin(); *ctiter != allconstraints->end(); ctiter++) {
        ConstraintEntity iterEntity = reinterpret_cast<const ConstraintEntity &>(ctiter);

        if (iterEntity.entityName().compare("mpdtype") == 0) {
            // Initialize all the definitions of this constraint corresponding to this entity.
            // Build all definitions corresponding to the constraint associate with the 'mpdType' entity.

            // Constraint #1: ast (Availability Start Time) is optional for "static" MPDs and mandatory for "dynamic" MPDs.
            // Default description below. Use the setter for a more accurate constructed description.
            // This is a dependency type constraint. Probably set a FLAG and check in both entities.
            // Alternate way of constructing the ConstraintDefinition.

            // Definition => Entity + EnforcementType + ConstraintType + Conditional
            // OR
            // Conditional + Entity + EnforcementType + ConstraintType.

            conformanceEntityID = iterEntity.entityID();
            std::string conformanceEntityVal = MPD_PROFILE_DYNAMIC;
            enforcementType = conformance::exception::ConformanceEnforcementTypes::MUST;
            operatorType = conformance::constraints::ConstraintOperator::PRESENT;
            const char *cformat = conditionalFormat.append(
                    std::string(typeid(conformanceEntityVal).name()) + ", ").c_str();
            const std::string astpresenceDesc = "MPD@availabilityStartTime MUST be present in a dynamic type manifest.";

            // Comparison =>  observed value (and datatype) vs. expected value (and datatype).
            // If MPD@MPDType is dynamic, MPD@availabilityStartTime MUST be PRESENT.
            // Any conditional for the constraint definition to apply.
            char mpdtypeConditionalFormat[STR_DETAILED_DESCRIPTION_LENGTH];
            sprintf(mpdtypeConditionalFormat, cformat, conformanceEntityID.c_str(), conformanceEntityVal.c_str());

            astPresenceDefn = new ConstraintDefinition("availabilityStartTimePresence",
                                                       astpresenceDesc, iterEntity);
            astPresenceDefn->setConstraintOperatorForEntity(operatorType);
            astPresenceDefn->setConstraintEnforcementForDefinition(enforcementType);

            ///////////////////////////////////////////////////////////
            // Constraint #2: type can be either "static" OR "dynamic".
            // Add an OR operator for the evaluation.
            ///////////////////////////////////////////////////////////
            conformanceEntityID = iterEntity.entityID();
            enforcementType = conformance::exception::ConformanceEnforcementTypes::MUST;
            operatorType = conformance::constraints::ConstraintOperator::EQUALS;
            const std::string mpdStaticTypeDesc = "MPD@type value MUST be static";
            const std::string mpdDynamicTypeDesc = "MPD@type value MUST be dynamic";

            // Define as two separate definitions, conjoined by the OR operator.
            mpdStaticTypeDefn = new ConstraintDefinition("MPD@type",
                                                         mpdStaticTypeDesc,
                                                         iterEntity);

            mpdStaticTypeDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::MUST);
            mpdStaticTypeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            mpdStaticTypeDefn->setExpectedConstraintEntityVal(iterEntity, "static");

            mpdDynamicTypeDefn = new ConstraintDefinition("MPD@type",
                                                          mpdDynamicTypeDesc,
                                                          iterEntity);

            mpdDynamicTypeDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::MUST);
            mpdDynamicTypeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            mpdDynamicTypeDefn->setExpectedConstraintEntityVal(iterEntity, "dynamic");

            // Two definitions need to be combined with an OR operator during evaluation.

        } else if (iterEntity.entityName() == "ast") {

        } else if (iterEntity.entityName().compare("mediapresDuration") == 0) {
            //////////////////////////////////////////////////////////////////////////////
            // Constraint #3: The MPD@mediaPresentationDuration entity SHALL be PRESENT OR
            // Period@Start is PRESENT"
            //////////////////////////////////////////////////////////////////////////////
            const std::string mediaPresDurationDesc = "The MPD@mediaPresentationDuration entity SHALL be PRESENT";
            const std::string periodStartDesc = "The Period@Start entity SHALL be PRESENT";

            mediaPresDurationDefn = new ConstraintDefinition("MPD@mediaPresentationDuration",
                                                             mediaPresDurationDesc, iterEntity);
            mediaPresDurationDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            mediaPresDurationDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::PRESENT);
            mediaPresDurationDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            periodStartDefn = new ConstraintDefinition("Period@start", periodStartDesc, iterEntity);
            periodStartDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            periodStartDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);
            periodStartDefn->setExpectedConstraintEntityVal(iterEntity, "true");
            // Two definitions need to be combined with an OR operator during evaluation.

        } else if (iterEntity.entityName().compare("availabilityTimeOffset") == 0) {
            /////////////////////////////////////////////////////////////////////////////////
            // Initialize all the definitions of this constraint corresponding to this entity.
            // Constraint #4: AvailabilityTimeOffset SHOULD NOT be PRESENT in static manifests
            /////////////////////////////////////////////////////////////////////////////////
            const std::string atoffsetPresenceDesc = "AvailabilityTimeOffset SHOULD NOT be PRESENT in static manifests";
            atoffsetPresenceDefn = new ConstraintDefinition("@availabilityTimeOffset", atoffsetPresenceDesc,
                                                            iterEntity);
            atoffsetPresenceDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHOULD_NOT);
            atoffsetPresenceDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);
            atoffsetPresenceDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            // Check for the conditionality of the definition.
            // ConstraintDefEvalStatus atoffsetStatus = mpdStaticTypeDefn->operator|(atoffsetPresenceDefn);

        } else if (iterEntity.entityName().compare("minBufferTime") == 0) {
            //////////////////////////////////////////////////////////////////////////////
            // Constraint #5: The minimum buffer time SHOULD be set to the maximum GOP size
            // Constraint #6: The minimumBufferTime MAY be set to a smaller value than the
            // segment duration AND not a higher value
            //////////////////////////////////////////////////////////////////////////////
            const std::string minBufferTimeDesc = "The minimum buffer time SHOULD be set to the maximum GOP size";
            minBufferTimeDefn = new ConstraintDefinition("MPD@minBufferTime",
                                                         minBufferTimeDesc, iterEntity);

            minBufferTimeDefn->setConstraintEnforcementForDefinition(conformance::exception::ConformanceEnforcementTypes::SHOULD);
            minBufferTimeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);

            // quite often is identical to the maximum segment duration.
            minBufferTimeDefn->setExpectedConstraintEntityVal(iterEntity, MAX_IOP_SEGMENT_DURATION);

            const std::string minBufferTimeLimitDesc = "The minimumBufferTime MAY be set to a smaller value than the segment duration and not a higher value";
            minBufferTimeLimitDefn = new ConstraintDefinition("minBufferTimeLimitDefinition", minBufferTimeLimitDesc, iterEntity);

            minBufferTimeDefn->setConstraintEnforcementForDefinition(conformance::exception::ConformanceEnforcementTypes::MAY);
            minBufferTimeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::LESS_THAN);
            minBufferTimeDefn->setExpectedConstraintEntityVal(iterEntity, MAX_IOP_SEGMENT_DURATION);

        } else if (iterEntity.entityName().compare("mpdprofiles") == 0) {

        } else if (iterEntity.entityName().compare("segmentAligned") == 0) {
            const std::string mpdProfilesLiveDesc = "MPD@Profiles EQUALS urn:mpeg:dash:profile:isoff-live:2011";
            const std::string liveSegmentAlignedDesc = "@segmentAlignment is set to TRUE for all adaptation sets.";

            mpdProfilesLiveDefn = new ConstraintDefinition("MPD@Profiles", mpdProfilesLiveDesc, iterEntity);
            mpdProfilesLiveDefn->setConstraintEnforcementForDefinition(conformance::exception::ConformanceEnforcementTypes::MUST);
            mpdProfilesLiveDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            mpdProfilesLiveDefn->setExpectedConstraintEntityVal(iterEntity, MPD_PROFILE_LIVE_ROLE_SCHEME);

            liveSegmentAlignedDefn = new ConstraintDefinition("liveSegmentAligned",
                                                              liveSegmentAlignedDesc, iterEntity);

            // live segment aligned definition setters.
            liveSegmentAlignedDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            liveSegmentAlignedDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::AND_OPERATOR);
            liveSegmentAlignedDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            // Set the conditional in place to validate for the alignment for live profiles.
           //  ConstraintDefEvalStatus segAlignedStatus = mpdProfilesLiveDefn->operator|(liveSegmentAlignedDefn);

        } else if (iterEntity.entityName().compare("subsegmentAligned") == 0) {

            const std::string mpdProfilesOndemandDesc = "MPD@Profiles EQUALS urn:mpeg:dash:profile:isoff-ondemand:2011";
            const std::string ondemandSegmentAlignedDesc = "@subSegmentAlignment is set to TRUE for all adaptation sets.";

            mpdProfilesOndemandDefn->setConstraintEnforcementForDefinition(conformance::exception::ConformanceEnforcementTypes::MUST);
            mpdProfilesOndemandDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            mpdProfilesOndemandDefn->setExpectedConstraintEntityVal(iterEntity, MPD_PROFLE_ONDEMAND_ROLE_SCHEME);
            ondemandSegmentAlignedDefn = new ConstraintDefinition("ondemandSegmentAligned",
                                                                  ondemandSegmentAlignedDesc,
                                                                  iterEntity);

            // ondemand segment aligned definition setters.
            ondemandSegmentAlignedDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            ondemandSegmentAlignedDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::AND_OPERATOR);
            ondemandSegmentAlignedDefn->setExpectedConstraintEntityVal(iterEntity, "true");

        } else if (iterEntity.entityName().compare("tsb") == 0) {
            const std::string staticTSBAbsenceDesc = "MPD@timeShiftBufferDepth SHOULD NOT be present if the MPD@type is static";
            staticTSBAbsenceDefn = new ConstraintDefinition("staticTimeShiftBufferDepth",
                                                            staticTSBAbsenceDesc, iterEntity);

            staticTSBAbsenceDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHOULD_NOT);
            staticTSBAbsenceDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);
            staticTSBAbsenceDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            // Set the constraint for a conditional check.
            // ConstraintDefEvalStatus staticTSBAbsenceCheck = mpdStaticTypeDefn->operator|(staticTSBAbsenceDefn);

        } else if (iterEntity.entityName().compare("minUpdatePeriod") == 0) {
            const std::string minUpdatePeriodDesc = "Minimum update period is NOT PRESENT in ondemand manifests";
            minUpdatePeriodDefn = new ConstraintDefinition("minimumUpdatePeriodDefinition",
                                                           minUpdatePeriodDesc,
                                                           iterEntity);

            minUpdatePeriodDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL_NOT);
            minUpdatePeriodDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);
            minUpdatePeriodDefn->setExpectedConstraintEntityVal(iterEntity, "0");

            const std::string minUpdatePeriodLiveDesc = "Minimum update period is PRESENT in live manifests";
            minUpdatePeriodLiveDefn = new ConstraintDefinition(
                    "minimumUpdatePeriodLiveDefinition",
                    minUpdatePeriodLiveDesc,
                    iterEntity);

            minUpdatePeriodLiveDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL_NOT);
            minUpdatePeriodLiveDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::PRESENT);
            minUpdatePeriodLiveDefn->setExpectedConstraintEntityVal(iterEntity, "0");

        } else if (iterEntity.entityName().compare("mimeType") == 0) {
            const std::string videoMimeType = "video/mp4";
            const std::string videoMimeTypeDesc = "@mimetype for a video adaptation set SHALL be set to video/mp4";
            videoMimeTypeDefn = new ConstraintDefinition("videoMimeTypeDefinition",
                                                         videoMimeTypeDesc, iterEntity);

            videoMimeTypeDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            videoMimeTypeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            videoMimeTypeDefn->setExpectedConstraintEntityVal(iterEntity, videoMimeType);

            const std::string audioMimeType = "audio/mp4";
            const std::string audioMimeTypeDesc = "@mimetype for an audio adaptation set SHALL be set to audio/mp4";
            audioMimeTypeDefn = new ConstraintDefinition("audioMimeTypeDefinition",
                                                         audioMimeTypeDesc, iterEntity);

            audioMimeTypeDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            audioMimeTypeDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            audioMimeTypeDefn->setExpectedConstraintEntityVal(iterEntity, audioMimeType);

            const std::string subtitleType1 = "application/mp4";
            const std::string subtitleType2 = "application/ttml+xml";
            const std::string subtitleMimeTypeDesc1 = "@mimetype for a subtitle adaptation set SHALL be set to application/mp4";
            const std::string subtitleMimeTypeDesc2 = "@mimetype for a subtitle adaptation set SHALL be set to application/ttml+xml";
            subtitleMimeTypeDefn1 = new ConstraintDefinition("subtitleMimeTypeDefn1",
                                                             subtitleMimeTypeDesc1, iterEntity);

            subtitleMimeTypeDefn1->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            subtitleMimeTypeDefn1->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            subtitleMimeTypeDefn1->setExpectedConstraintEntityVal(iterEntity, subtitleType1);

            subtitleMimeTypeDefn2 = new ConstraintDefinition("subtitleMimeTypeDefn2",
                                                             subtitleMimeTypeDesc2, iterEntity);
            subtitleMimeTypeDefn2->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            subtitleMimeTypeDefn2->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::EQUALS);
            subtitleMimeTypeDefn2->setExpectedConstraintEntityVal(iterEntity, subtitleType2);

            subtitleMimeTypeDefn = new ConstraintDefinition("subtitleMimeTypeDefn",
                                                            subtitleMimeTypeDesc1 + " AND " +
                                                            subtitleMimeTypeDesc2, iterEntity);
            subtitleMimeTypeDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            subtitleMimeTypeDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::AND_OPERATOR);
            // Should we set the expected val for the combinatorial result.
            subtitleMimeTypeDefn->setExpectedConstraintEntityVal(iterEntity, "0");

        } else if (iterEntity.entityName().compare("vMaxWidth") == 0) {
            const std::string widthTagForSameWidthDesc = "If all representations have the same width, the video adaptation set SHALL have the width tag PRESENT";
            widthTagPresenceDefn = new ConstraintDefinition("@width", widthTagForSameWidthDesc, iterEntity);

            widthTagPresenceDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            widthTagPresenceDefn->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);
            // Double check the val and type.
            widthTagPresenceDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            const std::string maxWidthTagPresentDesc = "If representations do not have the same width, the video adaptation tag SHALL have the maxWidth tag PRESENT";
            maxWidthTagPresenceDefn = new ConstraintDefinition("@maxWidth", maxWidthTagPresentDesc, iterEntity);
            maxWidthTagPresenceDefn->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            maxWidthTagPresenceDefn->setConstraintOperatorForEntity(
                    conformance::constraints::ConstraintOperator::PRESENT);
            // Double check the val and type.
            maxWidthTagPresenceDefn->setExpectedConstraintEntityVal(iterEntity, "true");

            widthDefinition = new ConstraintDefinition("widthconstraints",
                                                       widthTagForSameWidthDesc + " OR " + maxWidthTagPresentDesc,
                                                       iterEntity);
            widthDefinition->setConstraintEnforcementForDefinition(
                    conformance::exception::ConformanceEnforcementTypes::SHALL);
            widthDefinition->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::OR_OPERATOR);
            widthDefinition->setExpectedConstraintEntityVal(iterEntity, "true");

            const std::string maxWidthLimitDesc = "Max width value MAY exceed the largest value of any coded representation in an adaptation set";
            maxWidthLimitDefn = new ConstraintDefinition("maxWidthLimitDefinition", maxWidthLimitDesc, iterEntity);

            const std::string minWidthPresenceDesc = "Min width value SHOULD NOT be PRESENT";
            minWidthPresenceDefn = new ConstraintDefinition("minWidthPresenceDefn", minWidthPresenceDesc, iterEntity);

            const std::string minWidthLimitDesc = "Min width, if present, MAY be smaller than the smallest width in the adaptation set.";
            minWidthLimitDefn = new ConstraintDefinition("minWidthLimitDefinition", minWidthLimitDesc, iterEntity);

            // Define the height tag constraints.
        } else if (iterEntity.entityName().compare("vMaxHeight") == 0) {
            const std::string heightTagPresenceDesc = "A video adaptation set SHALL have the height tag for the same height in all representations OR the maxHeight tag if not the same height PRESENT.";
            heightPresenceDefn = new ConstraintDefinition("heightTagPresenceDefinition", heightTagPresenceDesc,
                                                          iterEntity);

            const std::string maxHeightLimitDesc = "Max height value MAY exceed the largest value of any coded representation in an adaptation set";
            maxHeightLimitDefn = new ConstraintDefinition("maxHeightLimitDefinition", maxHeightLimitDesc, iterEntity);

            const std::string minHeightPresenceDesc = "Min height value SHOULD NOT be PRESENT";
            minHeightPresenceDefn = new ConstraintDefinition("minHeightPresenceDefinition", minHeightPresenceDesc,
                                                             iterEntity);

            const std::string minHeightLimitDesc = "Min height, if present, MAY be smaller than the smallest height in the adaptation set.";
            minHeightLimitDefn = new ConstraintDefinition("minHeightLimitDefinition", minHeightLimitDesc, iterEntity);

        } else if (iterEntity.entityName().compare("vMaxFrameRate") == 0) {
            const std::string vMaxFrameRateDesc = "@framerate SHOULD be PRESENT in the mpd manifest if all representations "
                                                  "have the same framerate OR the maxFrameRate SHOULD be PRESENT.";
            vFrameRateDefn = new ConstraintDefinition("vMaxFrameRateDefinition", vMaxFrameRateDesc, iterEntity);
        } else if (iterEntity.entityName().compare("videoCodecs") == 0) {
        } else if (iterEntity.entityName().compare("sar") == 0) {

        }

        //////////////////////////////////////////////////////////
        // Re-align definitions with new outside the block declaration type.
        //////////////////////////////////////////////////////////
        else if (iterEntity.entityName().compare("par") == 0) {
            const std::string parTagPresenceDesc = "A video adaptation set SHALL have the par tag PRESENT";
            ConstraintDefinition *parPresenceDefn = new ConstraintDefinition("parTagPresenceDefinition",
                                                                             parTagPresenceDesc, iterEntity);

        } else if (iterEntity.entityName().compare("scanType") == 0) {
            const std::string scanTypePresenceDesc = "For a video adaptation set, scanType SHALL NOT be present.";
            ConstraintDefinition *scanTypePresenceDefn = new ConstraintDefinition("scanTypePresenceDefinition",
                                                                                  scanTypePresenceDesc, iterEntity);

            const std::string scanTypeValueDesc = "For a video adaptation set, scanType if present, SHALL be set to progressive";
            ConstraintDefinition *scanTypeValueDefn = new ConstraintDefinition("scanTypeValueDefinition",
                                                                               scanTypeValueDesc, iterEntity);

        } else if (iterEntity.entityName().compare("lang") == 0) {
            const std::string langPresenceDesc = "For an audio adaptation set, the lang attribute SHALL be PRESENT";
            ConstraintDefinition *langPresenceDefn = new ConstraintDefinition("langPresenceDefinition",
                                                                              langPresenceDesc, iterEntity);


        } else if (iterEntity.entityName().compare("audioSamplingRate") == 0) {
            const std::string audioSamplingRateDesc = "For an audio adaptation set, the audioSamplingRate SHALL be PRESENT";
            ConstraintDefinition *audioSamplingRateDefn = new ConstraintDefinition("audioSamplingRateDefinition",
                                                                                   audioSamplingRateDesc, iterEntity);

        } else if (iterEntity.entityName().compare("audioCodecs") == 0) {

        }
    }

    // Initialize the constraints/versions map.
    // Version 4.3 is the latest IOP version.
//    ConstraintDefinition *version2ConstraintDef = new ConstraintDefinition("version2", "version2", version2Constraint);
//    ConstraintDefinition *version3ConstraintDef = new ConstraintDefinition("version3", "version3", version3Constraint);
//    ConstraintDefinition *version4_0_ConstraintDef = new ConstraintDefinition("version4_0", "version4_0", version4_0_Constraint);
//    ConstraintDefinition *version4_1_ConstraintDef = new ConstraintDefinition("version4_1", "version4_1", version4_1_Constraint);
//    ConstraintDefinition *version4_2_ConstraintDef = new ConstraintDefinition("version4_2", "version4_2", version4_2_Constraint);
//    ConstraintDefinition *version4_3_ConstraintDef = new ConstraintDefinition("version4_3", "version4_3", version4_3_Constraint);

}

void ConstraintDefinition::setExpectedConstraintEntityVal(ConstraintEntity &ce, std::string ceval) {
    const std::string entitydatatype = ce.entityDatatype();
    const std::string entityid = ce.entityID();
    std::cout << "EntityDataType: " << entitydatatype;
    expectedConstraintVal_ = ceval;
    std::pair<std::string, const std::string> valtypepair = std::make_pair(expectedConstraintVal_, entitydatatype);
    expectedConstraintValAndDatatypeMap_->try_emplace(entityid, valtypepair);
}

void ConstraintDefinition::setObservedConstraintEntityVal(ConstraintEntity &ce, std::string ceval) {
    const std::string entitydatatype = ce.entityDatatype();
    const std::string entityid = ce.entityID();
    std::cout << "EntityDataType: " << entitydatatype;
    observedConstraintVal_ = ceval;
    std::pair<std::string, const std::string> cevalpair = std::make_pair(observedConstraintVal_, entitydatatype);
    observedConstraintValAndDatatypeMap_->try_emplace(entityid, cevalpair);
}

static bool conformance::constraints::integralTypeCheck(std::string val) {

    std::string valuetype = string(typeid(val).name());
    bool result = false;

    if (valuetype.compare("int") || valuetype.compare("int16_t") ||
        valuetype.compare("int32_t") || valuetype.compare("int64_t") ||
        valuetype.compare("size_t")) {
        result = true;
    }
    return result;
}

static bool conformance::constraints::floatTypeCheck(std::string val) {

    std::string valuetype = string(typeid(val).name());
    bool result = false;

    if (valuetype.compare("float") || valuetype.compare("double")) {
        result = true;
    }
    return result;
}

static bool conformance::constraints::containerTypeCheck(std::string val) {
    std::string valuetype = string(typeid(val).name());
    bool result = false;

    if (valuetype.compare("initializer_list") || valuetype.compare("list")) {
        result = true;
    }

    return result;
}

static ConstraintDefEvalStatus conformance::constraints::compareValues(std::string expectedVal, std::string observedVal,
                                                                       std::string valuetype, ConstraintOperator c_op) {
    // valuetype is the type of the expected or the observed val.
    // Sameness of both is tested before comparing values in this function.
    ConstraintDefEvalStatus result = ConstraintDefEvalStatus::FAILURE;

    switch (c_op) {
        case (conformance::constraints::ConstraintOperator::EQUALS):
        case (conformance::constraints::ConstraintOperator::GREATER_THAN_EQUALS):
        case (conformance::constraints::ConstraintOperator::LESS_THAN_EQUALS):
        case (conformance::constraints::ConstraintOperator::PRESENT):
            // Datatype comparisons and associations for value compare.
            // Compare for is_integral, is_floating_point, string comparison.
            if (conformance::constraints::integralTypeCheck(valuetype)) {
                auto intval_expected = atoi(expectedVal.c_str());
                auto intval_observed = atoi(observedVal.c_str());

                if (intval_observed == intval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                } else if (c_op == conformance::constraints::ConstraintOperator::GREATER_THAN_EQUALS &&
                           intval_observed > intval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                } else if (c_op == conformance::constraints::ConstraintOperator::LESS_THAN_EQUALS &&
                           intval_observed < intval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                } else if (c_op == conformance::constraints::ConstraintOperator::PRESENT &&
                           intval_observed > 0) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                }
            } else if (conformance::constraints::floatTypeCheck(valuetype)) {
                auto doubleval_expected = atof(expectedVal.c_str());
                auto doubleval_observed = atof(observedVal.c_str());

                if (doubleval_expected == doubleval_observed)
                    result = ConstraintDefEvalStatus::SUCCESS;

                else if (c_op == conformance::constraints::ConstraintOperator::GREATER_THAN_EQUALS &&
                         doubleval_observed > doubleval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                } else if (c_op == conformance::constraints::ConstraintOperator::LESS_THAN_EQUALS &&
                           doubleval_observed < doubleval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                } else if (c_op == conformance::constraints::ConstraintOperator::PRESENT &&
                           doubleval_observed > 0) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                }
            }
            break;

        case (conformance::constraints::ConstraintOperator::GREATER_THAN):
            if (conformance::constraints::integralTypeCheck(valuetype)) {
                auto intval_expected = atoi(expectedVal.c_str());
                auto intval_observed = atoi(observedVal.c_str());

                if (intval_observed > intval_expected)
                    result = ConstraintDefEvalStatus::SUCCESS;
                else
                    result = ConstraintDefEvalStatus::FAILURE;
            } else if (conformance::constraints::floatTypeCheck(valuetype)) {
                auto floatval_expected = atof(expectedVal.c_str());
                auto floatval_observed = atof(observedVal.c_str());

                if (floatval_observed > floatval_expected)
                    result = ConstraintDefEvalStatus::SUCCESS;
            }
            break;

        case (conformance::constraints::ConstraintOperator::LESS_THAN):
            if (conformance::constraints::integralTypeCheck(valuetype)) {
                auto intval_expected = atof(expectedVal.c_str());
                auto intval_observed = atof(observedVal.c_str());

                if (intval_observed < intval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                }
            } else if (conformance::constraints::floatTypeCheck(valuetype)) {
                auto floatval_expected = atof(expectedVal.c_str());
                auto floatval_observed = atof(observedVal.c_str());

                if (floatval_observed < floatval_expected) {
                    result = ConstraintDefEvalStatus::SUCCESS;
                }
            }
            break;
        case (conformance::constraints::ConstraintOperator::AND_OPERATOR):
            // TODO: Describing comparison with an AND operator
            // Segregate the comparisons as individual comparisons
            // OR use containers.
            break;
        case (conformance::constraints::ConstraintOperator::OR_OPERATOR):
            break;
        default:
            break;
    }

    return result;
}

// Expected constraint values as an std::pair and observed constraint values as an std::pair.
// For the combinatorial AND/OR, evaluate the result per definition.
// Then use the AND/OR result aggregate functions to arrive at the result status.
ConstraintDefEvalStatus
ConstraintDefinition::evaluateConformanceConstraintResult(std::pair<std::string, const std::string> &expected,
                                                          std::pair<std::string, const std::string> &observed,
                                                          ConstraintOperator coperator) {

    ConstraintDefEvalStatus result = ConstraintDefEvalStatus::FAILURE;
    std::string expectedVal = expected.first;
    const std::string expectedType = expected.second;

    std::string observedVal = expected.first;
    const std::string observedType = expected.second;

    ConstraintOperator c_op = coperator;

    if (expectedType.compare(observedType) != 0) {
        this->setConstraintDefEvalStatus(result);
        return result;
    }

    // Call to compare for evaluation.
    result = compareValues(expectedVal, observedVal, expectedType, c_op);
    this->setConstraintDefEvalStatus(result);
    return result;
}

ConstraintDefEvalStatus
valForCombinatorialAndDefinition(ConstraintDefEvalStatus result1, ConstraintDefEvalStatus result2) {

    ConstraintDefEvalStatus output = ConstraintDefEvalStatus::SUCCESS;
    switch (result1) {
        case (0):
            if (result2 == 0)
                output = ConstraintDefEvalStatus::SUCCESS;
            else if (result2 == 1)
                output = ConstraintDefEvalStatus::CONDITIONAL_SUCCESS;
            else
                output = ConstraintDefEvalStatus::FAILURE;
        case (1):
            if (result2 == 0 || result2 == 1)
                output = ConstraintDefEvalStatus::CONDITIONAL_SUCCESS;
            else
                output = ConstraintDefEvalStatus::FAILURE;
        case (2):
        default:
            output = ConstraintDefEvalStatus::FAILURE;
    }

    return output;
}

ConstraintDefEvalStatus valForCombinatorialOrDefinition(int16_t result1, int16_t result2) {

    ConstraintDefEvalStatus output = ConstraintDefEvalStatus::SUCCESS;
    switch (result1) {
        case (0):
            output = ConstraintDefEvalStatus::SUCCESS;
        case (1):
            if (result2 == 0 || result2 == 1)
                output = ConstraintDefEvalStatus::SUCCESS;
            else
                output = ConstraintDefEvalStatus::CONDITIONAL_SUCCESS;
        case (2):
            if (result2 == 0)
                output = ConstraintDefEvalStatus::SUCCESS;
            else if (result2 == 1)
                output = ConstraintDefEvalStatus::CONDITIONAL_SUCCESS;
            else
                output = ConstraintDefEvalStatus::FAILURE;
        default:
            output = ConstraintDefEvalStatus::FAILURE;
    }

    return output;
}

ConstraintDefEvalStatus valForCombinatorialConditionalDefinition(int16_t result1, int16_t result2) {
    ConstraintDefEvalStatus output = ConstraintDefEvalStatus::SUCCESS;
    if (!result1) {
        // Conditionals do not assume the first result check passing.
        output = ConstraintDefEvalStatus::SUCCESS;
    } else {
        if (result2 > 0) {
            output = ConstraintDefEvalStatus::SUCCESS;
        } else
            output = ConstraintDefEvalStatus::FAILURE;
    }

    return output;
}

void ConformanceConstraint::constraintShortDescription(const std::string &desc) {
    std::size_t substrlen = min(desc.length(), STR_SHORT_DESCRIPTION_LENGTH);
    constraint_short_desc_ = desc.substr(0, substrlen);
}

void ConformanceConstraint::constraintDetailedDescription(const std::string &desc) {
    std::size_t substrlen = min(desc.length(), STR_DETAILED_DESCRIPTION_LENGTH);
    constraint_detailed_desc_ = desc.substr(0, substrlen);
}

std::size_t ConstraintEntity::addChildEntityToEntity(ConstraintEntity &childentity) {
    // Placeholder.
//    std::string chname = childentity.entityName();
//    std::string chid = childentity.entityID();
//    std::string chdesc = childentity.entityDesc();
//    std::string chdatatype = childentity.entityDatatype();
//    std::size_t chhash = hashnum(chname);

    std::list<ConstraintEntity *> celist;
//    std::size_t listsize;
//
//    std::map<std::size_t, std::list<ConstraintEntity *>> *allsubentities = this->listSubEntities();
//
//    // Make a new map entry.
//    ConstraintEntity ceentity = ConstraintEntity(chname, chid, chdesc, chdatatype);
//    auto ceentry = allsubentities->find(chhash);
//
//    if (ceentry == allsubentities->end()) {
//        celist = {&ceentity};
//        // Indicates no entities under the given entity name.
//        auto entitypair = std::make_pair(chhash, celist);
//        allsubentities->try_emplace(chhash, &ceentity);
//    } else {
//
//        // Indicates presence of the given entity as a sub-entity in the instance.
//        celist = ceentry->second;
//
//        // Add the new child entity to the existing list
//        celist.emplace_back(&ceentity);
//        allsubentities->try_emplace(chhash, celist);
//    }
//
    return celist.size();
}

ConstraintDefinition::ConstraintDefinition(std::string
                                           defname, std::string
                                           defdesc, ConstraintEntity &entity) :
        constraintname_(defname), constraintdesc_(defdesc), entity_(&entity) {

    defStatus_ = ConstraintDefEvalStatus::SUCCESS;

    // Set a default operator until the setter is called.
    this->setConstraintOperatorForEntity(conformance::constraints::ConstraintOperator::PRESENT);

    // Expand upon the definition construction to build a constraint definition.
    // Change to failure/conditional failure as the conformance test progresses.
    this->setConstraintDefEvalStatus(conformance::constraints::ConstraintDefEvalStatus::SUCCESS);

}
