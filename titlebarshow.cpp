#include "titlebarshow.h"


TitleBarShow::TitleBarShow(QWidget *parent)
   : BaseWindow(parent)
{

    // 初始化标题栏;
    initTitleBar();
}

TitleBarShow::~TitleBarShow()
{

}

void TitleBarShow::initTitleBar()
{
    // 设置标题栏跑马灯效果，可以不设置;

    m_titleBar->setTitleIcon(":/images/images/5.ico");
    // m_titleBar->setTitleContent(QStringLiteral("矿用智能巡检系统"));
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

