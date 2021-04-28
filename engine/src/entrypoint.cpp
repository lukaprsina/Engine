#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#include "platform/android/android_platform.h"
void android_main(android_app *state)
{
    engine::AndroidPlatform platform{state};
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
#include "platform/windows_platform.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     PSTR lpCmdLine, INT nCmdShow)
{
    engine::WindowsPlatform platform{hInstance, hPrevInstance,
                                     lpCmdLine, nCmdShow};
#else
#include "platform/unix_platform.h"
int main(int argc, char *argv[])
{
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    engine::UnixPlatform platform{engine::UnixType::Mac, argc, argv};
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    engine::UnixPlatform platform{engine::UnixType::Linux, argc, argv};
#endif
#endif

#ifndef DEBUG
    try
    {
#endif
        std::unique_ptr<engine::Application> app = std::make_unique<engine::Application>(&platform);
        app->SetName("Engine");
        app->ParseOptions(platform.GetArguments());

        if (platform.Initialize(std::move(app)))
        {
            platform.MainLoop();
            platform.Terminate(engine::ExitCode::Success);
        }
        else
        {
            platform.Terminate(engine::ExitCode::UnableToRun);
        }
#ifndef DEBUG
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
        platform.Terminate(engine::ExitCode::FatalError);
    }
#endif
}