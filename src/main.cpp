#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// ÉTAPE 2 : Menu de choix entre SubZero, Meltdown et World
class SpinOffSelectMenu : public CCLayer {
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

        // Bouton Retour (Étape 1)
        auto backBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Back"),
            this,
            menu_selector(SpinOffSelectMenu::onBack)
        );
        auto backMenu = CCMenu::create();
        backMenu->addChild(backBtn);
        backMenu->setPosition({35, winSize.height - 25});
        this->addChild(backMenu);

        // Menu horizontal pour les 3 cartes/boutons
        auto gamesMenu = CCMenu::create();

        // Bouton GD SubZero
        auto btnSubZero = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("GD SubZero"),
            this,
            menu_selector(SpinOffSelectMenu::onSubZero)
        );

        // Bouton GD Meltdown
        auto btnMeltdown = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("GD Meltdown"),
            this,
            menu_selector(SpinOffSelectMenu::onMeltdown)
        );

        // Bouton GD World
        auto btnWorld = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("GD World"),
            this,
            menu_selector(SpinOffSelectMenu::onWorld)
        );

        gamesMenu->addChild(btnSubZero);
        gamesMenu->addChild(btnMeltdown);
        gamesMenu->addChild(btnWorld);

        gamesMenu->alignItemsHorizontallyWithPadding(15.0f);
        gamesMenu->setPosition(winSize / 2);
        this->addChild(gamesMenu);

        return true;
    }

    void onBack(CCObject*) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene(false)));
    }

    // ÉTAPE 3 : Redirection vers les carrousels de niveaux
    void onSubZero(CCObject*) {
        // Ouvre le carrousel SubZero (Press Start, etc.)
        auto scene = LevelSelectLayer::scene(4001); 
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onMeltdown(CCObject*) {
        // Ouvre le carrousel Meltdown (The Seven Seas, etc.)
        auto scene = LevelSelectLayer::scene(1001);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onWorld(CCObject*) {
        // Ouvre le carrousel World (Payload, etc.)
        auto scene = LevelSelectLayer::scene(2001);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

public:
    static SpinOffSelectMenu* create() {
        auto ret = new SpinOffSelectMenu();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    static CCScene* scene() {
        auto scene = CCScene::create();
        scene->addChild(SpinOffSelectMenu::create());
        return scene;
    }
};

// ÉTAPE 1 : Interception du bouton More Games
class $modify(MyMenuLayer, MenuLayer) {
    void onMoreGames(CCObject* sender) {
        auto scene = SpinOffSelectMenu::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
};
