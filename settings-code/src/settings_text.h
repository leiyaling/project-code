#ifndef AC841D0E_CED7_4196_81EB_F29980A83D4C
#define AC841D0E_CED7_4196_81EB_F29980A83D4C

#include "settings_node.h"

namespace rededa
{
    class RSettingsText : public RSettingsNode
    {
    public:
        RSettingsText(const std::string &name, const nlohmann::json &value)
            : RSettingsNode(name, value) {}

        ~RSettingsText() {}
    };

} // namespace rededa

#endif /* AC841D0E_CED7_4196_81EB_F29980A83D4C */
