#ifndef RUNMATRIXSCENE_HPP
#define RUNMATRIXSCENE_HPP

#include <iostream>
#include <list.hpp>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class RunMatrixScene : public Scene {
  public:
    RunMatrixScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help(bool need_description = false);
    List< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Kruskal's Algorithm for Finding Minimum Spanning Tree";
    List< List< int > > matrix;
    List< command > commands{
        command{"/rewrite", "Rewrite the matrix"},
        command{"/end", "Finish entering the matrix"},
        command{"/back", "Enter the main menu"},
    };
  };
}

#endif
