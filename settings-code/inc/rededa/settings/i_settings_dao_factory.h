#ifndef _SETTINGS_I_SETTINGS_DAO_FACTORY_H
#define _SETTINGS_I_SETTINGS_DAO_FACTORY_H

#include "i_settings_dao.h"
#include <memory.h>
namespace rededa
{
    class IRSettingsDAOFactory
    {
        virtual std::unique_ptr<IRSettingsDAO> createDAO() = 0;
    };
} // namespace rededa

#endif //_SETTINGS_I_SETTINGS_DAO_FACTORY_H
