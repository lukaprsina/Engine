#pragma once

namespace engine
{
    enum class ExitCode
    {
        Success = 0,     /* App prepare succeeded, it ran correctly and exited properly with no errors */
        UnableToRun = 1, /* App prepare failed, could not run */
        FatalError = 2   /* App encountered an unexpected error */
    };

    class Window
    {
    };
    class Application
    {
    };
    class Timer
    {
    };

    class Platform
    {
    public:
        Platform() = default;
        virtual ~Platform() = default;

        virtual bool Initialize(std::unique_ptr<Application> &&app);
        virtual void MainLoop();
        virtual void Terminate(ExitCode code);
        virtual void Close() const;

        Window &GetWindow() { return *m_Window; };
        Application &GetApplication() { return *m_App; };

        static void SetArguments(const std::vector<std::string> &arguments) { m_Arguments = arguments; };
        std::vector<std::string> &GetArguments() { return Platform::m_Arguments; };

        static void SetExternalStorageDirectory(const std::string &directory);
        std::string GetExternalStorageDirectory() { return Platform::m_ExternalStorageDirectory; };

        static void SetTempDirectory(const std::string &dir);
        std::string GetTempDirectory() { return Platform::m_TempDirectory; };

    protected:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Application> m_App;
        Timer m_Timer;

        virtual void CreateWindow() = 0;

    private:
        static std::vector<std::string> m_Arguments;
        static std::string m_ExternalStorageDirectory;
        static std::string m_TempDirectory;
    };
}