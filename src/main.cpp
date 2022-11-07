#include "application.h"
#include "spdlog/spdlog.h"

int main()
{
#if defined(BX_LOG_DEBUG_MODE)
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    const Application application;
    application.run();

    return 0;
}