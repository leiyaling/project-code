#ifndef BC82542F_BBD9_4774_819F_67F424BA4F2C
#define BC82542F_BBD9_4774_819F_67F424BA4F2C

#include "settings_node.h"
#include <string>
namespace rededa
{
    class RSettingsGeneral : public RSettingsNode
    {
    public:
        RSettingsGeneral(const std::string &name, const nlohmann::json &value)
            : RSettingsNode(name, value) {}

        ~RSettingsGeneral() {}
    };

} // namespace rededa

#endif /* BC82542F_BBD9_4774_819F_67F424BA4F2C */
