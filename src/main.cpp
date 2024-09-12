#include <memory>
#include <mutex>

#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include "fold_sink.h"

int main() {
  auto logger = std::make_shared<spdlog::logger>(
      "my_logger", std::make_shared<fold_sink<std::mutex>>());
  spdlog::set_default_logger(logger);

  spdlog::info("This is a msg for A.");
  spdlog::info("This is a msg for A.");
  spdlog::info("This is a msg for A.");
  spdlog::info("This is a msg for A.");
  spdlog::info("This is a msg for A.");

  spdlog::info("This is a msg for B.");
  spdlog::info("This is a msg for C.");

  return 0;
}
