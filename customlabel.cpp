#include "customlabel.h"
#include <QDebug>
customLabel::customLabel(QWidget *parent) : QLabel(parent)
{
    m_backupHeadImg = "";
}
//设置头像
void customLabel::setHeadImage(const QString & fileName)
{
    QPixmap headPic(fileName);
    setPixmap(headPic.scaled(125,125,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_backupHeadImg = fileName;
}

//鼠标进入事件
void customLabel::enterEvent(QEvent * event)
{
    setStyleSheet("background-color:rgba(0,0,0,100);"  // 半透明
                  "color: white;"                     //白色文本
                  "font-weight:bold;" );                 //粗体

    setText("更改头像");
    setAlignment(Qt::AlignCenter); //设置居中
    QLabel::enterEvent(event);//让进入事件回归到父类
}

//鼠标离开事件
void customLabel::leaveEvent(QEvent * event)
{
    setHeadImage(m_backupHeadImg);
    QLabel::leaveEvent(event);//让进入事件回归到父类
}

//鼠标点击事件
 void customLabel::mousePressEvent(QMouseEvent * event)
 {
    qDebug()<<"选择新的头像";
    QString filter = "Image File( *.png *.jpg *.jpeg *.gif)";   //筛选
    QString fileName =  QFileDialog::getOpenFileName(this, "选择新头像","", filter );//对话框
    setHeadImage(fileName);
    //让进入事件回归到父类
    QLabel::mousePressEvent(event);
 }
