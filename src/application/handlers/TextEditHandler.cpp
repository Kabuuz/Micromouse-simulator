#include <QDebug>
#include <application/handlers/TextEditHandler.hpp>

namespace application
{
namespace handlers
{
    TextEditHandler::TextEditHandler(QTextEdit* textEdit) :
        textEdit_(textEdit), prefix_("TextEditHandler")
    {}

    void TextEditHandler::doOnTextAdded(const std::string& text)
    {
        handle(text);
    }

    void TextEditHandler::handle(std::variant<int, std::string> change)
    {
        textEdit_->moveCursor(QTextCursor::End);
        if (textEdit_->document()->isEmpty())
        {
            textEdit_->insertPlainText(QString::fromStdString(std::get<std::string>(change)));
        }
        else
        {
            textEdit_->insertPlainText(
                QString::fromStdString("\n" + std::get<std::string>(change)));
        }
    }

}   // namespace handlers
}   // namespace application
