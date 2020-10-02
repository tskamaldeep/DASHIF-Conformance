//
// Created by Kamaldeep Tumkur on 28/08/20.
//

#include "ConformanceConstraints.h"

using namespace std;
using namespace conformance::constraints;
using namespace conformance::exception;

ConformanceConstraint::ConformanceConstraint(ConstraintTypes cttype) : cttype_(cttype), constraint_short_desc_(""),
                                                                       constraint_detailed_desc_("") {

    // Define a few stack vars.
    std::string entityName;
    std::string entityDesc;
    const char *entityType;

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
                                                              std::string(typeid(std::string).name()));
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
            ConstraintEntity lang = ConstraintEntity("lang", "@lang",
                                                     "Dominant Language attribute associated with the adaptation set",
                                                     std::string(typeid(std::string).name()));

            allConstraints_->push_back(&mimeType);
            allConstraints_->push_back(&vMaxWidth);
            allConstraints_->push_back(&vMaxHeight);
            allConstraints_->push_back(&vMaxFrameRate);
            allConstraints_->push_back(&videoCodecs);
            allConstraints_->push_back(&par);
            allConstraints_->push_back(&sar);
            allConstraints_->push_back(&scanType);
            allConstraints_->push_back(&lang);
            break;
        }

        case ConstraintTypes::AudioAdaptationSetConstraints: {
            ConstraintEntity audioSamplingRate = ConstraintEntity("audioSamplingRate", "@audioSamplingRate",
                                                                  "Maximum Audio Sampling rate of the rendition",
                                                                  std::string(typeid(std::size_t).name()));
            ConstraintEntity audioCodecs = ConstraintEntity("audioCodecs", "@codecs", "Supported audio codecs",
                                                            std::string(typeid(std::string).name()));

            allConstraints_->push_back(&audioCodecs);
            allConstraints_->push_back(&audioSamplingRate);
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

            // Version 4.3 is the latest IOP version.
            ConstraintDefinition *version2ConstraintDef = new ConstraintDefinition("version2", "version2", version2Constraint);
            ConstraintDefinition *version3ConstraintDef = new ConstraintDefinition("version3", "version3", version3Constraint);
            ConstraintDefinition *version4_0_ConstraintDef = new ConstraintDefinition("version4_0", "version4_0", version4_0_Constraint);
            ConstraintDefinition *version4_1_ConstraintDef = new ConstraintDefinition("version4_1", "version4_1", version4_1_Constraint);
            ConstraintDefinition *version4_2_ConstraintDef = new ConstraintDefinition("version4_2", "version4_2", version4_2_Constraint);
            ConstraintDefinition *version4_3_ConstraintDef = new ConstraintDefinition("version4_3", "version4_3", version4_3_Constraint);

            constraintDefVersionsMap->insert_or_assign(version2Constraint, version2ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version2Constraint, version2ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version3Constraint, version3ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version4_0_Constraint, version4_0_ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version4_1_Constraint, version4_1_ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version4_2_Constraint, version4_2_ConstraintDef);
            constraintDefVersionsMap->insert_or_assign(version4_3_Constraint, version4_3_ConstraintDef);

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

    std::list<ConstraintEntity*> *allconstraints = allConstraints_;
    for (auto const& [cttype] : *allconstraints) {
        auto addr = std::addressof(cttype);
        ConstraintEntity iterEntity = static_pointer_cast<ConstraintEntity>(*addr);

        if (iterEntity.entityName().compare("mpdtype")) {
            // Initialize all the definitions of this constraint corresponding to this entity.
        }
        else if (iterEntity.entityName().compare("ast")) {
            // Initialize all the definitions of this constraint corresponding to this entity.
        }
        else if (iterEntity.entityName().compare("mediapresDuration")) {

        }
        else if (iterEntity.entityName().compare("availabilityTimeOffset")) {

        }
        else if (iterEntity.entityName().compare("minBufferTime")) {

        }
        else if (iterEntity.entityName().compare("mpdprofiles")) {

        }
        else if (iterEntity.entityName().compare("segmentAligned")) {

        }
        else if (iterEntity.entityName().compare("subsegmentAligned")) {

        }
        else if (iterEntity.entityName().compare("tsb")) {

        }
        else if (iterEntity.entityName().compare("minUpdatePeriod")) {

        }
        else if (iterEntity.entityName().compare("mimeType")) {

        }
        else if (iterEntity.entityName().compare("vMaxWidth")) {

        }
        else if (iterEntity.entityName().compare("vMaxHeight")) {

        }
        else if (iterEntity.entityName().compare("vMaxFrameRate")) {

        }
        else if (iterEntity.entityName().compare("videoCodecs")) {

        }
        else if (iterEntity.entityName().compare("sar")) {

        }
        else if (iterEntity.entityName().compare("par")) {

        }
        else if (iterEntity.entityName().compare("scanType")) {

        }
        else if (iterEntity.entityName().compare("lang")) {

        }
        else if (iterEntity.entityName().compare("audioSamplingRate")) {

        }
        else if (iterEntity.entityName().compare("audioCodecs")) {

        }
    }

    // Initialize the constraints/versions map.


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
    std::string chname = childentity.entityName();
    std::string chid = childentity.entityID();
    std::string chdesc = childentity.entityDesc();
    std::string chdatatype = childentity.entityDatatype();
    std::size_t chhash = hashnum(chname);

    std::list<ConstraintEntity *> celist;
    std::size_t listsize;

    std::map<std::size_t, std::list<ConstraintEntity *>> *allsubentities = this->listSubEntities();

    // Make a new map entry.
    ConstraintEntity ceentity = ConstraintEntity(chname, chid, chdesc, chdatatype);
    auto ceentry = allsubentities->find(chhash);

    if (ceentry == allsubentities->end()) {
        celist = {&ceentity};
        // Indicates no entities under the given entity name.
        auto entitypair = std::make_pair(chhash, celist);
        allsubentities->try_emplace(chhash, &ceentity);
    } else {

        // Indicates presence of the given entity as a sub-entity in the instance.
        celist = ceentry->second;

        // Add the new child entity to the existing list
        celist.emplace_back(&ceentity);
        allsubentities->insert_or_assign(chhash, celist);
    }

    return celist.size();
}

ConstraintDefinition::ConstraintDefinition(std::string defname, std::string defdesc, ConstraintEntity &entity) :
        constraintname_(defname), constraintdesc_(defdesc), entity_(&entity) {

    defStatus_ = ConstraintDefEvalStatus::SUCCESS;

    // Set a default operator until the setter is called.
    coperator_ = ConstraintOperator::PRESENT;

    // Expand upon the definition construction to build a constraint definition.
    
}

