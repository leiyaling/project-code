#ifndef INCLUDE_BOARD_OBJ_BOARD_ASSEMBLE
#define INCLUDE_BOARD_OBJ_BOARD_ASSEMBLE
#include "rededa_intergfx/include/api.h"
#include "rededa_renderer/include/api.h"
#include "settings/settings_data.h"
#include "rededa/board/common/common.h"

#include <memory>
#include <unordered_map>

class RItemHolder;
class RLayerManager;
// class RColorManager;
// class IEditViaList;
class RSelection;
namespace rededa
{
    class IRSettings;
    class RDrawOperateMachine;
    class RShape_fsmOperateMachine;
    namespace base_operator
    {
        class RBaseOperatorOperateMachine;
    }
    namespace common_fsm
    {
        class RStateMachineManager;
    }
    namespace copper
    {
        class IRStateDrawComplexCopper;
    }
    class BoardAssemble
    {
    public:
        BoardAssemble();
        virtual ~BoardAssemble() = default;
        void assemble();
        void assembleFsmManager();
        void assembleLayerManager();
        //     void assembleColorManager();
        void assembleItemHolder();
        void assembleStateDrawComplexCopper();
        void assembleRender();
        // //     void assembleViaList();
        void assembleBaseOperateMachine();
        void assembleSettings();
        void assembleDrawLineMachine();
        void assembleDrawComplexCopperMachine();
        void assembleSelection();

        void createModuleConnection();
        //     void createLayerManagerConnection();
        void createDrawLineConnection();
        void createItemHolderConnection();
        void createSelectionConnection();
        void createDrawComplexCopperConnection();
        std::shared_ptr<RLayerManager> getLayerManager() const;

        int getLayerManagerID() const;
        //     int getColorManagerID() const;
        int getItemHolderID() const;
        // //     int getViaListID() const;
        int getDrawLineMachineID() const;
        int getDrawComplexCopperMachineID() const;
        int getSelectionID() const;
        int getStateDrawComplexCopperID() const;
        int getBaseOperateMachineID() const;

        red_intergfx_scene_t *getScenePtr() const;
        red_intergfx_render_context_t *getContextPtr() const;
        red_renderer_transform_t *getTransformPtr() const;
        red_renderer_surface_t *getSurfacePtr() const;
        red_renderer_renderer_t *getRenderPtr() const;

        int getSettingID() const;
        void setSettingProduct(const BoardProduct board_product);

    private:
        std::shared_ptr<RLayerManager> mLayerManger;
        int mLayerMangerID;

        //     std::shared_ptr<RColorManager> mColorManger;
        //     int mColorMangerID;

        std::shared_ptr<RItemHolder> mItemHolder;
        int mItemHolderID;

        // std::shared_ptr<copper::IRStateDrawComplexCopper> mStateDrawComplexCopper;
        int mStateDrawComplexCopperID;

        // //     std::shared_ptr<IEditViaList> mViaList;
        //     int mViaListID;

        red_intergfx_scene_t *mScene;
        red_intergfx_render_context_t *mContext;
        red_renderer_transform_t *mTransform;
        red_renderer_surface_t *msurface;
        red_renderer_renderer_t *mRender;
        int mRenderID;

        std::shared_ptr<common_fsm::RStateMachineManager> mStateMachineManager;                  ///< 状态机管理器
        std::shared_ptr<base_operator::RBaseOperatorOperateMachine> mBaseOperatorOperateMachine; ///< 基础操作状态机
        int mBaseOperatorOperateMachineID;                                                       ///< 基础操作状态机ID

        std::shared_ptr<RDrawOperateMachine> mDrawLineMachine; ///< drawline状态机
        int mDrawLineMachineID;                                ///< drawline状态机ID

        std::shared_ptr<RShape_fsmOperateMachine> mDrawComplexCopperMachine; ///< 画复杂铜皮状态机
        int mDrawComplexCopperMachineID;                                     ///< 画复杂铜皮状态机ID

        std::shared_ptr<RSelection> mSelection;
        int mSelectionID;

        //     std::unordered_map<int, std::shared_ptr<IRSettings>>
        //         mSettings; ///< settings

        std::shared_ptr<IRSettings> mSettings;
        int mSettingsID;

        SettingsProduct mSettingsProduct; ///< settings的产品类型
    };

} // namespace rededa

#endif /* INCLUDE_BOARD_OBJ_BOARD_ASSEMBLE */