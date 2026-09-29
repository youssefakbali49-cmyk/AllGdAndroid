#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Création du menu personnalisé pour tous les niveaux Spin-Offs
class SpinOffMenu : public CCLayer {
protected:
    bool init() override {
        if (!CCLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Fond sombre
        auto bg = CCSprite::create("GJ_gradientBG.png");
        bg->setPosition(winSize / 2);
        bg->setScaleX(winSize.width / bg->getContentSize().width);
        bg->setScaleY(winSize.height / bg->getContentSize().height);
        this->addChild(bg, -1);

        // Bouton Retour
        auto backBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow01_001.png"),
            this,
            menu_selector(SpinOffMenu::onBack)
        );
        auto backMenu = CCMenu::create();
        backMenu->addChild(backBtn);
        backMenu->setPosition({25, winSize.height - 25});
        this->addChild(backMenu);

        // Menu de boutons pour les niveaux
        auto levelMenu = CCMenu::create();
        levelMenu->setPosition(winSize / 2);
        
        // Titre
        auto label = CCLabelBMFont::create("Spin-off Levels", "bigFont.fnt");
        label->setPosition({winSize.width / 2, winSize.height - 40});
        this->addChild(label);

        this->addChild(levelMenu);
        return true;
    }

    void onBack(CCObject*) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene(false)));
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

// Interception du bouton More Games dans le menu principal
class $modify(MyMenuLayer, MenuLayer) {
    void onMoreGames(CCObject* sender) {
        auto scene = SpinOffMenu::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
};
