#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//提前声明
class QMediaPlayer;

//切歌模式
enum PLAYMODE{
    ORDER_MODE,
    RANDOM_MODE,
    CIRCLEONCE_MODE
};

//播放暂停切换
enum PSMODE{
    PLAY_MODE,
    STOP_MODE
};

// //音乐列表展示和隐藏
// enum ICONMODE{
//     SHOW_MODE,
//     HIDE_MODE
// };

namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void setBackGround(const QString & filename);//设置图片背景

    void handleModeSlot();//设置切歌模式

    void PlayerIconSlot();//设置暂停&播放模式切换

    void handleMusicListSlot();//设置音乐播放列表

    void showAnimation(QWidget *target);//显示动画

    void hideAnimation(QWidget *target);//隐藏动画


private:
    Ui::Widget *ui;
    QList<QUrl> playList;//播放列表
    PLAYMODE m_mode;//切歌模式
    PSMODE ps_mode;//暂停播放切换
    // ICONMODE ic_mode;//列表音乐按钮切换
    int curPlayIndex = 0;
    QMediaPlayer* mediaPlayer;
    bool m_isShowFlag;//列表存在的状态
};
#endif // WIDGET_H
