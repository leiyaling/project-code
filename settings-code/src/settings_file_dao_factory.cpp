#include "settings_file_dao_factory.h"
#include "settings_file_dao.h"

namespace rededa
{
    std::unique_ptr<IRSettingsDAO> RFileDAOFactory::createDAO()
    {
        return std::make_unique<RFileSettingsDAO>(mFilePath);
    }
} // namespace rededa
