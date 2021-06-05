#ifndef APPLICATION_HANDLERS_IHANDLER_HPP
#define APPLICATION_HANDLERS_IHANDLER_HPP

#include <QObject>
#include <string>
#include <variant>

namespace application
{
namespace handlers
{
    class IHandler : public QObject
    {
        Q_OBJECT

      public:
        IHandler() = default;
        virtual ~IHandler() = default;

      protected:
        virtual void handle(std::variant<int, std::string> change) = 0;
    };

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_HANDLERS_IHANDLER_HPP
