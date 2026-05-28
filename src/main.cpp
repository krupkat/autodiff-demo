//------------------------------------------------------------------------------
//  imgui-sapp.c
//
//  Demonstrates Dear ImGui UI rendering via sokol_gfx.h and
//  the utility header sokol_imgui.h.
//
//  Also tests default window size by keeping sapp_desc.width/height
//  zero-initialized.
//
// MIT License
//
// Copyright (c) 2017 Andre Weissflog
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------

#ifdef __EMSCRIPTEN__
#define SOKOL_GLES3
#else
#define SOKOL_GLCORE
#endif
#define SOKOL_IMPL

#include <imgui.h>
#include <implot.h>
#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>
#include <util/sokol_imgui.h>

#include "autodiff_demo.h"

static sg_pass_action pass_action;

void Init(void) {
  sg_desc desc = {};
  desc.environment = sglue_environment();
  desc.logger.func = slog_func;
  sg_setup(&desc);

  simgui_desc_t simgui_desc = {};
  simgui_desc.logger.func = slog_func;
  simgui_setup(&simgui_desc);

  ImPlot::CreateContext();

  pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
  pass_action.colors[0].clear_value = {0.0f, 0.5f, 0.7f, 1.0f};
}

void Frame(void) {
  static autodiff_demo::AutoDiffDemo demo;

  const int width = sapp_width();
  const int height = sapp_height();
  const double delta_time = sapp_frame_duration();
  simgui_new_frame({width, height, delta_time, sapp_dpi_scale()});

  ImGui::ShowDemoWindow();
  ImPlot::ShowDemoWindow();

  demo.Run();

  sg_pass pass = {};
  pass.action = pass_action;
  pass.swapchain = sglue_swapchain();
  sg_begin_pass(&pass);
  simgui_render();
  sg_end_pass();
  sg_commit();
}

void Cleanup(void) {
  ImPlot::DestroyContext();
  simgui_shutdown();
  sg_shutdown();
}

void Input(const sapp_event* event) { simgui_handle_event(event); }

sapp_desc sokol_main(int argc, char* argv[]) {
  sapp_desc desc = {};
  desc.init_cb = Init;
  desc.frame_cb = Frame;
  desc.cleanup_cb = Cleanup;
  desc.event_cb = Input;
  desc.window_title = "autodiff-demo";
  desc.ios.keyboard_resizes_canvas = false;
  desc.icon.sokol_default = true;
  desc.enable_clipboard = true;
  desc.logger.func = slog_func;
  return desc;
}