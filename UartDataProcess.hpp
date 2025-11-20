#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: process the uart received data
constructor_args: []
template_args: []
required_hardware: []
depends: []
=== END MANIFEST === */
// clang-format on

#include <array>

#include "app_framework.hpp"
#include "message.hpp"
#include "timebase.hpp"
struct UartData
{
  std::array<float, 4> Quat;
  UartData() {}
  UartData(float a, float b, float c, float d) : Quat{a, b, c, d} {}
};
struct UartDataT
{
  UartData data;
  LibXR::MicrosecondTimestamp time;
  UartDataT(UartData dataRaw) : data(dataRaw) {}
  UartDataT() {}
};
class UartDataProcess : public LibXR::Application
{
 public:
  UartDataProcess(LibXR::HardwareContainer& hw, LibXR::ApplicationManager& app);
  void OnMonitor() override {}

 private:
  void UartCallback(UartData* data);
  LibXR::Topic imu_topic_;
};
