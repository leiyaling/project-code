#ifndef _SETTINGS_MODEL_DB_DAO_FACTORY_
#define _SETTINGS_MODEL_DB_DAO_FACTORY_

#include "rededa/settings/i_settings_dao.h"
#include "rededa/settings/i_settings_dao_factory.h"
#include <memory>
namespace rededa
{
    class RDBDAOFactory final: public IRSettingsDAOFactory
    {
    public:
        explicit RDBDAOFactory(const std::string &aConnStr) : mConnectionString(aConnStr) {}

        std::unique_ptr<IRSettingsDAO> createDAO() override;

    private:
        std::string mConnectionString;
    };
}; // namespace rededa

#endif //_SETTINGS_MODEL_DB_DAO_FACTORY_
