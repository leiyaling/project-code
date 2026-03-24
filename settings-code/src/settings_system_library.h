#ifndef A7DFE383_7058_40A3_9D3E_38F1AB5C7D15
#define A7DFE383_7058_40A3_9D3E_38F1AB5C7D15
#include "settings_node.h"
#include "settings_keyvalue.h"
namespace rededa
{
    class RSettingsSystemLibrary : public RSettingsNode
    {
    public:
        RSettingsSystemLibrary() : RSettingsNode("Library", nlohmann::json()) {}
    };
} // namespace rededa
#endif /* A7DFE383_7058_40A3_9D3E_38F1AB5C7D15 */
