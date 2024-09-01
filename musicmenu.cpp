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
#include <QJsonObject>
#include <QJsonDocument>
#include <QBuffer>
#include <QSettings>
#include <QJsonArray>


#define timer_set 500
#define min_volume 0
#define max_volume 100
#define set_vloume 50

MusicMenu::MusicMenu(ClientSocket * cilentInfo,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicMenu),
    m_player(new QMediaPlayer(this)),
    m_isPlay(false),
    m_currentType(Local),
    m_currentPlayMode(ORDER_MODE),
    m_isCollected(false),
    m_currentSongRow(0),
    m_backupLastSongRow(0),
    m_timer(new QTimer(this)),
    m_showLyrics(false),
    m_clientInfo(cilentInfo),
    m_buffer(nullptr),
    ismultiple(false),
    readsetting(true),
    onlinecache(true)

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
    connect(ui->searchBtn,&QPushButton::clicked,this,&MusicMenu::handleSearchSlot);
    connect(ui->downloadBtn,&QPushButton::clicked,this,&MusicMenu::handleDownloadSlot);
    connect(ui->radioBtn,&QRadioButton::toggled,this,&MusicMenu::handleMultipleSlot);

    connect(m_player,&QMediaPlayer::durationChanged,this,&MusicMenu::handleDurationSlot);
    connect(m_player,&QMediaPlayer::positionChanged,this,&MusicMenu::handlePositionSlot);
    connect(m_player,&QMediaPlayer::stateChanged,this,&MusicMenu::handleStateChangeSlot);
    connect(ui->processBar,&QSlider::sliderMoved,m_player,&QMediaPlayer::setPosition);
    connect(ui->musicList, &QListWidget::itemDoubleClicked, this, &MusicMenu::handleDoubleClickSlot);
    connect(m_clientInfo,&ClientSocket::dataReceived,this,&MusicMenu::handleDataSlot);
    connect(m_clientInfo,&ClientSocket::dataReceived,this,&MusicMenu::handleLyricdataSlot);
    connect(m_clientInfo,&ClientSocket::dataReceived,this,&MusicMenu::handleOnlineListSlot);

    connect(ui->loveBtn, &QPushButton::clicked, this, &MusicMenu::handleLoveBtnSlot);
    connect(ui->localBtn, &QPushButton::clicked, this, &MusicMenu::handleLocalBtnSlot);
    connect(ui->onlineBtn, &QPushButton::clicked, this, &MusicMenu::handleOnlineBtnSlot);
    connect(m_timer,&QTimer::timeout,this,&MusicMenu::handleTimeoutSlot);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MusicMenu::handleVolumeChange);



//    //初始化加载第一首歌
//    ui->musicList->setCurrentRow(m_currentSongRow);
//    m_currentSongName = "七里香 - 周杰伦.mp3";
//    m_player->setMedia(QUrl::fromLocalFile(m_musicPath + m_currentSongName));
//    QString m_currentSongName = "七里香 - 周杰伦.lrc";
//    loadAppointLyricPath(m_musicPath + m_currentSongName);
//    //定时器
    ui->lyricLabel->hide();
    ui->downloadBtn->hide();
    ui->radioBtn->hide();
    m_timer->setInterval(timer_set);

    ui->searchMusic->setPlaceholderText("搜索音乐");//设置占位符
    ui->volumeSlider->setVisible(false); // 默认隐藏音量调整

    //音量初始化
    ui->volumeSlider->setRange(min_volume, max_volume);
    ui->volumeSlider->setValue(set_vloume);

    //在线列表
    qDebug()<<"在线列表"<<endl;
    //创建json对象
    QJsonObject jsonObj;
    //设置keyvalue
    jsonObj["type"] = ONLINE_LIST;
    jsonObj["musicname"] = "allname";
    //创建document对象
    QJsonDocument document(jsonObj);
    //发送信息到服务器
    m_clientInfo->writeData(document.toJson());

}

void MusicMenu::handleMultipleSlot(bool checked)//多选
{
       ismultiple = checked;
}

void MusicMenu::handleDownloadSlot()
{
    qDebug() << "下载音乐" << endl;

    if (m_musicName.isEmpty() || m_musicData.isEmpty())
    {
        qDebug() << "No music data available for download." << endl;
        return;
    }

    QString filepath = "D:\\下载\\music\\" + m_musicName + ".mp3";
    QFile file(filepath);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(m_buffer->data());
        file.flush();
        file.close();
        qDebug() << "Music saved successfully.";
        QMessageBox::information(this,"下载","下载成功");
    }
    else
    {
        qDebug() << "Failed to open the file for writing." << endl;
        QMessageBox::information(this,"下载","下载失败");
    }


}

void MusicMenu::handleOnlineListSlot(const QByteArray &data)
{
    // 解析 JSON 数据
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        qCritical() << "JSON parsing error:" << jsonError.errorString();
        return;
    }

    if (!doc.isObject())
    {
        qCritical() << "Expected JSON object";
        return;
    }

    QJsonObject responseObj = doc.object();
    int type = responseObj["type"].toInt();
    if (type == ONLINE_LIST)
    {
        QJsonArray musicNamesArray = responseObj["musicnames"].toArray();

        // 清空现有的歌曲列表
        m_onlineSongs.clear();

        // 将歌曲名添加到向量中
        for (const QJsonValue &val : musicNamesArray)
        {
            if (val.isString())
            {
                QString songName = val.toString();
                m_onlineSongs.append(songName);
            }
        }

        // 输出歌曲名列表
        qDebug() << "Received song names:";
        for (const QString &songName : m_onlineSongs)
        {
            qDebug() << songName;
        }
    }
    else
    {
        qCritical() << "Invalid request type";
    }
    //补全器在接受在线列表时更新
    // 将 QVector<QString> 转换为 QStringList
    QStringList songList = QStringList::fromVector(m_onlineSongs);

    // 创建一个 QStringListModel 对象
    m_songListModel = new QStringListModel(songList, this);

    // 创建 QCompleter 对象，并将模型设置为 m_songListModel
    m_complete = new QCompleter(m_songListModel, this);
    m_complete->setCompletionMode(QCompleter::PopupCompletion);

    // 将补全器设置到搜索框
    ui->searchMusic->setCompleter(m_complete);
    if(readsetting)//确保只记忆一次
    {
       readSettings();
       readsetting=!readsetting;
    }


}

void MusicMenu::writeSettings()
{
    QSettings settings("Qt", "musicPlayer");
    // 保存当前播放状态
    settings.beginGroup("PlayerState");
    // 保存当前模式（本地、在线、收藏）
    settings.setValue("playMode", static_cast<int>(m_currentType));  // 将枚举类型转换为整数存储
    settings.setValue("player_position", m_player->position());
     QString songName = ui->musicList->currentItem()->text();
     settings.setValue("player_name", songName);
    qDebug()<<settings.value("player_name")<<endl;
    qDebug()<<settings.value("player_position")<<endl;
}

void MusicMenu::readSettings()
{
    QSettings settings("Qt", "musicPlayer");
    // 恢复保存的播放状态
    settings.beginGroup("PlayerState");
    // 读取当前模式并转换为枚举类型
    int savedMode = settings.value("playMode", static_cast<int>(Local)).toInt();
    m_currentType = static_cast<MusicType>(savedMode);
    // 读取播放器位置和歌曲名称
    qint64 position = settings.value("player_position", 0).toLongLong();
    QString songName = settings.value("player_name", "").toString();
    // 根据保存的模式和歌曲名称恢复相应的状态
    if(m_currentType==Local)
    {
        handleLocalBtnSlot();
        m_player->setMedia(QUrl::fromLocalFile(m_musicPath + songName +".mp3"));
        loadAppointLyricPath(m_musicPath + songName +".lrc");
        m_player->setPosition(position);
        int restoredIndex = m_allSongs.indexOf(songName);
        if (restoredIndex != -1)
        {
            ui->musicList->setCurrentRow(restoredIndex); // 恢复找到的索引
        }
        else
        {
            ui->musicList->setCurrentRow(0); // 如果没有找到，默认选中第一首
        }
    }
    else if (m_currentType==Favorite)
    {

        handleLoveBtnSlot();
        m_player->setMedia(QUrl::fromLocalFile(m_musicPath + songName +".mp3"));
        loadAppointLyricPath(m_musicPath + songName +".lrc");
        m_player->setPosition(position);
        int restoredIndex = m_favoriteSongs.indexOf(songName);
        if (restoredIndex != -1)
        {
            ui->musicList->setCurrentRow(restoredIndex); // 恢复找到的索引
        }
        else
        {
            ui->musicList->setCurrentRow(0); // 如果没有找到，默认选中第一首
        }
    }
    else if (m_currentType==Online)
    {
        handleOnlineBtnSlot();
        QString searchmusic = songName;
        ui->searchMusic->setText(searchmusic);
        handleSearchSlot();
        ui->searchMusic->clear();
        int restoredIndex = m_onlineSongs.indexOf(songName);
        if (restoredIndex != -1)
        {
            ui->musicList->setCurrentRow(restoredIndex); // 恢复找到的索引
        }
        else
        {
            ui->musicList->setCurrentRow(0); // 如果没有找到，默认选中第一首
        }

    }
    else
    {
        qDebug()<<"no setting"<<endl;
        return;
    }

    settings.endGroup();
    m_player->setPosition(position);
    handlePlaySlot();//播放音乐
}
//音量
void MusicMenu::handleVolumeChange(int value)
{
    // 设置音量的范围从 0 到 100
    m_player->setVolume(value);
}
// 显示指定的歌曲列表
void MusicMenu::displaySongs(const QVector<QString> &songs)
{
    ui->musicList->clear(); // 清空列表
    for (const QString &song : songs)
    {
        ui->musicList->addItem(song);
    }
}
// 点击喜爱按钮时显示喜爱歌曲
void MusicMenu::handleLoveBtnSlot()
{
    m_currentType = Favorite;
    ui->downloadBtn->hide();
    ui->radioBtn->hide();
    loadAppointMusicPath(m_musicPath);
    displaySongs(m_favoriteSongs); // 切换到喜爱的歌曲列表

    ui->musicList->setCurrentRow(0);
//    // 保存当前播放歌曲的名称和索引
//    QString currentSongName = ui->musicList->currentItem()->text();
//    // 切换后恢复之前的播放状态
//    int restoredIndex = m_favoriteSongs.indexOf(currentSongName);
//    if (restoredIndex != -1)
//    {
//        ui->musicList->setCurrentRow(restoredIndex);
//    }
//    else
//    {
//        ui->musicList->setCurrentRow(0); // 如果没有找到，默认选中第一首
//    }

}
// 点击本地按钮时显示所有歌曲
void MusicMenu::handleLocalBtnSlot()
{
    m_currentType = Local;
    ui->downloadBtn->hide();
    ui->radioBtn->hide();
    loadAppointMusicPath(m_musicPath);
    displaySongs(m_allSongs); // 切换到本地所有歌曲列表
    ui->musicList->setCurrentRow(0);
//    // 保存当前播放歌曲的名称和索引
//    QString currentSongName = ui->musicList->currentItem()->text();
//    // 切换后恢复之前的播放状态
//    int restoredIndex = m_allSongs.indexOf(currentSongName);
//    if (restoredIndex != -1)
//    {
//        ui->musicList->setCurrentRow(restoredIndex);
//    }
//    else
//    {
//        ui->musicList->setCurrentRow(0); // 如果没有找到，默认选中第一首
//    }

}
// 点击在线按钮时搜索并显示在线歌曲
void MusicMenu::handleOnlineBtnSlot()
{
    m_currentType = Online;
    ui->downloadBtn->show();
    ui->radioBtn->show();
    displaySongs(m_onlineSongs); // 切换到在线所有歌曲列表
    ui->musicList->setCurrentRow(0);

}

void MusicMenu::handleDataSlot(const QByteArray & data)//接收在线音乐数据
{
    QSettings settings("Qt", "musicPlayer");
    // 恢复保存的播放状态
    settings.beginGroup("PlayerState");
    // 读取播放器位置
    qint64 position = settings.value("player_position", 0).toLongLong();

    qDebug() << "online music" << endl;
    // 1. 解析 JSON 字符串
    QJsonDocument document = QJsonDocument::fromJson(data);
    if (!document.isObject())
    {
        qDebug() << "document parse is not object" << endl;
        return;
    }
    // 2. 将 document 对象转成 JSON 对象
    QJsonObject jsonObj = document.object();
    // 3. 取值
    int type = jsonObj["type"].toInt();
    if (type == SEARCH_MUSIC)
    {
        qDebug() << "ready to play" << endl;
        m_musicName = jsonObj["musicname"].toString();  // 存储音乐名称
        QString musicData = jsonObj["musiccontent"].toString();
        m_musicData = QByteArray::fromBase64(musicData.toUtf8()); // 存储音乐数据
        m_buffer = new QBuffer(this);
        m_buffer->setData(m_musicData);
        if (!m_buffer->open(QIODevice::ReadOnly))
        {
            qDebug() << "online music error" << endl;
            delete m_buffer;
            return;
        }
        m_player->setMedia(QMediaContent(), m_buffer);
        if(onlinecache)
        {
           m_player->setPosition(position);
           onlinecache=!onlinecache;
        }
        m_player->play();

    }
}

void MusicMenu::handleLyricdataSlot(const QByteArray & data)//接收在线歌词数据
{
    qDebug()<<"online lyric"<<endl;
    //1.解析json字符串
    QJsonDocument document = QJsonDocument::fromJson(data);
    if(document.isObject()==false)
    {
        qDebug()<<"document parse is not object"<<endl;
        return;
    }
    //2.将document对象转成json对象
    QJsonObject jsonObj = document.object();
    //3.取值
    int type = jsonObj["type"].toInt();
    if(type ==SEARCH_LYRIC)
    {
        qDebug()<<"ready to lyric"<<endl;
        QString lyricName = jsonObj["lyricname"].toString();
        QString lyricData = jsonObj["lyriccontent"].toString();
        QByteArray data = QByteArray::fromBase64(lyricData.toUtf8());

        // 创建一个文件对象
        QFile file(QString("D:\\下载\\music\\%1.lrc").arg(lyricName));

        // 打开文件用于写入
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // 将 QByteArray 写入文件
            file.write(data);
            // 确保所有数据都被写入
            file.flush();
            // 关闭文件
            file.close();
            qDebug() << "Lyric saved successfully.";
        }
        else
        {
            qDebug() << "Failed to open the file for writing.";
        }
        loadAppointLyricPath(QString("D:\\下载\\music\\%1.lrc").arg(lyricName));
    }


}

void MusicMenu::handleSearchSlot()//搜索(音乐，歌词)
{
    qDebug()<<"在线音乐"<<endl;
    QString searchmusic = ui->searchMusic->text();
    //创建json对象
    QJsonObject jsonObj1;
    //设置keyvalue
    jsonObj1["type"] = SEARCH_MUSIC;
    jsonObj1["musicname"] = searchmusic;
    //创建document对象
    QJsonDocument document1(jsonObj1);
    //发送信息到服务器
    m_clientInfo->writeData(document1.toJson());
    qDebug()<<"在线歌词"<<endl;
    QString searchlyric = ui->searchMusic->text();
    //创建json对象
    QJsonObject jsonObj2;
    //设置keyvalue
    jsonObj2["type"] = SEARCH_LYRIC;
    jsonObj2["lyricname"] = searchlyric;
    //创建document对象
    QJsonDocument document2(jsonObj2);
    //发送信息到服务器
    m_clientInfo->writeData(document2.toJson());
}

void MusicMenu::closeEvent(QCloseEvent *event)//关闭事件
{
    // 检查当前列表是否为空
    if (ui->musicList->count() == 0)
    {
        QMessageBox::information(this,"关闭","关闭窗口");
        return;
    }
     writeSettings();

    QWidget::closeEvent(event);
    QMessageBox::information(this,"关闭","关闭窗口");
}

void MusicMenu::handleDoubleClickSlot(QListWidgetItem *item)
{
    // 设置当前选中的行
    ui->musicList->setCurrentItem(item);
    if(m_currentType==Online)
    {
        QString searchmusic = ui->musicList->currentItem()->text();
        ui->searchMusic->setText(searchmusic);
        handleSearchSlot();
        startAppointMusic();
//        handlePlaySlot();
        ui->searchMusic->clear();
        return;
    }

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

// 辅助函数：根据时间戳找到对应的歌词项
QListWidgetItem* MusicMenu::findLyricItemByTimestamp(quint32 timestamp)
{
    // 遍历 lyricWidget 中的所有项，查找时间戳与给定时间戳相等的项
    for (int i = 0; i < ui->lyricWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->lyricWidget->item(i);
        if (item->data(Qt::UserRole).toUInt() == timestamp)
        {
            return item;
        }
    }
    return nullptr;
}

void MusicMenu::handleTimeoutSlot()
{
    int currentPos = m_player->position();
    quint32 currentPosUnsigned = static_cast<quint32>(currentPos);
    QListWidgetItem *currentItem = nullptr;

    // 寻找当前播放位置所在的区间
    for (auto iter = m_lyricInfo.begin(); iter != m_lyricInfo.end(); ++iter)
    {
        quint32 prevPos = iter.key();

        // 检查是否是最后一个元素
        if (iter + 1 == m_lyricInfo.end())
        {
            if (prevPos <= currentPosUnsigned)
            {
                ui->lyricLabel->setText(iter.value());
                currentItem = findLyricItemByTimestamp(iter.key());
                break;
            }
        }
        else
        {
            quint32 nextPos = (iter + 1).key();
            if (prevPos <= currentPosUnsigned && currentPosUnsigned < nextPos)
            {
                ui->lyricLabel->setText(iter.value());
                currentItem = findLyricItemByTimestamp(iter.key());
                break;
            }
        }
    }

    // 高亮当前歌词项并滚动到视图中心
    if (currentItem)
    {
        ui->lyricWidget->setCurrentItem(currentItem);
        ui->lyricWidget->scrollToItem(currentItem, QAbstractItemView::PositionAtCenter);
        currentItem->setSelected(true);
    }
}

//加载歌词
void MusicMenu::loadAppointLyricPath(const QString &filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly))
    {
//        QMessageBox::warning(this, "歌词文件", "文件不存在");
        return;
    }
    ui->lyricWidget->clear();
    ui->lyricLabel->clear();
    char buffer[128] = {0};

    while (!file.atEnd())
    {
        file.readLine(buffer, sizeof(buffer));
        QString lineData(buffer);

        QStringList listInfo = lineData.split("]");
        if (listInfo.size() > 1)
        {
            int lyricTime = parseTime(listInfo[0].split("[")[1]); // 字符串时间转换(毫秒)
            QString lyric = listInfo[1].trimmed(); // 去除前后空格
            m_lyricInfo[lyricTime] = lyric;

            // 插入歌词项并存储时间戳
            QListWidgetItem *item = new QListWidgetItem(lyric, ui->lyricWidget);
            item->setData(Qt::UserRole, lyricTime);
        }

        memset(buffer, 0, sizeof(buffer));
    }

    file.close();
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
     // 清空歌曲列表
     m_allSongs.clear();
     m_favoriteSongs.clear();

     // 循环查找所有歌曲
     for (const QFileInfo &info : fileinfo)
     {
         if (info.suffix() == "mp3") // 后缀
         {
             QString songName = info.baseName();
             m_allSongs.push_back(songName); // 添加到所有歌曲列表

             // 检查是否为喜爱歌曲
             QSettings settings("FavoriteMusic", "Favorites");
             if (settings.value(songName, false).toBool())
             {
                 m_favoriteSongs.push_back(songName); // 添加到喜爱歌曲列表
             }
         }
     }

     // 显示所有歌曲
     displaySongs(m_allSongs);
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

    QIcon downloadIcon(":/Icon/downloadIcon.png");
    ui->downloadBtn->setIcon(downloadIcon);
    ui->downloadBtn->setIconSize(QSize(40,40));
    ui->downloadBtn->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0)}");

    m_modeIcons.push_back(":/Icon/circulate.png");
    m_modeIcons.push_back(":/Icon/Single.png");
    m_modeIcons.push_back(":/Icon/random.png");




}

void MusicMenu::handlePrevSlot()
{
    // 检查当前列表是否为空
    if (ui->musicList->count() == 0)
    {
        QMessageBox::information(this, "提示", "没有可播放的歌曲。");
        return;
    }

    int nextRow = 0;

      if (!m_historyStack.isEmpty())
      {
          // 从历史栈中获取上一首歌曲的行号
          nextRow = m_historyStack.pop();
      }
      else
      {
          // 栈为空时执行正常逻辑
          int currentRow = ui->musicList->currentRow();
          if (m_currentPlayMode == ORDER_MODE) // 顺序播放
          {
              if (currentRow == 0) {
                  nextRow = (ui->musicList->count() - 1);
              } else {
                  nextRow = (currentRow - 1);
              }
          }
          else if (m_currentPlayMode == CYCLE_MODE) // 循环播放
          {
              nextRow = currentRow;
          }
          else if (m_currentPlayMode == RANDOM_MODE) // 随机播放
          {
              nextRow = m_backupLastSongRow;
          }
      }

      ui->musicList->setCurrentRow(nextRow);
      if(m_currentType==Online)
      {
          QString searchmusic = ui->musicList->currentItem()->text();
          ui->searchMusic->setText(searchmusic);
          handleSearchSlot();
          startAppointMusic();
          ui->searchMusic->clear();
          return;
      }
      startAppointMusic(); // 播放指定音乐
}

void MusicMenu::handlePlaySlot()
{
    // 检查当前列表是否为空
    if (ui->musicList->count() == 0)
    {
        QMessageBox::information(this, "提示", "没有可播放的歌曲。");
        return;
    }
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
    // 检查当前列表是否为空
    if (ui->musicList->count() == 0) {
        QMessageBox::information(this, "提示", "没有可播放的歌曲。");
        return;
    }

   //播放列表当前行
    int currentRow = ui->musicList->currentRow();
    m_backupLastSongRow = currentRow;

    // 保存当前行到历史栈中
    if (!m_historyStack.isEmpty() && m_historyStack.top() == currentRow)
    {
        m_historyStack.pop();
    }
    m_historyStack.push(currentRow);
    if (m_historyStack.size() > 10)
    {
        m_historyStack.remove(0);  // 保持栈大小为10
    }



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
    if(m_currentType==Online)
    {
        QString searchmusic = ui->musicList->currentItem()->text();
        ui->searchMusic->setText(searchmusic);
        handleSearchSlot();
        startAppointMusic();
//        handlePlaySlot();
        ui->searchMusic->clear();
        return;
    }

    //播放指定音乐
    startAppointMusic();

}

void MusicMenu::startAppointMusic()//播放指定音乐
{
    QString songname = ui->musicList->currentItem()->text();

    // 使用 QSettings 加载喜爱状态
    QSettings collect_settings("FavoriteMusic", "Favorites");
    m_isCollected = collect_settings.value(songname, false).toBool(); // 默认值为 false
    // 根据喜爱状态设置按钮图标
    if (m_isCollected)
    {
        ui->collectBtn->setIcon(QIcon(":/Icon/collect.png")); // 收藏状态
    }
    else
    {
        ui->collectBtn->setIcon(QIcon(":/Icon/no_collect.png")); // 未收藏状态
    }


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
    //添加音量调整功能
    ui->volumeSlider->setVisible(!ui->volumeSlider->isVisible());
}

void MusicMenu::handleLyricSlot()
{
    // 切换歌词显示状态
    m_showLyrics = !m_showLyrics;

    if (m_showLyrics)
    {

        ui->lyricWidget->hide();
    }
    else
    {
        ui->lyricWidget->show();
    }
}

void MusicMenu::handleCollectSlot()//喜爱音乐
{
    // 检查当前列表是否为空
    if (ui->musicList->count() == 0) {
        QMessageBox::information(this, "提示", "无法收藏。");
        return;
    }
    // 切换收藏状态
    m_isCollected = !m_isCollected;

    // 获取当前歌曲名
    QString songName = ui->musicList->currentItem()->text();

    // 使用 QSettings 保存喜爱状态
    QSettings settings("FavoriteMusic", "Favorites");
    settings.setValue(songName, m_isCollected);

    // 更新收藏按钮图标
    if (m_isCollected)
    {
        ui->collectBtn->setIcon(QIcon(":/Icon/collect.png")); // 收藏状态
        // 添加到喜爱列表
        if (!m_favoriteSongs.contains(songName))
        {
            m_favoriteSongs.push_back(songName);
        }
    }
    else
    {
        ui->collectBtn->setIcon(QIcon(":/Icon/no_collect.png")); // 未收藏状态
        // 从喜爱列表中移除
        m_favoriteSongs.removeAll(songName);
    }

    // 刷新当前显示的喜爱歌曲列表，如果在喜爱列表界面
    if (ui->loveBtn->isChecked())
    {
        displaySongs(m_favoriteSongs);
    }

}


MusicMenu::~MusicMenu()
{
    delete ui;
}
