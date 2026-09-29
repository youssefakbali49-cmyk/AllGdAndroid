#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class SpinOffMenu : public CCLayer {
protected:
    bool init() override {
        if (!CCLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Fond
        auto bg = CCSprite::create("GJ_gradientBG.png");
        if (bg) {
            bg->setPosition(winSize / 2);
            bg->setScaleX(winSize.width / bg->getContentSize().width);
            bg->setScaleY(winSize.height / bg->getContentSize().height);
            this->addChild(bg, -1);
        }

        // Bouton Retour
        auto backBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Back"),
            this,
            menu_selector(SpinOffMenu::onBack)
        );
        auto backMenu = CCMenu::create();
        backMenu->addChild(backBtn);
        backMenu->setPosition({35, winSize.height - 25});
        this->addChild(backMenu);

        // Titre
        auto label = CCLabelBMFont::create("Spin-off Levels", "bigFont.fnt");
        label->setPosition({winSize.width / 2, winSize.height - 35});
        this->addChild(label);

        // Menu de boutons
        auto levelMenu = CCMenu::create();
        levelMenu->setPosition(winSize / 2);

        // Bouton Press Start (SubZero)
        auto btnPressStart = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Press Start"),
            this,
            menu_selector(SpinOffMenu::onPressStart)
        );

        // Bouton The Seven Seas (Meltdown)
        auto btnSevenSeas = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("The Seven Seas"),
            this,
            menu_selector(SpinOffMenu::onSevenSeas)
        );

        levelMenu->addChild(btnPressStart);
        levelMenu->addChild(btnSevenSeas);
        levelMenu->alignItemsVerticallyWithPadding(15.0f);
        this->addChild(levelMenu);

        return true;
    }

    void openLevel(int levelID) {
        auto level = GJGameLevel::create();
        level->m_levelID = levelID;
        auto scene = LevelInfoLayer::scene(level, false);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onBack(CCObject*) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene(false)));
    }

    void onPressStart(CCObject*) {
        // Charge la page du niveau Press Start
        openLevel(39000000);
    }

    void onSevenSeas(CCObject*) {
        // Charge la page du niveau The Seven Seas
        openLevel(15000000);
    }

public:
    static SpinOffMenu* create() {
        auto ret = new SpinOffMenu();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    static CCScene* scene() {
        auto scene = CCScene::create();
        scene->addChild(SpinOffMenu::create());
        return scene;
    }
};

class $modify(MyMenuLayer, MenuLayer) {
    void onMoreGames(CCObject* sender) {
        auto scene = SpinOffMenu::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
};
