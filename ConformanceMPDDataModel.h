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
    const std::list<const std::string> AAC_AUDIO_CODECS = { MPEG4_AAC_CODEC, MPEG4_HE_AAC_CODEC, MPEG4_HE_AAC_v2_CODEC };

    // H.264 codec attributes.
    const std::string AVC_HIGH_LEVEL_40_28_CODEC = "avc1.640028";
    const std::string AVC_HIGH_LEVEL_40_30_CODEC = "avc1.640030";
    const std::string AVC_MAIN_LEVEL_CODEC = "avc1.4D401E";

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
            AVC_HIGH_LEVEL_40_28_CODEC, AVC_HIGH_LEVEL_40_30_CODEC, AVC_MAIN_LEVEL_CODEC
    };

    const std::size_t AUDIO_SAMPLE_RATE_44_1 = 44100;
    const std::size_t AUDIO_SAMPLE_RATE_48 = 48000;

    enum AdaptationSets : std::size_t {
        ADAPTATION_SET_VIDEO_TYPE = 0,
        ADAPTATION_SET_AUDIO_TYPE,
        ADAPTATION_SET_TEXT_TYPE
    };

    class ConformanceMPDRepresentation {
    private:
        const std::string repid_;
        std::string mimetype_ = VIDEO_MIME_TYPE;
        std::string codecs_ = std::string("");
        std::size_t repwidth_ = -1;
        std::size_t repheight_ = -1;
        std::size_t repaudiosamplerate_ = -1;
        std::size_t repframerate_ = -1;
        std::string repsar_ = std::string("");
        std::size_t repbandwidth_ = -1;
        bool repstartWithSAP_ = true;

    public:
        ConformanceMPDRepresentation(const std::string repid) : repid_(repid) {}

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

        // Set the rest of the attributes.
//        void setMimeTypeForRepresentation(std::string mimetype) {
//            if (mimetype != VIDEO_MIME_TYPE && mimetype != AUDIO_MIME_TYPE && mimetype != TEXT_MIME_TYPE) {
//                std::cerr << "Invalid mimeType provided with representation ID: " << repid_ << std::endl;
//                std::cerr << "mimetype setting failed." << std::endl;
//                return;
//            }
//
//            mimetype_ = std::move(mimetype);
//        }

        ~ConformanceMPDRepresentation() = default;

    };

    class ConformanceMPDAdaptationSet {
    private:
        const std::string adID_;
        bool segaligned_;
        std::size_t maxwidth_ = -1;
        std::size_t maxheight_ = -1;
        std::size_t maxframerate_ = -1;
        std::string par_ = "16:9";

    public:
        ConformanceMPDAdaptationSet(std::size_t pID, bool segaligned) {
            segaligned_ = segaligned;
//            adID_ = pID + "_" +
        }
    };

    class ConformanceMPDPeriod {
    private:
        std::size_t pid_;
        std::size_t pduration_;
//        std::list<>
    };

    class ConformanceMPDDataModel {
    private:
        const std::string xmlns_;
        float minbuffertime_;
        const std::string mpdtype_;
        float mpdduration_;
        std::size_t numperiods_;
        bool ismultipleperiods_ = false;
        std::list<const std::string> *mpdprofiles_;

//        bool createPeriodObjectFromMPD(const std::size_t pid, )

        bool createAdaptationSetFromMPD(AdaptationSets adaptationType, bool segAlignment = true);

        void addAttributeToAdaptationSet(const std::string attrkey, std::size_t attrval);

    public:
        bool isMultiplePeriods() { return numperiods_ > 1; }

        std::size_t numPeriods() { return numperiods_; }

    };

}


#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDDATAMODEL_H
