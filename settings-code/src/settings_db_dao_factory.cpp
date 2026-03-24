#include "settings_db_dao_factory.h"
#include "rededa/settings/i_settings_dao.h"
#include "settings_db_dao.h"

namespace rededa
{
    std::unique_ptr<IRSettingsDAO> RDBDAOFactory::createDAO()
    {
        return std::make_unique<RDBSettingsDAO>(mConnectionString);
    }
} // namespace rededa
