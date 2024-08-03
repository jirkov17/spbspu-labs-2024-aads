#ifndef GRAPHMENUSCENE_HPP
#define GRAPHMENUSCENE_HPP

#include <iostream>
#include <list.hpp>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class GraphMenuScene : public Scene {
  public:
    GraphMenuScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help(bool need_description = false);
    List< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Kruskal's Algorithm for Finding Minimum Spanning Tree";
    List< List< int > > edges;
    List< command > commands{
        command{"/add", "add edge"},
        command{"/list", "current entered list"},
        command{"/pop",
                "delete the i-th element in the list, if i is not specified, then the last element is deleted"},
        command{"/end", "Finish entering the matrix"},
        command{"/back", "Enter the main menu"},
    };
  };
}

#endif
