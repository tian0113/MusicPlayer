#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QFileDialog>
#include<QDir>
#include<QMediaPlayer>
#include<QMediaContent>
#include<QPixmap>
#include<QPalette>
#include<QRandomGenerator>//获取随机数
#include<QPropertyAnimation>//动画效果
#include<QTimer>//定时器
#include<QTextEdit>
#include<QTextBlock>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,m_mode(ORDER_MODE)//切歌模式
    ,ps_mode(PLAY_MODE)//播放模式
    // ,ic_mode(SHOW_MODE)//列表模式
    ,m_isShowFlag(false)//列表状态
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //如何播放音乐，先加载模块multimedia
    //创建媒体播放对象
    mediaPlayer = new QMediaPlayer(this);

    //获取当前媒体的时长，通过信号槽获取
    connect(mediaPlayer,&QMediaPlayer::durationChanged,[=](qint64 duration){
        ui->totalLabel->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60));
        //设置进度条，跟随音乐进度自动移动
        ui->playCourseSlider->setRange(0,duration);
    });

    //获取当前播放时长
    connect(mediaPlayer,&QMediaPlayer::positionChanged,[=](qint64 pos){
        ui->curLabel->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));
        //设置进度条，跟随音乐进度自动移动
        ui->playCourseSlider->setValue(pos);
    });

    //设置进度条，移动滑块改变播放进度
    connect(ui->playCourseSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);

    //设置音量
    //初始化音量滑块
    ui->volumeSlider->setRange(0,100);
    ui->volumeSlider->setValue(30);
    mediaPlayer->setVolume(30);
    ui->volumeSlider->setVisible(false);

    //初始化音量标签
    ui->speedlabel_3->setText("100");
    ui->speedlabel_3->setVisible(false);
    ui->speedlabel_3->setStyleSheet("QLabel {"
                                  "font-family: Arial;" // 设置字体为 Arial
                                  "font-size: 14px;"    // 设置字体大小为 14 像素
                                  "font-weight: bold;"  // 设置字体为粗体
                                  "color: white;"       // 设置文本颜色为白色
                                  "background-color: rgba(0, 0, 0, 128);" // 设置背景颜色为半透明黑色
                                  "padding: 4px;"       // 设置内边距为 4 像素
                                  "border-radius: 5px;" // 设置圆角边框，半径为 5 像素
                                  "}");

    //为音量按钮和音量条安装事件过滤器
    ui->pushButton_6->installEventFilter(this);
    ui->volumeSlider->installEventFilter(this);

    //鼠标点击音量按钮关闭音量条
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        bool vis = ui->volumeSlider->isVisible();
        ui->volumeSlider->setVisible(!vis);
        ui->speedlabel_3->setVisible(!vis);
    });

    //设置倍速图标样式
    ui->pushButton_8->setIcon(QIcon(":/assets/speed.png"));

    //初始化倍速
    ui->speedSlider->setRange(50,150); // 范围为 25% 到 200%
    ui->speedSlider->setValue(100); // 初始值为 100%（即正常速度）
    ui->speedSlider->setSingleStep(5); // 每次滑动的步长为 5%

    //初始化倍速标签
    ui->speedlabel->setText("0.5X"); //最低速度
    ui->speedlabel_2->setText("1.5X");//最大速度

    //设置倍速标签样式
    ui->speedlabel->setStyleSheet("QLabel {"
                                    "font-family: Times New Roman;" // 设置字体为 Arial
                                    "font-size: 14px;"    // 设置字体大小为 14 像素
                                    "font-weight: bold;"  // 设置字体为粗体
                                    "color: white;"       // 设置文本颜色为白色
                                    "background-color: rgba(0, 0, 0, 128);" // 设置背景颜色为半透明黑色
                                    "padding: 4px;"       // 设置内边距为 4 像素
                                    "border-radius: 5px;" // 设置圆角边框，半径为 5 像素
                                    "}");
    ui->speedlabel_2->setStyleSheet("QLabel {"
                                    "font-family: Times New Roman;" // 设置字体为 Arial
                                    "font-size: 14px;"    // 设置字体大小为 14 像素
                                    "font-weight: bold;"  // 设置字体为粗体
                                    "color: white;"       // 设置文本颜色为白色
                                    "background-color: rgba(0, 0, 0, 128);" // 设置背景颜色为半透明黑色
                                    "padding: 4px;"       // 设置内边距为 4 像素
                                    "border-radius: 5px;" // 设置圆角边框，半径为 5 像素
                                    "}");

    //设置倍速按钮，不使用时隐藏音量条
    ui->speedSlider->setVisible(false);
    ui->speedlabel->setVisible(false);
    ui->speedlabel_2->setVisible(false);

    //设置倍速按钮，点击倍速时弹出倍速条
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        bool vis2 = ui->speedSlider->isVisible();
        ui->speedSlider->setVisible(!vis2);
        ui->speedlabel->setVisible(!vis2);
        ui->speedlabel_2->setVisible(!vis2);
    });

    //歌词
    //设置歌词显示图标样式表
    ui->pushButton_Lyrics->setIcon(QIcon(":/assets/showSong.png"));

    // 初始化歌词显示框
    ui->lyricsTextEdit->setReadOnly(true);
    ui->lyricsTextEdit->setGeometry(20, 90, 421, 251); // 设置歌词显示区域大小
    ui->lyricsTextEdit->setVisible(false); // 默认隐藏

    //歌词显示框样式表设置（背景颜色，透明度，字体，滚动条，阴影效果）
    ui->lyricsTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(10, 20, 50, 200), stop:1 rgba(5, 10, 30, 220));"  // 蓝黑渐变背景
        "   color: rgba(220, 220, 220, 220);"  // 浅灰色文字
        "   font-family: 'Microsoft YaHei', 'PingFang SC', 'Segoe UI', sans-serif;"  // 中文字体优先
        "   font-size: 18px;"  // 稍大字号
        "   padding: 20px 30px;"  // 更大的内边距
        "   border: 1px solid rgba(100, 150, 255, 50);"  // 浅蓝色半透明边框
        "   border-radius: 12px;"  // 更大的圆角
        "   selection-background-color: rgba(0, 150, 255, 150);"  // 选中文本背景色
        "   selection-color: white;"  // 选中文本颜色
        "}"
        );

    //禁止在歌词显示界面使用滚动条
    ui->lyricsTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lyricsTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 初始化歌词按钮,确保歌词按钮可见
    ui->pushButton_Lyrics->setVisible(true);

    //歌单
    //设置歌单显示界面样式表，使QListWidget背景透明
    //歌词显示框样式表设置（背景颜色，透明度，字体，滚动条，阴影效果）
    ui->listWidget->setStyleSheet(
        "QListWidget {"
        "   background-color: rgba(25, 30, 45, 220);"  // 深蓝灰半透明背景
        "   border: 1px solid rgba(255, 255, 255, 30);"  // 浅色半透明边框
        "   border-radius: 8px;"  // 圆角
        "   padding: 5px;"
        "   outline: 0;"  // 移除焦点边框
        "   font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;"
        "}"

        // 列表项默认样式
        "QListWidget::item {"
        "   background-color: transparent;"  // 透明背景
        "   color: rgb(50, 220, 220);"  // 浅灰色文字
        "   height: 36px;"  // 固定行高
        "   padding-left: 15px;"
        "   border-bottom: 1px solid rgba(255, 255, 255, 10);"  // 项间分隔线
        "   font-size: 14px;"
        "}"

        // 鼠标悬停样式
        "QListWidget::item:hover {"
        "   background-color: rgba(60, 140, 230, 80);"  // 浅蓝色悬停效果
        "   color: white;"
        "}"

        // 选中项样式
        "QListWidget::item:selected {"
        "   background-color: rgba(40, 110, 200, 150);"  // 蓝色选中背景
        "   color: white;"
        "   border-left: 3px solid rgb(0, 150, 255);"  // 左侧高亮条
        "}"
        );

    //设置歌单显示区域大小
    ui->listWidget->setGeometry(490,0,221,371);

    //设置歌单默认隐藏
    ui->listWidget->setVisible(false);

    //禁止在歌单显示界面使用滚动条
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //下载
    //设置下载按钮图标样式
    ui->pushButton_9->setIcon(QIcon(":/assets/Download.png"));

    //信号和槽函数
    //播放完当前歌曲后自动切换歌曲
    connect(mediaPlayer,&QMediaPlayer::mediaStatusChanged,[=](QMediaPlayer::MediaStatus status){
        //判断当前音乐是否播放完
        if(status == QMediaPlayer::EndOfMedia){
            //切换下一首歌曲
            on_pushButton_5_clicked();
        }
    });

    //设置切歌模式
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::handleModeSlot);

    //设置暂停&播放模式切换
    connect(ui->pushButton_4,&QPushButton::clicked,this,&Widget::PlayerIconSlot);

    //设置音乐播放列表
    connect(ui->pushButton_7,&QPushButton::clicked,this,&Widget::handleMusicListSlot);

    //设置音量条，移动滑块改变音量大小
    connect(ui->volumeSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setVolume);

    //设置倍速条，移动滑块改变播放速率
    connect(ui->speedSlider, &QSlider::valueChanged, this, &Widget::on_pushButton_8_clicked);

    //设置歌词显示
    connect(ui->pushButton_Lyrics,&QPushButton::clicked,this,&Widget::toggleLyrics);

    //设置播放器背景
    setBackGround(":/assets/BK2.png");

    //设置标题
    setWindowTitle("ty的音乐播放器");

    //设置窗口大小不变
    //setFixedSize(357,492);

    //初始化切歌模式
    ui->pushButton_2->setIcon(QIcon(":/assets/playlist_order.png"));

    //初始化播放暂停模式
    ui->pushButton_4->setIcon(QIcon(":/assets/pause.png"));

    //初始化列表按钮模式
    ui->pushButton_7->setIcon(QIcon(":/assets/close.png"));

    //设置随机数种子
    //srand(time(NULL));
    //改用Qt官方的获取随机数种子方法：QRandomGenerator::global()->bounded(playList.size());
}

Widget::~Widget()
{
    delete ui;
}

//打开文件夹
void Widget::on_pushButton_clicked()
{
    //qInfo()<<"Hello";
    //打开文件对话框，让用户选择音乐所在的目录
    auto path = QFileDialog::getExistingDirectory(
        this,"请选择音乐所在的目录","E:/QtCode/MusicPlayer/assets/music");
    //根据这个路径，获取里面的所有mp3,wav文件
    QDir dir(path);
    auto musicList = dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
    //把音乐文件放入到listWidget展示
    ui->listWidget->addItems(musicList);
    //默认选中第一个音乐
    ui->listWidget->setCurrentRow(0);
    //把音乐的完整路径保存
    for(auto file : musicList)
        playList.append(QUrl::fromLocalFile(path+"./"+file));
    qInfo()<<playList;

}

//播放音乐
void Widget::on_pushButton_4_clicked()
{
    //错误处理
    if(playList.empty()){
        return;
    }

    //获取播放状态
    switch(mediaPlayer->state()){
        case QMediaPlayer::StoppedState://停止状态
        {
            //获取选中的行号
            curPlayIndex = ui->listWidget->currentRow();
            //如果没有播放，那就就播放当前选中的音乐
            //播放对应下标的音乐
            mediaPlayer->setMedia(QMediaContent(playList[curPlayIndex]));
            mediaPlayer->play();
            break;
        }
        case QMediaPlayer::PlayingState://播放状态
        {
            //如果现在正在播放，那就暂停音乐
            mediaPlayer->pause();
            break;
        }

        case QMediaPlayer::PausedState://暂停状态
        {
            //如果现在是暂停状态，继续播放音乐
            mediaPlayer->play();
            break;
        }
    }
}

//上一曲
void Widget::on_pushButton_3_clicked()
{
    //判断播放列表是否为空
    if (playList.isEmpty()) return;

    curPlayIndex = (curPlayIndex - 1 + playList.size()) % playList.size();

    //获取当前行
    ui->listWidget->setCurrentRow(curPlayIndex);
    //播放对应下标的音乐
    mediaPlayer->setMedia(QMediaContent(playList[curPlayIndex]));
    mediaPlayer->play();
}

//下一曲
void Widget::on_pushButton_5_clicked()
{
    //判断播放列表是否为空
    if (playList.isEmpty()) return;

    //获取当前行
    ui->listWidget->setCurrentRow(curPlayIndex);

    //根据播放模式播放下一首
    int nextRow = 0;
    if(m_mode == ORDER_MODE){
        //避免index越界，并且让listWidget选中下一行
        curPlayIndex = (curPlayIndex+1) % playList.size();
    }
    else if (m_mode == RANDOM_MODE) {
        int newIdx;
        if (playList.size() == 1) {
            newIdx = 0;               // 只有一首，只能播它
        }
        else {
            do {
                newIdx = QRandomGenerator::global()->bounded(playList.size());//qt获取随机数的方法
            } while (newIdx == curPlayIndex);
        }
        curPlayIndex = newIdx;
    }
    else if(m_mode == CIRCLEONCE_MODE){
        curPlayIndex = curPlayIndex;
    }

    //播放对应下标的音乐
    mediaPlayer->setMedia(QMediaContent(playList[curPlayIndex]));
    mediaPlayer->play();
}

//双击列表中的歌曲实现播放
void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    curPlayIndex = index.row();
    //播放对应下标的音乐
    mediaPlayer->setMedia(QMediaContent(playList[curPlayIndex]));
    mediaPlayer->play();
}

//设置图片背景
void Widget::setBackGround(const QString & filename){
    //创建照片
    QPixmap pixmap(filename);

    //获取当前窗口的大小
    QSize windowSize = this->size();

    //将照片缩放到当前窗口的大小
    QPixmap scalePixmap = pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //创建QPattle对象，并设置背景图像(调色板)
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(scalePixmap));

    //将调色板应用到窗口
    this->setPalette(palette);
}

//设置切歌模式
void Widget::handleModeSlot(){
    //测试代码
    qDebug() << "mode changed to" << m_mode;
    //如果当前播放模式为循序播放，则切换至随机播放
    if(m_mode == ORDER_MODE){
        m_mode = RANDOM_MODE;
        ui->pushButton_2->setIcon(QIcon(":/assets/playlist_random.png"));
    }
    //如果当前播放模式为随机播放，则切换至单曲循环播放
    else if(m_mode == RANDOM_MODE){
        m_mode = CIRCLEONCE_MODE;
        ui->pushButton_2->setIcon(QIcon(":/assets/playlist_repeatOnce.png"));
    }
    //如果当前播放模式为单曲循环播放，则切换至顺序播放
    else if(m_mode == CIRCLEONCE_MODE){
        m_mode = ORDER_MODE;
        ui->pushButton_2->setIcon(QIcon(":/assets/playlist_order.png"));
    }
}

//设置暂停&播放模式切换
void Widget::PlayerIconSlot(){
    //测试代码
    qDebug() << "mode changed to" << ps_mode;
    //如果当前为播放模式则切换为暂停模式
    if(ps_mode == PLAY_MODE){
        ps_mode = STOP_MODE;
        ui->pushButton_4->setIcon(QIcon(":/assets/playing.png"));
    }
    //如果当前为暂停模式则切换为播放模式
    else if(ps_mode == STOP_MODE){
        ps_mode = PLAY_MODE;
        ui->pushButton_4->setIcon(QIcon(":/assets/pause.png"));
    }
}

//设置音乐播放列表
void Widget::handleMusicListSlot(){
    qDebug() << "clicked, flag =" << m_isShowFlag;
    //列表展示和隐藏
    if(m_isShowFlag == false){
        ui->listWidget->show();
        showAnimation(ui->listWidget);//加载动画
        ui->pushButton_7->setIcon(QIcon(":/assets/close.png"));
        m_isShowFlag = true;
    }
    else if(m_isShowFlag == true){
        hideAnimation(ui->listWidget);//隐藏动画
        ui->listWidget->hide();
        ui->pushButton_7->setIcon(QIcon(":/assets/open.png"));
        m_isShowFlag = false;
    }
}

//显示动画
void Widget::showAnimation(QWidget *target){
    QPropertyAnimation *ani = new QPropertyAnimation(target,"pos");
    ani->setDuration(1000);//动画持续时间
    ani->setStartValue(QPoint(this->width(),0));//起始坐标
    ani->setEndValue(QPoint(this->width() - ui->listWidget->width(),0));//结束坐标
    ani->start();//启动动画

    QEventLoop loop;
    //等待动画结束
    connect(ani,&QPropertyAnimation::finished,&loop,QEventLoop::quit);
    loop.exec();
}

//隐藏动画
void Widget::hideAnimation(QWidget *target){
    QPropertyAnimation *ani = new QPropertyAnimation(target, "pos", target);
    ani->setDuration(1000);                                      // 与 showAnimation 同步
    ani->setStartValue(QPoint(this->width() - target->width(), 0)); // 当前停靠位置
    ani->setEndValue(QPoint(this->width(), 0));                  // 向右滑出窗口
    ani->start();           // Qt5 兼容

    QEventLoop loop;
    connect(ani,&QPropertyAnimation::finished,&loop,QEventLoop::quit);       // 阻塞直到动画结束
    loop.exec();
}

//倍速播放
void Widget::on_pushButton_8_clicked(int value)
{
    double playbackRate = value / 100.0; // 将滑块值（百分比）转换为播放倍速
    mediaPlayer->setPlaybackRate(playbackRate); // 设置播放倍速
    qDebug() << "当前播放倍速：" << playbackRate;
}

//显示和隐藏音量条
void Widget::showVolumeSlider()
{
    ui->volumeSlider->setVisible(true);
    ui->speedlabel_3->setVisible(true);
    m_volumeSliderVisible = true;
}

void Widget::hideVolumeSlider()
{
    //通过设置m_volumeSliderVisible来判断当前音量条隐藏状态，避免重复隐藏
    if (m_volumeSliderVisible) {
        ui->volumeSlider->setVisible(false);
        ui->speedlabel_3->setVisible(false);
        m_volumeSliderVisible = false;
    }
}

//捕获鼠标进入事件
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->pushButton_6) {
        if (event->type() == QEvent::Enter) {
            showVolumeSlider(); // 鼠标进入按钮区域，显示音量条
            return true;
        }
    } else if (obj == ui->volumeSlider) {
        if (event->type() == QEvent::Leave) {
            hideVolumeSlider(); // 鼠标离开音量条，隐藏音量条
            return true;
        }
    }
    return QWidget::eventFilter(obj, event); // 调用基类的事件过滤器
}

//切换歌词显示框的显示状态
void Widget::toggleLyrics()
{
    if (ui->lyricsTextEdit->isVisible()) {
        ui->lyricsTextEdit->setVisible(false);
    } else {
        ui->lyricsTextEdit->setVisible(true);
        QString musicFilePath = playList[curPlayIndex].toLocalFile();
        QString lyrics = loadLyrics(musicFilePath);
        ui->lyricsTextEdit->setText(lyrics);
    }
}

//加载歌词文件
QString Widget::loadLyrics(const QString& musicFilePath)
{
    if (musicFilePath.isEmpty()) {
        qDebug() << "Error: No music file loaded.";
        return "No music file loaded.";
    }

    // 获取歌词文件路径
    QString lyricsFilePath = musicFilePath.section('.', 0, -2) + ".lrc";
    qDebug() << "Lyrics file path:" << lyricsFilePath;

    QFile lyricsFile(lyricsFilePath);
    if (lyricsFile.exists()) {
        qDebug() << "Lyrics file exists.";
        lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&lyricsFile);
        QString lyrics = in.readAll();
        lyricsFile.close();
        return lyrics;
    } else {
        qDebug() << "Lyrics file does not exist.";
        return "Lyrics not found.";
    }
}
