#include "IgnoreLineParser.hpp"
#include "CANBusManager.hpp"

namespace cantools_cpp
{

    bool IgnoreLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) {
        std::string _trimmed = line; // Copy line to trim it
        _trimmed.erase(0, _trimmed.find_first_not_of(" \t\n\r\f\v")); // Left trim

        // Helper lambda to replace starts_with for older C++ versions
        auto startsWith = [](const std::string& fullString, const std::string& beginning) -> bool {
            if (fullString.length() >= beginning.length()) {
                return fullString.compare(0, beginning.length(), beginning) == 0;
            }
            return false;

            };

        // Checking for specific start sequences or complete matches
        return startsWith(_trimmed, "VERSION") ||
            startsWith(_trimmed, "BS_") ||
            startsWith(_trimmed, "NS_ ") ||
            startsWith(_trimmed, "NS_DESC_") ||
            _trimmed == "CM_" ||
            _trimmed == "BA_DEF_" ||
            _trimmed == "BA_" ||
            _trimmed == "VAL_" ||
            _trimmed == "CAT_DEF_" ||
            _trimmed == "CAT_" ||
            _trimmed == "FILTER" ||
            _trimmed == "BA_DEF_DEF_" ||
            _trimmed == "EV_DATA_" ||
            _trimmed == "ENVVAR_DATA_" ||
            _trimmed == "SGTYPE_" ||
            _trimmed == "SGTYPE_VAL_" ||
            _trimmed == "BA_DEF_SGTYPE_" ||
            _trimmed == "BA_SGTYPE_" ||
            _trimmed == "SIG_TYPE_REF_" ||
            _trimmed == "VAL_TABLE_" ||
            _trimmed == "SIG_GROUP_" ||
            _trimmed == "SIG_VALTYPE_" ||
            _trimmed == "SIGTYPE_VALTYPE_" ||
            _trimmed == "BO_TX_BU_" ||
            _trimmed == "BA_DEF_REL_" ||
            _trimmed == "BA_REL_" ||
            _trimmed == "BA_DEF_DEF_REL_" ||
            _trimmed == "BU_SG_REL_" ||
            _trimmed == "BU_EV_REL_" ||
            _trimmed == "BU_BO_REL_" ||
            _trimmed == "SG_MUL_VAL_";
    }
}