#include <memory>
#include <mutex>

#include <spdlog/details/console_globals.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include "fold_sink.h"

int main() {
  auto my_fold_sink = std::make_shared<
      spdlog::sinks::fold_sink<spdlog::details::console_mutex>>();
  auto logger = std::make_shared<spdlog::logger>("my_logger", my_fold_sink);
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
