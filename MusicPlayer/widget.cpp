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
    mediaPlayer->setVolume(30);

    //设置音量按钮，不使用时隐藏音量条
    ui->volumeSlider->setVisible(false);

    //设置音量按钮，点击音量按钮弹出音量条
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        bool vis = ui->volumeSlider->isVisible();
        ui->volumeSlider->setVisible(!vis);
    });

    //使QListWidget背景透明
    ui->listWidget->setStyleSheet(
        "QListWidget { background: transparent; border: none; }"
        "QListWidget::item { background: transparent; }");
    ui->listWidget->viewport()->setAutoFillBackground(false);

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

    //根据播放模式播放下一首
    //connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::on_pushButton_5_clicked);

    //设置音量条，移动滑块改变音量大小
    connect(ui->volumeSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setVolume);

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

