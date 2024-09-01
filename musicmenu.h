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
#include <QStringListModel>
#include <QStringList>//歌曲清单
#include "clientsocket.h"
#include <QCloseEvent>
#include <QStack>
#include "stdShared.h"
#include <QBuffer>
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

enum COLLECTMODE
{
    NO_COLLECT,
    COLLECT,
    COLLECT_MODE_MAX,
};
enum MusicType
{
    Local,
    Online,
    Favorite,
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
    void displaySongs(const QVector<QString> &songs);// 显示歌曲
    void writeSettings();
    void readSettings();
    QListWidgetItem* findLyricItemByTimestamp(quint32 timestamp);
private:

    Ui::MusicMenu *ui;
    QMediaPlayer * m_player;

    bool m_isPlay;//是否在播放
    MusicType m_currentType; // 用于记录当前显示的歌曲类型
    int m_currentPlayMode;//当前播放模式

    QVector<QString> m_modeIcons;//切换模式图标

    bool m_isCollected; // 记录收藏状态

    int m_currentSongRow;//当前播放音乐在歌单里是哪一行
    int m_backupLastSongRow;//维护上一首歌在歌曲的行数

     QString m_musicPath;//文件夹路径
    //保留上一次退出的歌曲名
     QString m_currentSongName;
     //歌词信息<时间，歌词>
    QMap<quint32,QString> m_lyricInfo;
    //定时器-检测position位置的歌词
    QTimer * m_timer;
    bool m_showLyrics;//选择显示歌词

    QCompleter * m_complete;//搜索补全
    QStringListModel *m_songListModel;

    ClientSocket * m_clientInfo;

    QStack<int> m_historyStack;//历史记录

    QVector<QString> m_allSongs; // 保存所有歌曲
    QVector<QString> m_favoriteSongs; // 保存喜爱歌曲
    QVector<QString> m_onlineSongs;//保存在线歌曲


    QString m_musicName;    // 用于存储音乐名称
    QByteArray m_musicData; // 用于存储音乐数据
    QBuffer *m_buffer;
    bool ismultiple;  // 是否批量下载
    bool readsetting;//读一次设置
    bool onlinecache;//在线记忆修复






private slots:
    void handlePrevSlot();
    void handlePlaySlot();
    void handleNextSlot();
    void handleSwitchModeSlot();
    void handleVolumeSlot();
    void handleLyricSlot();
    void handleCollectSlot();
    void handleSearchSlot();//搜歌
    void handleDownloadSlot();//下载
    void handleMultipleSlot(bool checked);//多选

    void handleDurationSlot(qint64 duration);//处理进度条长度
    void handlePositionSlot(qint64 position);//处理进度条进度
    void handleTimeoutSlot();//处理定时器超时
    void handleStateChangeSlot();//音乐状态改变
    void handleDoubleClickSlot(QListWidgetItem *item);//双击
    void handleDataSlot(const QByteArray & data);//接收音乐数据
    void handleLyricdataSlot(const QByteArray & data);//接收歌词数据
    void handleOnlineListSlot(const QByteArray & data);//接收音乐列表

    void handleLoveBtnSlot();// 点击喜爱按钮时显示喜爱歌曲
    void handleLocalBtnSlot();// 点击本地按钮时显示所有歌曲
    void handleOnlineBtnSlot();// 点击在线按钮时显示在线歌曲
    void handleVolumeChange(int value);//音量滑块
private:
    void setInitButtonIcon();
    //解析时间
    int parseTime(const QString & time);


};

#endif // MUSICMENU_H
