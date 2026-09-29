#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class SpinOffMenu : public CCLayer {
protected:
    bool init() override {
        if (!CCLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Fond sombre
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

        // Menu principal pour les boutons de niveaux
        auto levelMenu = CCMenu::create();
        levelMenu->setPosition(winSize / 2);

        // Bouton Meltdown (Niveau 1001)
        auto btnMeltdown = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Meltdown"),
            this,
            menu_selector(SpinOffMenu::onMeltdown)
        );

        // Bouton World (Niveau 2001)
        auto btnWorld = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("World"),
            this,
            menu_selector(SpinOffMenu::onWorld)
        );

        // Bouton SubZero (Niveau 3001)
        auto btnSubZero = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("SubZero"),
            this,
            menu_selector(SpinOffMenu::onSubZero)
        );

        levelMenu->addChild(btnMeltdown);
        levelMenu->addChild(btnWorld);
        levelMenu->addChild(btnSubZero);

        levelMenu->alignItemsVerticallyWithPadding(15.0f);
        this->addChild(levelMenu);

        return true;
    }

    void onBack(CCObject*) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene(false)));
    }

    void onMeltdown(CCObject*) {
        auto scene = LevelSelectLayer::scene(1001);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onWorld(CCObject*) {
        auto scene = LevelSelectLayer::scene(2001);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onSubZero(CCObject*) {
        auto scene = LevelSelectLayer::scene(3001);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
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
