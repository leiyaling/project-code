#ifndef F0D12169_FCB9_4A77_830C_D15654907BBC
#define F0D12169_FCB9_4A77_830C_D15654907BBC

#include "settings_node.h"

namespace rededa
{
    class RSettingsDisplay : public RSettingsNode
    {
    public:
        RSettingsDisplay(const std::string &name, const nlohmann::json &value)
            : RSettingsNode(name, value) {}

        ~RSettingsDisplay() {}
    };

} // namespace rededa

#endif /* F0D12169_FCB9_4A77_830C_D15654907BBC */
