#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MonPlayLayer, PlayLayer) {
    void levelComplete() {
        PlayLayer::levelComplete();

        std::string nomNiveau = m_level->m_levelName;

        Notification::create(
            "Succes AllGDAchieve : " + nomNiveau,
            NotificationIcon::Success
        )->show();
    }
};
