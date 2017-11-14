#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicmodel.h"
#include <QCloseEvent>
#include <QTranslator>
#include <QLibraryInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MusicModel *model;
    QTranslator myappTranslator;
    QTranslator s_myappTranslator;
public slots:
    void setModified();
    void update_active_actions(QModelIndex index);
private slots:
    void on_add_artist_action_triggered();
    void on_delete_action_triggered();
    void on_edit_action_triggered();
    void on_add_album_action_triggered();
    void on_add_song_action_triggered();
    bool on_save_action_triggered();
    void on_load_action_triggered();
    void on_exit_action_triggered();
    void on_actionRussian_triggered();
    void on_actionEnglish_triggered();
};

#endif // MAINWINDOW_H
