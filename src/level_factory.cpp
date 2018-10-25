#include "level_factory.h"
#include "level_file.h"

namespace level_factory
{
    std::shared_ptr<Level> generate_level(Generator algorithm)
    {
      switch (algorithm)
      {
        case LEVEL_FILE:
          return std::shared_ptr<LevelFile>();
      }
    }
}
