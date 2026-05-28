#include "autodiff_demo.h"

#include <imgui.h>

#include "autodiff.h"

namespace autodiff_demo {

void AutoDiffDemo::Run() {
  ImGui::Begin("AutoDiff Demo");
  ImGui::Text("This is a demo of automatic differentiation.");
  ImGui::End();
}

}  // namespace autodiff_demo