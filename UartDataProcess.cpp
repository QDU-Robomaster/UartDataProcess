#include "UartDataProcess.hpp"

#include <chrono>

#include "libxr_def.hpp"

UartDataProcess::UartDataProcess(LibXR::HardwareContainer& hw,
                                 LibXR::ApplicationManager& app)
{
  UNUSED(hw);
  // Hardware initialization example:
  // auto dev = hw.template Find<LibXR::GPIO>("led");
  this->imu_topic_ = LibXR::Topic("imu_topic", sizeof(UartDataT));

  auto uart_topic = LibXR::Topic(LibXR::Topic::Find("uart_topic"));
  auto uart_cb = LibXR::Topic::Callback::Create(
      [](bool, UartDataProcess* self, LibXR::RawData& data)
      {
        XR_LOG_DEBUG("Got uart!");
        auto* uart_msg = reinterpret_cast<UartData*>(data.addr_);
        self->UartCallback(uart_msg);
      },
      this);
  uart_topic.RegisterCallback(uart_cb);

  app.Register(*this);
}
void UartDataProcess::UartCallback(UartData* data)
{
  UartDataT data_t(*data);
  data_t.time = std::chrono::steady_clock::now();
  this->imu_topic_.Publish(data_t);
}