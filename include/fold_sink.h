// #pragma once

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>

#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/formatter.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/spdlog.h>

namespace spdlog {
namespace sinks {
template <typename Mutex>
class fold_sink : public ansicolor_sink<Mutex> {
 public:
  fold_sink()
      : spdlog::sinks::ansicolor_sink<Mutex>(stdout,
                                             spdlog::color_mode::automatic),
        formatter_(details::make_unique<spdlog::pattern_formatter>()),
        last_msg_(),
        repeat_count_(0) {}

  void log(const details::log_msg &msg) override {
    memory_buf_t formatted_cur, formatted_last;
    formatter_->format(msg, formatted_cur);
    formatter_->format(last_msg_, formatted_last);

    std::string str_cur, str_last;
    str_cur = fmt::to_string(formatted_cur);
    str_last = fmt::to_string(formatted_last);

    if (last_msg_.payload.data() &&
        strcmp(last_msg_.payload.data(), msg.payload.data()) == 0) {
      ++repeat_count_;
    } else {
      if (repeat_count_ > 0) {
        ansicolor_sink<Mutex>::log(
            details::log_msg(last_msg_.logger_name, last_msg_.level,
                             fmt::format("repeated {} times", repeat_count_)));
        repeat_count_ = 0;
      }
      last_msg_ = msg;
      ansicolor_sink<Mutex>::log(msg);
    }
  }

 private:
  details::log_msg last_msg_;
  std::size_t repeat_count_;
  std::unique_ptr<spdlog::formatter> formatter_;
};

}  // namespace sinks
}  // namespace spdlog
