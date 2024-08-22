#ifndef MUSICMENU_H
#define MUSICMENU_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVector>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QListWidgetItem>
#include <QCompleter> //补全
#include <QStringList>//歌曲清单
#include "clientsocket.h"
#include <QCloseEvent>
namespace Ui {
class MusicMenu;
}

enum PLAYMODE
{
    ORDER_MODE,
    CYCLE_MODE,
    RANDOM_MODE,
    PLAY_MODE_MAX,
};

class MusicMenu : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override;


public:
    explicit MusicMenu(ClientSocket * clientInfo,QWidget *parent = nullptr);
    ~MusicMenu();

    void setAlbumPic(const QPixmap & pixmap);
    void setAlbumPic(const QString & picfilename);
    //加载指定音乐路径
    void loadAppointMusicPath(const QString & filepath);
    //加载歌词
    void loadAppointLyricPath(const QString & filepath);
    void startAppointMusic();//播放指定音乐

private:
    Ui::MusicMenu *ui;
    QMediaPlayer * m_player;

    bool m_isPlay;//是否在播放

    int m_currentPlayMode;//当前播放模式

    QVector<QString> m_modeIcons;//切换模式图标

    int m_currentSongRow;//当前播放音乐在歌单里是哪一行
    int m_backupLastSongRow;//维护上一首歌在歌曲的行数  to do

     QString m_musicPath;//文件夹路径
    //保留上一次退出的歌曲名
     QString m_backupExitMusic;
     //歌词信息<时间，歌词>
    QMap<quint32,QString> m_lyricInfo;
    //定时器-检测position位置的歌词
    QTimer * m_timer;
    bool m_showLyrics;//选择显示歌词

    QCompleter * m_complete;//搜索补全

    ClientSocket * m_clientInfo;

private slots:
    void handlePrevSlot();
    void handlePlaySlot();
    void handleNextSlot();
    void handleSwitchModeSlot();
    void handleVolumeSlot();
    void handleLyricSlot();
    void handleCollectSlot();

    void handleDurationSlot(qint64 duration);//处理进度条长度
    void handlePositionSlot(qint64 position);//处理进度条进度
    void handleTimeoutSlot();//处理定时器超时
    void handleStateChangeSlot();//音乐状态改变
    void handleDoubleClickSlot(QListWidgetItem *item);//双击
private:
    void setInitButtonIcon();
    //解析时间
    int parseTime(const QString & time);

};

#endif // MUSICMENU_H
