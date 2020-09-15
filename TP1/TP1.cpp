#include "TP1.h"
#include <iostream>
#include "../libraries/lodepng/lodepng.h"
#include "../libraries/glm/glm.hpp"

int foo()
{
        glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
        glm::mat4 Model = glm::mat4(1.0);
        Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
        glm::vec4 Transformed = Model * Position;
        return 0;
}

int main()
{
  std::cout << "Hello World!";
  return 0;
}
