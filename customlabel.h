#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QFileDialog>
class customLabel : public QLabel
{
    Q_OBJECT
public:
    explicit customLabel(QWidget *parent = nullptr);
    //设置头像
    void setHeadImage(const QString & fileName);
public:
    //鼠标进入事件
    void enterEvent(QEvent * event) override;

    //鼠标离开事件
    void leaveEvent(QEvent * event) override;

    //鼠标点击事件
    void mousePressEvent(QMouseEvent * event) override;
private:
    QString m_backupHeadImg;
signals:

};

#endif // CUSTOMLABEL_H
