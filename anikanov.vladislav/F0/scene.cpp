#include "scene.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <list.hpp>

anikanov::Scene::Scene(std::shared_ptr< SceneManager > &manager)
{
  this->manager = manager;
}

bool anikanov::Scene::exist(List< std::string > &list, std::string &command)
{
  return std::find(list.begin(), list.end(), command) != list.end();
}
