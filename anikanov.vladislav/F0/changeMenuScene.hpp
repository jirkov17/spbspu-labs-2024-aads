#ifndef CHANGEMENUSCENE_HPP
#define CHANGEMENUSCENE_HPP

#include <iostream>
#include <list.hpp>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class ChangeMenuScene : public Scene {
  public:
    ChangeMenuScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help();
  private:
    List< std::string > commands{
        "input",
        "output",
    };
  };
}

#endif
