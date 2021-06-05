#ifndef APPLICATION_PAINT_IPAINTER_HPP
#define APPLICATION_PAINT_IPAINTER_HPP

namespace application
{
namespace paint
{
    class IPainter
    {
      public:
        virtual ~IPainter() = default;

        virtual void paint(QPainter* painter) = 0;
        virtual void setColor(unsigned int color) = 0;
        virtual void setWidth(unsigned int width) = 0;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_IPAINTER_HPP
