#include "views/view_skeleton.h"
#include "view_manager.h"

ViewManager::ViewManager()
{

}

ViewManager *ViewManager::Instance()
{
  static ViewManager instance;
  return &instance;
}

void ViewManager::remove_view(long long view_id)
{
  auto iter = views.begin();
  while (iter != views.end()){
    if ((*iter)->get_id() == view_id){
      iter = views.erase(iter);
    }
    else {
      iter++;
    }
  }
}
