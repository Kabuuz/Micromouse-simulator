#ifndef APPLICATION_HANDLERS_TEXTEDITHANDLER_HPP
#define APPLICATION_HANDLERS_TEXTEDITHANDLER_HPP

#include <QString>
#include <QTextEdit>
#include <application/handlers/IHandler.hpp>

namespace application
{
namespace handlers
{
    class TextEditHandler : public IHandler
    {
      public:
        TextEditHandler(QTextEdit* textEdit);

      public slots:
        void doOnTextAdded(const std::string& text);

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        QTextEdit* textEdit_;
        QString prefix_;
    };

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_HANDLERS_TEXTEDITHANDLER_HPP
