#ifndef C41C87DF_B89C_444F_994E_C7CB823E2964
#define C41C87DF_B89C_444F_994E_C7CB823E2964

#include "settings_node.h"
#include "settings_keyvalue.h"
namespace rededa
{
    class RSettingsSystemGeneral : public RSettingsNode
    {
    private:
    public:
        RSettingsSystemGeneral() : RSettingsNode("General", nlohmann::json()) {}
    };

} // namespace rededa

#endif /* C41C87DF_B89C_444F_994E_C7CB823E2964 */
