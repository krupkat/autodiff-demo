#pragma once

#include <vector>

namespace autodiff_demo {

class AutoDiffDemo {
 public:
  AutoDiffDemo();
  void Run();

 private:
  std::vector<double> xs_;
  std::vector<double> ys_;
};

}  // namespace autodiff_demo