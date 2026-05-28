#include "autodiff_demo.h"

#include <utility>

#include <imgui.h>
#include <implot.h>

#include "autodiff.h"

namespace autodiff_demo {

// Interesting function: damped multi-frequency wave
// f(x) = sin(x) * cos(x/3) * exp(-x*x/40)
template <typename TValueType>
TValueType f(TValueType x) {
  return sin(x) * cos(x / 3.0) * exp(-x * x / 40.0);
}

AutoDiffDemo::AutoDiffDemo() {
  constexpr double kXMin = -10.0;
  constexpr double kXMax = 10.0;
  constexpr int kSamples = 600;

  xs_.resize(kSamples);
  ys_.resize(kSamples);

  for (int i = 0; i < kSamples; ++i) {
    double x = kXMin + (kXMax - kXMin) * i / (kSamples - 1);
    xs_[i] = x;
    ys_[i] = f(x);
  }
}

static void PlotTangent(double x0, double fx0, double dfx0) {
  constexpr double kHalfWidth = 2.5;
  double tx[2], ty[2];
  tx[0] = x0 - kHalfWidth;
  ty[0] = fx0 + dfx0 * (tx[0] - x0);
  tx[1] = x0 + kHalfWidth;
  ty[1] = fx0 + dfx0 * (tx[1] - x0);
  ImPlot::PlotLine("Tangent", tx, ty, 2,
                   ImPlotSpec(ImPlotProp_LineColor, ImVec4(1, 0.4f, 0.1f, 1.0f),
                              ImPlotProp_LineWeight, 2.0f));
}

void AutoDiffDemo::Run() {
  ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
  ImGui::Begin("AutoDiff Demo");

  // Evaluate f and its derivative at a point using forward-mode autodiff
  auto eval_with_deriv = [](double x0) -> std::pair<double, double> {
    dual x = x0;
    x.grad = 1.0;  // seed: dx/dx = 1
    dual result = f(x);
    return {result.val, result.grad};  // return f(x0) and f'(x0)
  };

  ImGui::Text("f(x) = sin(x) * cos(x/3) * exp(-x²/40)");
  ImGui::Spacing();

  if (ImPlot::BeginPlot("##autodiff", ImVec2(-1, -1))) {
    ImPlot::SetupAxes("x", "f(x)");
    ImPlot::SetupAxisLimits(ImAxis_X1, xs_.front(), xs_.back(),
                            ImPlotCond_Once);
    ImPlot::SetupAxisLimits(ImAxis_Y1, -1.2, 1.2, ImPlotCond_Once);

    // Plot the function
    ImPlot::PlotLine("f(x)", xs_.data(), ys_.data(), xs_.size());

    // Hover detection
    if (ImPlot::IsPlotHovered()) {
      ImPlotPoint mouse = ImPlot::GetPlotMousePos();

      double x0 = mouse.x;
      auto [fx0, dfx0] = eval_with_deriv(x0);

      // Vertical line at mouse x
      double vline_x = x0;
      ImPlot::PlotInfLines(
          "##vline", &vline_x, 1,
          ImPlotSpec(ImPlotProp_LineColor, ImVec4(1, 1, 0, 0.6f),
                     ImPlotProp_LineWeight, 1.5f));

      // Tangent line: y = fx0 + dfx0 * (x - x0)
      PlotTangent(x0, fx0, dfx0);

      // Dot at (x0, f(x0))
      ImPlot::PlotScatter(
          "##dot", &x0, &fx0, 1,
          ImPlotSpec(ImPlotProp_Marker, (float)ImPlotMarker_Circle,
                     ImPlotProp_MarkerSize, 6.0f, ImPlotProp_MarkerFillColor,
                     ImVec4(1, 0.4f, 0.1f, 1.0f), ImPlotProp_MarkerLineColor,
                     ImVec4(1, 0.4f, 0.1f, 1.0f)));

      // Tooltip
      ImGui::BeginTooltip();
      ImGui::Text("x      = %.4f", x0);
      ImGui::Text("f(x)   = %.4f", fx0);
      ImGui::Text("f'(x)  = %.4f", dfx0);
      ImGui::EndTooltip();
    }

    ImPlot::EndPlot();
  }

  ImGui::End();
}

}  // namespace autodiff_demo