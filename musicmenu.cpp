#include "musicmenu.h"
#include "ui_musicmenu.h"
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QUrl>
#include <QVector>
#include <QDir>
#include <QMessageBox>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSlider>
#include <QFile>
#include <string.h>

MusicMenu::MusicMenu(ClientSocket * cilentInfo,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicMenu),
    m_player(new QMediaPlayer(this)),
    m_isPlay(false),
    m_currentPlayMode(ORDER_MODE),
    m_currentSongRow(0),
    m_backupLastSongRow(0),
    m_timer(new QTimer(this)),
    m_showLyrics(false)

{
   ui->setupUi(this);
   m_lyricInfo.clear();//清空哈希表

   setInitButtonIcon();//设置初始按钮图标

   setAlbumPic(":/photo/3.jpg");//初始化头像
   //初始化路径
   m_musicPath = "D:\\下载\\music\\";
   loadAppointMusicPath(m_musicPath);

//信号和槽
    connect(ui->prevBtn,&QPushButton::clicked,this,&MusicMenu::handlePrevSlot);
    connect(ui->playBtn,&QPushButton::clicked,this,&MusicMenu::handlePlaySlot);
    connect(ui->nextBtn,&QPushButton::clicked,this,&MusicMenu::handleNextSlot);
    connect(ui->switchModeBtn,&QPushButton::clicked,this,&MusicMenu::handleSwitchModeSlot);
    connect(ui->volumeBtn,&QPushButton::clicked,this,&MusicMenu::handleVolumeSlot);
    connect(ui->post_lrc_Btn,&QPushButton::clicked,this,&MusicMenu::handleLyricSlot);
    connect(ui->collectBtn,&QPushButton::clicked,this,&MusicMenu::handleCollectSlot);
    connect(m_player,&QMediaPlayer::durationChanged,this,&MusicMenu::handleDurationSlot);
    connect(m_player,&QMediaPlayer::positionChanged,this,&MusicMenu::handlePositionSlot);
    connect(m_player,&QMediaPlayer::stateChanged,this,&MusicMenu::handleStateChangeSlot);
    connect(ui->processBar,&QSlider::sliderMoved,m_player,&QMediaPlayer::setPosition);
    connect(ui->musicList, &QListWidget::itemDoubleClicked, this, &MusicMenu::handleDoubleClickSlot);
    //初始化加载第一首歌
    ui->musicList->setCurrentRow(m_currentSongRow);
    m_backupExitMusic = "七里香.mp3";
    m_player->setMedia(QUrl::fromLocalFile(m_musicPath + m_backupExitMusic));
    QString m_backupExitMusic = "七里香.lrc";
    loadAppointLyricPath(m_musicPath + m_backupExitMusic);
    //定时器
    m_timer->setInterval(500);
    connect(m_timer,&QTimer::timeout,this,&MusicMenu::handleTimeoutSlot);

    ui->searchMusic->setPlaceholderText("搜索音乐");//设置占位符

    QStringList songList;

    songList.push_back("爱如潮水");
    songList.push_back("爱情转移");
    songList.push_back("无名的人");
    songList.push_back("朋友的酒");
    songList.push_back("我怀念的");

    m_complete = new QCompleter(songList,this);
    //弹出匹配项
    m_complete->setCompletionMode(QCompleter::PopupCompletion);
    //将补全器设置到搜索框
    ui->searchMusic->setCompleter(m_complete);



}
void MusicMenu::closeEvent(QCloseEvent *event)//关闭事件
{
    QMessageBox::information(this,"关闭","关闭窗口");
    //to do 记录数据
}
void MusicMenu::handleDoubleClickSlot(QListWidgetItem *item)
{
    // 设置当前选中的行
    ui->musicList->setCurrentItem(item);

    // 播放指定的歌曲
    startAppointMusic();

}

void MusicMenu::handleStateChangeSlot()//音乐状态改变(播完放下一首)
{
    if(m_player->state()==QMediaPlayer::StoppedState && m_player->position()!=0)
    {
        handleNextSlot();//播放下一首
    }

}

void MusicMenu::handleTimeoutSlot()//处理定时器超时
{
    //获取当前歌曲的位置
    int currentPos = m_player->position();
    for (auto iter = m_lyricInfo.begin();iter!=m_lyricInfo.end();iter++)
    {
        int prevPos = iter.key();
        int nextPos = (iter+1).key();
        if(prevPos<currentPos && currentPos<nextPos)
        {
            ui->lyricLabel->setText(iter.value());
            break;
        }
    }
}
//解析时间(毫秒)
int MusicMenu::parseTime(const QString & time)
{
    int minutes = time.split(':')[0].toUInt();
    int seconds = time.split(":")[1].split(".")[0].toUInt();
    int millsecond = time.split(".")[1].toUInt();
    int totalMills = minutes * 60 * 1000 + seconds * 1000 + millsecond;
    return totalMills;
}
//加载歌词
void MusicMenu::loadAppointLyricPath(const QString & filepath)
{
    QFile file(filepath);

    if(file.open(QIODevice::ReadOnly) ==false)
    {
        QMessageBox::warning(this, "歌词文件","文件不存在");
        return;
    }
    char buffer[128] ={0};

    while (!file.atEnd())
    {
        file.readLine(buffer,sizeof(buffer));

        QString LineData(buffer);

        QStringList listinfo = LineData.split("]");

        int lyricTime = parseTime(listinfo[0].split("[")[1]);//字符串时间转换(毫秒)
        //插入哈希表
        QString lyric = listinfo[1];
        m_lyricInfo[lyricTime] = lyric;
        memset(buffer,0,sizeof(buffer));
    }
    file.close();
}
// 加载指定音乐路径
void MusicMenu::loadAppointMusicPath(const QString & filepath)
 {
     QDir dir(filepath);
     if(dir.exists() == false)
     {
         QMessageBox::warning(this,"打开文件夹","文件夹不存在");
        return;
     }

     QFileInfoList fileinfo = dir.entryInfoList(QDir::Files);
    //循环查找
     for(const QFileInfo & info : fileinfo)
     {
        if(info.suffix()=="mp3")//后缀
        {
            qDebug()<<"info.fileName():"<< info.baseName()<<endl;
            ui->musicList->addItem(info.baseName());
        }
     }
 }

void MusicMenu::handlePositionSlot(qint64 position)
{
    if(position>0)
    {
    int minutes = position /1000/60;
    int seconds = position /1000%60;

    QString formatStr = "%1:%2";
    QString currentTime = formatStr.arg(minutes,2,10,QChar('0')).arg(seconds,2,10,QChar('0'));
    ui->currentTime->setText(currentTime);
    //更新进度条
    ui->processBar->setValue(position);
    }
}

void MusicMenu::handleDurationSlot(qint64 duration)//处理进度条长度
{
    if(duration>0)
    {
        int minutes = duration /1000/60;
        int seconds = duration /1000%60;

        QString formatStr = "%1:%2";
        QString totalTime = formatStr.arg(minutes).arg(seconds);
        ui->totalTime->setText(totalTime);
        //更新进度条最大值
        ui->processBar->setRange(0,duration);

        qDebug()<<"dur"<<duration<<endl;
    }
}

void MusicMenu::setAlbumPic(const QPixmap & pixmap)
{
    ui->albumLabel->setPixmap(pixmap.scaled(ui->albumLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MusicMenu::setAlbumPic(const QString & picfilename)
{
    QPixmap headPic(picfilename);
    setAlbumPic(headPic);
}

void MusicMenu::setInitButtonIcon()
{
    QIcon prevIcon(":/Icon/prevIcon.png");
    ui->prevBtn->setIcon(prevIcon);
    ui->prevBtn->setIconSize(QSize(40,40));
    ui->prevBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");


    QIcon playIcon(":/Icon/playIcon.png");
    ui->playBtn->setIcon(playIcon);
    ui->playBtn->setIconSize(QSize(40,40));
    ui->playBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    QIcon nextIcon(":/Icon/nextIcon.png");
    ui->nextBtn->setIcon(nextIcon);
    ui->nextBtn->setIconSize(QSize(40,40));
    ui->nextBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    QIcon switchModeIcon(":/Icon/circulate.png");
    ui->switchModeBtn->setIcon(switchModeIcon);
    ui->switchModeBtn->setIconSize(QSize(40,40));
    ui->switchModeBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    QIcon volumeIcon(":/Icon/volune.png");
    ui->volumeBtn->setIcon(volumeIcon);
    ui->volumeBtn->setIconSize(QSize(40,40));
    ui->volumeBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    QIcon post_lrc_Icon(":/Icon/post_irc.png");
    ui->post_lrc_Btn->setIcon(post_lrc_Icon);
    ui->post_lrc_Btn->setIconSize(QSize(40,40));
    ui->post_lrc_Btn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    QIcon collectIcon(":/Icon/no_collect.png");
    ui->collectBtn->setIcon(collectIcon);
    ui->collectBtn->setIconSize(QSize(40,40));
    ui->collectBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");


    m_modeIcons.push_back(":/Icon/circulate.png");
    m_modeIcons.push_back(":/Icon/Single.png");
    m_modeIcons.push_back(":/Icon/random.png");


}

void MusicMenu::handlePrevSlot()
{
    //播放列表当前行
    int currentRow = ui->musicList->currentRow();
    int prevRow = m_backupLastSongRow;//维护上一首行数
    int nextRow = 0;
    if(m_currentPlayMode == ORDER_MODE)//顺序播放
    {
        if(currentRow==0)
        {
            nextRow = (ui->musicList->count()-1);
        }
        else
        {
           nextRow = (currentRow - 1 );
        }
    }
    else if(m_currentPlayMode == CYCLE_MODE)//循环播放
    {
         nextRow = currentRow;
    }
    else if(m_currentPlayMode == RANDOM_MODE)//随机播放
    {
        nextRow = prevRow;
    }
    ui->musicList->setCurrentRow(nextRow);


    // 播放指定音乐
    startAppointMusic();

}

void MusicMenu::handlePlaySlot()
{
#if 0
    if(m_isPlay ==false)
    {
        //播放
        m_player->play();
        ui->playBtn->setIcon(QIcon(":/Icon/pauseIcon.png"));
        m_isPlay = true;
    }
    else
    {
        //停止
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/Icon/playIcon.png"));
        m_isPlay = false;
    }

#else
    if(m_player->state() == QMediaPlayer::PlayingState)
    {
        //停止
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/Icon/playIcon.png"));
        //停止定时器
        m_timer->stop();
    }
    else
    {
        //播放
        m_player->play();
        ui->playBtn->setIcon(QIcon(":/Icon/pauseIcon.png"));
        //启动定时器
        m_timer->start();
    }


#endif

}

void MusicMenu::handleNextSlot()
{

   //播放列表当前行
    int currentRow = ui->musicList->currentRow();
    m_backupLastSongRow = currentRow;
    int nextRow = 0;
    if(m_currentPlayMode == ORDER_MODE)//顺序播放
    {
        nextRow = (currentRow + 1) % ui->musicList->count();
    }
    else if(m_currentPlayMode == CYCLE_MODE)//循环播放
    {
         nextRow = currentRow;
    }
    else if(m_currentPlayMode == RANDOM_MODE)//随机播放
    {
        do
        {
          nextRow = qrand() % ui->musicList->count();
        } while(currentRow == nextRow);

    }
    ui->musicList->setCurrentRow(nextRow);


    //播放指定音乐
    startAppointMusic();

}

void MusicMenu::startAppointMusic()//播放指定音乐
{
    QString songname = ui->musicList->currentItem()->text();
    qDebug()<<songname<<endl;
    QString absPathname = m_musicPath + songname + ".mp3";
    qDebug()<<absPathname<<endl;
    m_player->setMedia(QUrl::fromLocalFile(absPathname));
    handlePlaySlot();//播放音乐

    // 根据歌曲名加载歌词文件
    QString lyricFilename = songname + ".lrc";
    QString lyricPath = m_musicPath + lyricFilename;

    // 清除上次的歌词
    m_lyricInfo.clear();
    loadAppointLyricPath(lyricPath); // 加载新歌词
}

void MusicMenu::handleSwitchModeSlot()
{
    m_currentPlayMode = (m_currentPlayMode + 1) % PLAY_MODE_MAX;
    ui->switchModeBtn->setIcon(QIcon(m_modeIcons[m_currentPlayMode]));
}

void MusicMenu::handleVolumeSlot()
{

}

void MusicMenu::handleLyricSlot()
{
    // 切换显示状态
    m_showLyrics = !m_showLyrics;

    if (m_showLyrics)
    {
        ui->lyricLabel->show();
    }
    else
    {
        ui->lyricLabel->hide();
    }
}

void MusicMenu::handleCollectSlot()//喜爱音乐
{

}

MusicMenu::~MusicMenu()
{
    delete ui;
}
