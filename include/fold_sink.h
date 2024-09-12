// #pragma once

#include <iostream>
#include <mutex>

#include <fmt/format.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

template <typename Mutex>
class fold_sink : public spdlog::sinks::base_sink<Mutex> {
 public:
  fold_sink() : last_msg_(""), repeat_count_(0) {}

 protected:
  void sink_it_(const spdlog::details::log_msg &msg) override {
    spdlog::memory_buf_t formatted;
    this->formatter_->format(msg, formatted);
    std::string current_msg = fmt::to_string(formatted);

    if (current_msg == last_msg_) {
      ++repeat_count_;
    } else {
      if (repeat_count_ > 0) {
        spdlog::memory_buf_t folded_msg;
        fmt::format_to(std::back_inserter(folded_msg),
                       "Previous message repeated {} times\n", repeat_count_);
        // this->log_it_(spdlog::details::log_msg(
        // msg.logger_name, spdlog::level::info, folded_msg));
        std::cout << fmt::to_string(folded_msg);
      }

      last_msg_ = current_msg;
      repeat_count_ = 0;

      std::cout << current_msg;
    }
  }

  void flush_() override {
    if (repeat_count_ > 0) {
      spdlog::memory_buf_t folded_msg;
      fmt::format_to(std::back_inserter(folded_msg),
                     "Previous message repeated {} times\n", repeat_count_);
      // this->log_it_(
      // spdlog::details::log_msg("none", spdlog::level::info, folded_msg));
    }
    this->flush_();
  }

 private:
  std::string last_msg_;
  size_t repeat_count_;
};
