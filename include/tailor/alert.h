#ifndef ALERT_H
#define ALERT_H

#include <iostream>
#include "record.h"
using namespace std;

// Alert level
const static uint8_t AlertLevelWarning = 1;
const static uint8_t AlertLevelFatal = 2;
const static uint8_t AlertLevelUnknow = 255;

// Alert Description
const static uint16_t AlertCloseNotify = 0;
const static uint16_t AlertMMTLSCloseNotify = 1;
const static uint16_t AlertUnexceptedMessage = 10;
const static uint16_t AlertBadRecordMac = 20;
const static uint16_t AlertDescriptionFailed = 21;
const static uint16_t AlertRecordOverflow = 22;
const static uint16_t AlertDecompressionFailure = 30;
const static uint16_t AlertHandshakeFailure = 40;
const static uint16_t AlertNoCertificate = 41;
const static uint16_t AlertBadCertificate = 42;
const static uint16_t AlertUnsupportedCertificate = 43;
const static uint16_t AlertCertificateRevoke = 44;
const static uint16_t AlertCertificateExpired = 45;
const static uint16_t AlertCertificateUnknown = 46;
const static uint16_t AlertIllegalParameter = 47;
const static uint16_t AlertUnknowCA = 48;
const static uint16_t AlertAccessDenied = 49;
const static uint16_t AlertDecodeError = 50;
const static uint16_t AlertDecryptError = 51;
const static uint16_t AlertExportRestriction = 60;
const static uint16_t AlertProtocolVersion = 70;
const static uint16_t AlertInsuffcientSecurity = 71;
const static uint16_t AlertInternalError = 80;
const static uint16_t AlertInappropriateFallback = 86;
const static uint16_t AlertUserCanceled = 90;
const static uint16_t AlertNoRenegotiation = 100;
const static uint16_t AlertMissingExtention = 109;
const static uint16_t AlertUnsupportedExtention = 110;
const static uint16_t AlertCertificateNobtainable = 111;
const static uint16_t AlertUnrecognizedName = 112;
const static uint16_t AlertBadCertificateStatusResponse = 113;
const static uint16_t AlerBadCerfificateHashValue = 114;
const static uint16_t AlertUnknowPSKIdentify = 115;
const static uint16_t AlertCertificateRequired = 116;
const static uint16_t AlertNoApplicationProtocol = 120;
const static uint16_t AlertUnknow = 255;

namespace tailor {
    class Alert : public Record{
    private:
        uint8_t level;
        uint16_t desc;
    
    public:
        uint8_t getLevel() const
        {
            return this->level;
        }
        
        uint16_t getDesc() const
        {
            return this->desc;
        }

        void setLevel(uint8_t level)
        {
            this->level = level;
        }

        void setDesc(uint16_t desc)
        {
            this->desc = desc;
        }

        size_t serialize(std::basic_ostringstream<uint8_t>&);
        void deserialize(std::basic_istringstream<uint8_t>&);
    }
};

#endif  // ALERT_H