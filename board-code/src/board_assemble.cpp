#include "board_assemble.h"
#include "rededa/board/common/common.h"
#include "rededa_baseoperate/base_operator_cpp_interface.h"
#include "rededa_baseoperate/base_operator_state_machine_manager/base_operator_operate_machine.h"
// // #include "board_controller_log.h"
#include "settings/settings_data.h"
#include "settings/i_settings.h"
#include "settings/settings_read.h"
#include "settings/settings_controller.h"
// // #include "vialist/editvialist.h"
// #include "rededa_color_manager/data/colormanager.h"
// #include "rededa_color_manager/data/color_manager_obj.h"
#include "drawing/cpp_interface.h"
#include "item_holder/item_holder/item_holder.h"
#include "item_holder/item_holder/item_holder_manager.h"
#include "item_holder/observer/item_holder_observers_manager.h"
#include "item_holder/filter/factory/item_holder_filter_factory.h"
#include "item_holder/dao/item_holder_db_dao.h"
#include "rededa_layer_manager/api/ilayermanager.h"
#include "rededa_layer_manager/data/layermanager.h"
#include "rededa_layer_manager/data/layermanager_obj.h"
#include "rededa_intergfx/include/cpp_api.h"
#include "shape_fsm/shape_fsm_cpp_interface.h"
#include "shape_fsm/shape_fsm_states/r_draw_complex_copper.h"
#include "shape_fsm/shape_fsm_state_machine_manager/shape_fsm_operate_machine.h"
#include "selection/selection/selection.h"
#include "selection/selection/selection_manager.h"
#include "copper/notifier/notifier_preview.h"
#include "copper/draw_complex_copper/idraw_complex_copper_cxx.h"

#include <iostream>

#include <unordered_map>
namespace rededa
{

    // // BoardAssemble::BoardAssemble()
    // //     : mLayerManger(nullptr), mLayerMangerID(-1), mColorManger(nullptr),
    // //       mColorMangerID(-1), mItemHolder(nullptr), mItemHolderID(-1),
    // //       mViaList(nullptr), mViaListID(-1), mScene(nullptr), mContext(nullptr),
    // //       mTransform(nullptr), msurface(nullptr), mRender(nullptr), mRenderID(-1),
    // //       mStateMachineManager(std::make_shared<RStateMachineManager>()),
    // //       mBaseOperatorOperateMachine(nullptr), mBaseOperatorOperateMachineID(-1),
    // //       mDrawLine(nullptr), mDrawLineID(-1)
    // // {
    // // }

    // BoardAssemble::BoardAssemble()
    //     : mLayerManger(nullptr), mLayerMangerID(-1), mColorManger(nullptr),mColorMangerID(-1),
    //       mItemHolder(nullptr), mItemHolderID(-1), mStateDrawComplexCopper(nullptr),
    //       mStateDrawComplexCopperID(-1)  , mScene(nullptr), mContext(nullptr),
    //       mTransform(nullptr), msurface(nullptr), mRender(nullptr), mRenderID(-1),
    //       mStateMachineManager(std::make_shared<common_fsm::RStateMachineManager>()),
    //       mBaseOperatorOperateMachine(nullptr), mBaseOperatorOperateMachineID(-1),
    //       mDrawLineMachine(nullptr), mDrawLineMachineID(-1),mDrawComplexCopperMachine(nullptr),
    //       mDrawComplexCopperMachineID(-1), mSelection(nullptr), mSelectionID(-1)
    // {
    // }

    BoardAssemble::BoardAssemble()
        : mLayerManger(nullptr), mLayerMangerID(-1),
          mItemHolder(nullptr), mItemHolderID(-1),
          mStateDrawComplexCopperID(-1), mScene(nullptr), mContext(nullptr),
          mTransform(nullptr), msurface(nullptr), mRender(nullptr), mRenderID(-1),
          mStateMachineManager(nullptr), mBaseOperatorOperateMachine(nullptr),
          mBaseOperatorOperateMachineID(-1), mDrawLineMachine(nullptr), mDrawLineMachineID(-1),
          mDrawComplexCopperMachine(nullptr), mDrawComplexCopperMachineID(-1),
          mSelection(nullptr), mSelectionID(-1), mSettingsID(-1)
    {
    }

    void BoardAssemble::assemble()
    {
        assembleFsmManager();
        assembleLayerManager();
        //     assembleColorManager();
        assembleItemHolder();
        // //     assembleViaList();
        assembleBaseOperateMachine();
        assembleRender();
        assembleSettings();
        assembleDrawComplexCopperMachine();
        assembleSelection();
        assembleDrawLineMachine();
    }

    void BoardAssemble::assembleFsmManager()
    {
        mStateMachineManager = std::make_shared<common_fsm::RStateMachineManager>();
    }

    void BoardAssemble::assembleLayerManager()
    {
        // 装载 layer manager
        mLayerManger = creatLayerManager();
        mLayerMangerID = registerLayerManager(mLayerManger);
    }

    // void BoardAssemble::assembleColorManager()
    // {
    //     // 装载 color manager
    //     mColorManger = creatColorManager();
    //     mColorMangerID = registerColorManager(mColorManger);

    // }

    void BoardAssemble::assembleItemHolder()
    {
        // TODO: DAO 对象创建设置
        mItemHolderID = RItemHolderManager::getInstance().registerModel();
        mItemHolder = RItemHolderManager::getInstance().getModel(mItemHolderID);
        auto itemholdDbDao = std::make_shared<RItemHolderDbDao>();
        mItemHolder->setDao(itemholdDbDao);
        // getRBoardLogger().info("assemble ItemHolder ID: {}", mItemHolderID);
    }

    // // void BoardAssemble::assembleViaList()
    // // {
    // //     mViaList = std::make_shared<EditViaList>();
    // //     mViaListID =
    // //         EditViaListObjectManager::getInstance().registerLayerObject(mViaList);
    // //     getRBoardLogger().info("assemble ViaList  ID: {}", mViaListID);
    // // }

    void BoardAssemble::assembleBaseOperateMachine()
    {
        // 创建基础操作状态机
        mBaseOperatorOperateMachine = base_operator::createFsm();

        // 注册到状态机管理器
        mStateMachineManager->registerMachine(mBaseOperatorOperateMachine);

        // 获取id
        mBaseOperatorOperateMachineID = mBaseOperatorOperateMachine->getMachineId();

        // getRBoardLogger().info("assemble BaseOperateMachine  ID: {}",
        //                        mBaseOperatorOperateMachineID);
    }

    void rededa::BoardAssemble::assembleDrawLineMachine()
    {
        // 创建drawline状态机
        mDrawLineMachine = drawing::createFsm();

        // 注册到状态机管理器
        mStateMachineManager->registerMachine(mDrawLineMachine);

        // 获取id
        mDrawLineMachineID = mDrawLineMachine->getMachineId();
    }

    void BoardAssemble::assembleDrawComplexCopperMachine()
    {
        // 创建画复杂铜皮状态机
        mDrawComplexCopperMachine = shape_fsm::createFsm();

        // 注册到状态机管理器
        mStateMachineManager->registerMachine(mDrawComplexCopperMachine);

        // 获取铜皮状态机id
        mDrawComplexCopperMachineID = mDrawComplexCopperMachine->getMachineId();

        RDrawComplexCopper &drawComplexCopper = mDrawComplexCopperMachine->getState<RDrawComplexCopper>();

        // 获取铜皮模块id
        mStateDrawComplexCopperID = drawComplexCopper.getStateHandle();
    }

    void BoardAssemble::assembleRender()
    {
        double x = 0;
        double y = 0;
        double width = 2000;
        double height = 2000;
        mContext = red_intergfx_render_context_create(
            width, height);

        red_intergfx_render_context_set_exposed_rect(mContext, 0.0, 0.0, width,
                                                     height);
        mTransform = red_renderer_transform_create(1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                                                   0.0, 0.0, 1.0);
        red_intergfx_render_context_set_world_transform(mContext, mTransform);
        // create scene
        mScene = red_intergfx_scene_create(0, 0, 400, 400);

        msurface = red_renderer_surface_create(width, height);
        mRender = red_renderer_renderer_create(msurface);
        mRenderID = 0;
    }

    void BoardAssemble::assembleSettings()
    {
        auto read = std::make_shared<RSettingsRead>();

        auto &controller = RSettingsController::instance();

        auto setting = controller.createByProduct(SettingsProduct::REDEDA_PKG);
        mSettingsID = read->addRSettings(setting);
    }

    void BoardAssemble::assembleSelection()
    {
        auto &manager = RSelectionManager::getInstance();
        auto handle = manager.registModel();
        mSelection = manager.getModel(handle);
        mSelectionID = mSelection->getId();
        mStateMachineManager->setSelector(mSelection);
    }

    void BoardAssemble::createModuleConnection()
    {
        //     createLayerManagerConnection();
        createSelectionConnection();
        createItemHolderConnection();
        createDrawLineConnection();
        createDrawComplexCopperConnection();
    }

    // void BoardAssemble::createLayerManagerConnection()
    // {
    //     // mColorManger->initLayerManager(mLayerManger.get());
    //     mColorManger -> getTableLayer() -> initLayerManager(mLayerManger);
    // }

    void BoardAssemble::createSelectionConnection()
    {
        mSelection->setItemHolderFilterFactory(mItemHolder->getFilterFactory());
    }

    void BoardAssemble::createItemHolderConnection()
    {
        // 创建 manager
        auto manager = intergfx::getSceneItemTotalManager();
        // 设置给场景
        setItemManager(mScene, manager);
        // 创建 渲染模块 普通画线观察者
        auto renderPresidentObserver = intergfx::getDrawLineObserverNormal(manager);
        auto renderPreviewObserver = intergfx::getDrawLineObserverPreview(manager);
        // 将观察者注册到itemholder
        mItemHolder->registerObserver(renderPresidentObserver);
        mItemHolder->registerObserver(renderPreviewObserver);
    }

    void BoardAssemble::createDrawLineConnection()
    {
        auto &drawLineMachine = mDrawLineMachine->getState<RDrawLine>();

        //     // 将层叠管理器注册到DrawLinwMachine
        //     // drawLineMachine.setLayerManager(mLayerManger);

        // 创建观察者
        auto itemholderObserverManager = mItemHolder->getObserversManager();
        auto itemholderObserver =
            itemholderObserverManager->createPreviewLineObserver();
        auto itemholderLineObserver =
            itemholderObserverManager->createLineObserver();

        // 将观察者注册到DrawLineMachine
        drawLineMachine.attachPreviewNotifier(itemholderObserver);
        drawLineMachine.attach(itemholderLineObserver);
    }

    void rededa::BoardAssemble::createDrawComplexCopperConnection()
    {
        // 创建观察者
        auto itemholderObserverManager = mItemHolder->getObserversManager();
        auto auxiliaryObserver =
            itemholderObserverManager->createCopperAuxiliaryLineObserver();
        auto saveObserver =
            itemholderObserverManager->createCopperPersistantLineObserver();
        auto previewObserver =
            itemholderObserverManager->createCopperPreviewLineObserver();
        auto saveCopper =
            itemholderObserverManager->createCopperPersistantCopperObserver();

        // 将观察者注册到DrawLineMachine
        RDrawComplexCopper &drawComplexCopper = mDrawComplexCopperMachine->getState<RDrawComplexCopper>();
        drawComplexCopper.attachCopperItemNotifier(saveCopper);
        drawComplexCopper.attachCopperPreviewNotifier(auxiliaryObserver);
        drawComplexCopper.attachCopperPreviewNotifier(saveObserver);
        drawComplexCopper.attachCopperPreviewNotifier(previewObserver);
    }

    std::shared_ptr<RLayerManager> BoardAssemble::getLayerManager() const
    {
        return mLayerManger;
    }

    int BoardAssemble::getLayerManagerID() const
    {
        return mLayerMangerID;
    }

    // int BoardAssemble::getColorManagerID() const
    // {
    //     return mColorMangerID;
    // }

    int BoardAssemble::getItemHolderID() const
    {
        return mItemHolderID;
    }

    // // int BoardAssemble::getViaListID() const
    // // {
    // //     return mViaListID;
    // // }

    int BoardAssemble::getDrawLineMachineID() const
    {
        return mDrawLineMachineID;
    }

    int BoardAssemble::getDrawComplexCopperMachineID() const
    {
        return mDrawComplexCopperMachineID;
    }

    int BoardAssemble::getSelectionID() const
    {
        return mSelectionID;
    }

    int BoardAssemble::getStateDrawComplexCopperID() const
    {
        return mStateDrawComplexCopperID;
    }

    int BoardAssemble::getBaseOperateMachineID() const
    {
        return mBaseOperatorOperateMachineID;
    }

    red_intergfx_scene_t *BoardAssemble::getScenePtr() const
    {
        return mScene;
    }

    red_intergfx_render_context_t *BoardAssemble::getContextPtr() const
    {
        return mContext;
    }

    red_renderer_transform_t *BoardAssemble::getTransformPtr() const
    {
        return mTransform;
    }

    red_renderer_surface_t *BoardAssemble::getSurfacePtr() const
    {
        return msurface;
    }

    red_renderer_renderer_t *BoardAssemble::getRenderPtr() const
    {
        return mRender;
    }

    int BoardAssemble::getSettingID() const
    {
        return mSettingsID;
    }

    // void BoardAssemble::setSettingProduct(const BoardProduct board_product)
    // {
    //     switch(board_product)
    //     {
    //         case BoardProduct::REDPKG:
    //             mSettingsProduct = SettingsProduct::REDEDA_PKG;
    //             break;
    //         case BoardProduct::REDPCB:
    //             mSettingsProduct = SettingsProduct::REDEDA_PCB;
    //             break;
    //         default:
    //             break;
    //     }
    // }

} // namespace rededa