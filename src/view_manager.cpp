#include "view_skeleton.h"
#include "view_manager.h"

ViewManager::ViewManager()
{
  mapping.insert(std::pair<std::shared_ptr<Skeleton>, std::shared_ptr<SkeletonView>>());
}

ViewManager *ViewManager::Instance()
{
  static ViewManager instance;
  return &instance;
}

void ViewManager::remove_view(std::shared_ptr<View> view)
{

}
