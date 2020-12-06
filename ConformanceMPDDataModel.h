//
// Created by Kamaldeep Tumkur on 28/11/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEMPDDATAMODEL_H
#define DASHIF_CONFORMANCE_CONFORMANCEMPDDATAMODEL_H

#include <string>
#include <cfloat>
#include <iostream>
#include <algorithm>
#include <list>

namespace conformance::parser {

    const std::string VIDEO_MIME_TYPE = "video/mp4";
    const std::string AUDIO_MIME_TYPE = "audio/mp4";
    const std::string TEXT_MIME_TYPE = "application/mp4";

    // Audio codec attributes.
    const std::string MPEG4_AAC_CODEC = "mp4a.40.2";
    const std::string MPEG4_HE_AAC_CODEC = "mp4a.40.5";
    const std::string MPEG4_HE_AAC_v2_CODEC = "mp4a.40.29";
    // List of allowed audio codec settings.
    const std::list<const std::string> AAC_AUDIO_CODECS = {MPEG4_AAC_CODEC, MPEG4_HE_AAC_CODEC, MPEG4_HE_AAC_v2_CODEC};

    // H.264 codec attributes.
    const std::string AVC_HIGH_LEVEL_40_1E_CODEC = "avc1.64001e";
    const std::string AVC_HIGH_LEVEL_40_28_CODEC = "avc1.640028";
    const std::string AVC_HIGH_LEVEL_40_30_CODEC = "avc1.640030";
    const std::string AVC_MAIN_LEVEL_1_CODEC = "avc1.42C01F";
    const std::string AVC_MAIN_LEVEL_2_CODEC = "avc1.4D401E";
    const std::string AVC_MAIN_LEVEL_3_CODEC = "avc1.4D401F";
    // HEVC codec attributes.
    const std::string HEVC_MAIN_3_1_LEVEL_CODEC_1 = "hev1.1.2.L93.B0";
    const std::string HEVC_MAIN_4_1_LEVEL_CODEC_1 = "hev1.1.2.L123.B0";
    const std::string HEVC_MAIN_10_4_1_LEVEL_CODEC_1 = "hev1.2.4.L123.B0";

    const std::string HEVC_MAIN_3_1_LEVEL_CODEC_2 = "hvc1.1.2.L93.B0";
    const std::string HEVC_MAIN_4_1_LEVEL_CODEC_2 = "hvc1.12.L123.B0";
    const std::string HEVC_MAIN_10_4_1_LEVEL_CODEC_2 = "hvc1.2.4.L123.B0";
    // List of video codec settings.
    const std::list<const std::string> MP4_VIDEO_CODECS = {
            HEVC_MAIN_3_1_LEVEL_CODEC_1, HEVC_MAIN_4_1_LEVEL_CODEC_1, HEVC_MAIN_10_4_1_LEVEL_CODEC_1,
            HEVC_MAIN_3_1_LEVEL_CODEC_2, HEVC_MAIN_4_1_LEVEL_CODEC_2, HEVC_MAIN_10_4_1_LEVEL_CODEC_2,
            AVC_HIGH_LEVEL_40_28_CODEC, AVC_HIGH_LEVEL_40_30_CODEC, AVC_MAIN_LEVEL_1_CODEC, AVC_MAIN_LEVEL_2_CODEC,
            AVC_MAIN_LEVEL_3_CODEC
    };

    const std::size_t AUDIO_SAMPLE_RATE_44_1 = 44100;
    const std::size_t AUDIO_SAMPLE_RATE_48 = 48000;
    const std::list<const std::size_t> AUDIO_SAMPLE_RATES = {AUDIO_SAMPLE_RATE_44_1, AUDIO_SAMPLE_RATE_48};

    const std::size_t MAX_POSSIBLE_WIDTH_UHD = 3840;
    const std::size_t MAX_POSSIBLE_WIDTH_DCI = 4096;
    const std::size_t MAX_POSSIBLE_HEIGHT = 2160;

    // Assuming max frame rate of 30 for now.
    const float MAX_FRAME_RATE = 30.000000;
    const std::string DEFAULT_SAR = "1:1";

    const std::string PAR_16_9 = "16:9";
    const std::string PAR_4_3 = "4:3";

    enum AdaptationSets : std::size_t {
        ADAPTATION_SET_VIDEO_TYPE = 0,
        ADAPTATION_SET_AUDIO_TYPE,
        ADAPTATION_SET_TEXT_TYPE
    };

    enum AdaptationSetContentType : std::size_t {
        CONTENT_TYPE_VIDEO = 0,
        CONTENT_TYPE_IMAGE,
        CONTENT_TYPE_AUDIO,
        CONTENT_TYPE_TEXT
    };

    typedef struct S {
        std::size_t d;
        std::size_t r;
    } S;

    class ConformanceMPDSegmentTimeline {
    private:
        S s_;

    public:
        ConformanceMPDSegmentTimeline(std::size_t d, std::size_t r) {
            s_.d = std::move(d);
            s_.r = std::move(r);
        }

        std::size_t segdur () { return s_.d; }
        std::size_t segr() {return s_.r; }

        void assignS(S s) { s_ = std::move(s); }

        ~ConformanceMPDSegmentTimeline() = default;
    };

    class ConformanceMPDSegmentTemplate {
    private:
        std::size_t timescale_;
        std::size_t pts_;
        std::size_t duration_ = -1;
        std::string mediastr_;
        std::string initializationStr_;
        std::size_t startNum_;

        std::list<ConformanceMPDSegmentTimeline> segTimelines_ = {};
        bool segtimeslinesPresent_ = true;

    public:
        ConformanceMPDSegmentTemplate(std::size_t startnum, std::string initialization,
                                      std::string mediaStr, std::size_t timescale,
                                      std::size_t pts, std::size_t duration=-1);

        bool segTimelinesPresent() { return segtimeslinesPresent_; }
        std::size_t duration () { return duration_; }

        std::size_t addSegmentTimeline(std::size_t dur, std::size_t r);

        ~ConformanceMPDSegmentTemplate() = default;

    };

    class ConformanceMPDRepresentation {
    private:
        const std::string repid_;
        std::string mimetype_ = VIDEO_MIME_TYPE;
        std::string codecs_ = std::string("");
        std::size_t repwidth_ = -1;
        std::size_t repheight_ = -1;
        std::size_t repaudiosamplerate_ = -1;
        float repframerate_ = -1;
        std::string repsar_ = std::string("");
        std::size_t repbandwidth_ = -1;
        bool repstartWithSAP_ = true;

        std::size_t numsegmenttemplates_ = 0;
        std::list<ConformanceMPDSegmentTemplate> segmentTemplates_ = {};

    public:
        ConformanceMPDRepresentation(const std::string repid) : repid_(repid) {}

        const std::string repID() { return repid_; }

        std::list<ConformanceMPDSegmentTemplate> segmentTemplates() { return segmentTemplates_; }

        void setMimeTypeForRepresentation(std::string mimetype) {
            if (mimetype != VIDEO_MIME_TYPE && mimetype != AUDIO_MIME_TYPE && mimetype != TEXT_MIME_TYPE) {
                std::cerr << "Invalid mimeType provided with representation ID: " << repid_ << std::endl;
                std::cerr << "mimetype setting failed." << std::endl;
                return;
            }

            mimetype_ = std::move(mimetype);
        }

        void setCodecsForRepresentation(std::string codecs) {
            if (std::find(AAC_AUDIO_CODECS.begin(), AAC_AUDIO_CODECS.end(), codecs) == AAC_AUDIO_CODECS.end() &&
                std::find(MP4_VIDEO_CODECS.begin(), MP4_VIDEO_CODECS.end(), codecs) == MP4_VIDEO_CODECS.end()) {
                std::cerr << "Invalid codec parameters provided with representation ID: " << repid_ << std::endl;
                std::cerr << "codec param setting failed." << std::endl;
                return;
            }

            codecs_ = std::move(codecs);
        }

        void setWidthForRepresentation(std::size_t repwidth) {
            if (repwidth < 0 || repwidth > MAX_POSSIBLE_WIDTH_UHD) {
                std::cerr << "Invalid representation width provided with representation ID: " << repid_ << std::endl;
                std::cerr << "Representation width setting failed." << std::endl;
                return;
            }

            repwidth_ = std::move(repwidth);
        }

        void setHeightForRepresentation(std::size_t repheight) {
            if (repheight < 0 || repheight > MAX_POSSIBLE_HEIGHT) {
                std::cerr << "Invalid representation height provided with representation ID: " << repid_ << std::endl;
                std::cerr << "Representation height setting failed." << std::endl;
                return;
            }

            repheight_ = std::move(repheight);
        }

        void setAudioSampleRateForRepresentation(std::size_t asrate) {
            if (std::find(AUDIO_SAMPLE_RATES.begin(), AUDIO_SAMPLE_RATES.end(), asrate) == AUDIO_SAMPLE_RATES.end()) {
                std::cerr << "Invalid representation audio sample rate provided with representation ID: " << repid_
                          << std::endl;
                std::cerr << "Representation audio sample rate failed." << std::endl;
                return;
            }

            repaudiosamplerate_ = std::move(asrate);
        }

        void setVideoFrameRateForRepresentation(float repframerate) {
            if (repframerate < 0 || repframerate > MAX_FRAME_RATE) {
                std::cerr << "Invalid representation video frame rate provided with representation ID: " << repid_
                          << std::endl;
                std::cerr << "Representation video frame rate failed." << std::endl;
                return;
            }

            repframerate_ = std::move(repframerate);
        }

        void setSARForRepresentation(const std::string repsar) {
            // TODO: Refine check. Only "1:1" allowed for now.
            if (!repsar.compare(DEFAULT_SAR)) {
                std::cerr << "Invalid representation SAR provided with representation ID: " << repid_ << std::endl;
                std::cerr << "Representation SAR failed." << std::endl;
                return;
            }

            repsar_ = std::move(repsar);
        }

        void setStartWithSAPForRepresentation(bool startwithSAP) {
            repstartWithSAP_ = std::move(startwithSAP);
        }

        void setBandwidthForRepresentation(std::size_t bandwidth) {
            repbandwidth_ = std::move(bandwidth);
        }

        std::size_t addSegmentTemplateToRepresentation(ConformanceMPDSegmentTemplate segtmp);

        ~ConformanceMPDRepresentation() = default;

    };

    class ConformanceMPDAdaptationSet {
    private:
        const std::string adID_;
        bool segaligned_;
        std::size_t numrepresentations_ = 0;
        std::size_t maxwidth_ = -1;
        std::size_t maxheight_ = -1;
        std::size_t minwidth_ = -1;
        std::size_t minheight_ = -1;
        std::size_t adwidth_ = -1;
        std::size_t adheight_ = -1;

        std::size_t maxframerate_ = -1;
        std::size_t framerate_ = -1;

        std::string par_ = "16:9";
        // Look into validating via ISO 639-2 type.
        std::string langstr_ = "eng";
        std::size_t contentType_ = AdaptationSetContentType::CONTENT_TYPE_VIDEO;
        bool bitstreamswitching_ = true;
        std::list<ConformanceMPDRepresentation> representations_ = {};

    public:
        ConformanceMPDAdaptationSet(const std::string adID) : adID_(adID) {}

        const std::string adID() { return adID_; }

        std::list<ConformanceMPDRepresentation> representations() { return representations_; }

        void setPARForAdaptationSet(const std::string adpar);

        void setContentTypeForAdaptationSet(std::size_t ctype);

        void setBitstreamSwitchingForAdaptationSet(bool bsswitching);

        void setWidthForAdaptationSet(std::size_t widthval, bool max = false, bool min = false);

        void setHeightForAdaptationSet(std::size_t heightval, bool max = false, bool min = false);

        void setFrameRateForAdaptationSet(std::size_t frate, bool max = false);

        std::size_t addRepresentationToAdaptationSet(ConformanceMPDRepresentation &rep);

        // Consider ISO-639-2 validation. What langs are not supported by deployed decoders?
        void setLangAttributeForAdaptationSet(std::string langstr) { langstr_ = std::move(langstr); }

        ~ConformanceMPDAdaptationSet() = default;
    };

    class ConformanceMPDPeriod {
    private:
        std::string pid_;
        std::size_t pduration_;
        std::size_t pdstart_ = -1;
        bool starttagpresent = false;
        std::size_t numadaptationSets_;
        std::list<ConformanceMPDAdaptationSet> adaptationSets = {};

    public:
        ConformanceMPDPeriod(std::string pid, std::size_t pduration, std::size_t pdstart=-1);
        std::string pid() {return pid_; }
        std::size_t pduration() {return pduration_; }
        std::size_t numadaptationSets() {return numadaptationSets_; }

        std::size_t numAdaptationSets() { return adaptationSets.size(); }
        std::size_t addAdaptationSetToPeriod (ConformanceMPDAdaptationSet& aset);

        ~ConformanceMPDPeriod() = default;
    };

    class ConformanceMPDDataModel {
    private:
        const std::string xmlns_;
        float minbuffertime_;
        std::string mpdtype_;
        float mpdduration_;
        std::size_t numperiods_ = 0;
        bool ismultipleperiods_ = false;
        std::list<const std::string> *mpdprofiles_;
        std::list<ConformanceMPDPeriod> mpdPeriods = {};

    public:
        ConformanceMPDDataModel() {}

        bool isMultiplePeriods() { return numperiods_ > 1; }
        void addMPDProfile(const std::string profilestr) { mpdprofiles_->push_back(profilestr); }

        std::size_t addPeriodTagToMPD(ConformanceMPDPeriod& pd);

        std::size_t numPeriods() { return numperiods_; }
        float minBufferTime () {return minbuffertime_; }
        std::string MPDType() {return mpdtype_; }

        // Attributes of root MPD tree.
        // Private or public? Shift accordingly.
        void MPDType (std::string mpdtype) {mpdtype_ = std::move(mpdtype); }
        void MPDDuration (float mpddur) {mpdduration_ = std::move(mpddur); }
        void MPDMinBufferTime (float mpdmbt) { minbuffertime_= std::move(mpdmbt); }

        ~ConformanceMPDDataModel() = default;
    };

}


#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDDATAMODEL_H
