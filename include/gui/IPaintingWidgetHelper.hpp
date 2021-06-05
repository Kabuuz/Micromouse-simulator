#ifndef GUI_IPAINTINGWIDGETHELPER_HPP
#define GUI_IPAINTINGWIDGETHELPER_HPP

namespace gui
{
class IPaintingWidgetHelper
{
  public:
    IPaintingWidgetHelper() = default;
    virtual ~IPaintingWidgetHelper() = default;

  public:
    virtual void paint(QPainter* painter, QPaintEvent* event) = 0;
};

}   // namespace gui

#endif   // GUI_IPAINTINGWIDGETHELPER_HPP
