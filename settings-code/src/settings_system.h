#ifndef C595C6D3_8CE7_4F15_898D_2669CD8C3918
#define C595C6D3_8CE7_4F15_898D_2669CD8C3918

#include "settings_node.h"
#include "settings_system_library.h"
#include "settings_system_general.h"

namespace rededa
{
    class RSettingsSystem : public RSettingsNode
    {
    public:
        RSettingsSystem() : RSettingsNode("System", nlohmann::json()) {}

        ~RSettingsSystem() {}
    };

} // namespace rededa

#endif /* C595C6D3_8CE7_4F15_898D_2669CD8C3918 */
