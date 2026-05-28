#pragma once

#include <vector>

namespace autodiff_demo {

class AutoDiffDemo {
 public:
  void Run();

 private:
  bool precomputed_ = false;
  std::vector<double> xs_;
  std::vector<double> ys_;
};

}  // namespace autodiff_demo