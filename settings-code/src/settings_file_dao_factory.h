#ifndef _SETTINGS_FILE_DAO_FACTORY_
#define _SETTINGS_FILE_DAO_FACTORY_

#include "rededa/settings/i_settings_dao.h"
#include "rededa/settings/i_settings_dao_factory.h"
#include <memory>
namespace rededa
{
    class RFileDAOFactory final: public IRSettingsDAOFactory
    {
    public:
        explicit RFileDAOFactory(const std::string &aPath) : mFilePath(aPath) {}

        std::unique_ptr<IRSettingsDAO> createDAO() override;

    private:
        std::string mFilePath;
    };
}; // namespace rededa

#endif //_SETTINGS_FILE_DAO_FACTORY_