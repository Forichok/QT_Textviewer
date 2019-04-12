#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dirTreeView_clicked(const QModelIndex &index);

    void on_fileListView_doubleClicked(const QModelIndex &index);

    void on_underlineCheckBox_toggled(bool checked);

    void on_boldCheckBox_toggled(bool checked);

    void on_italicCheckBox_clicked(bool checked);

    void on_strikeoutCheckBox_toggled(bool checked);

    void on_colorComboBox_activated(int index);

    void on_resetButton_clicked();

    void on_actionExit_triggered();

    void on_actionSave_as_triggered();

    void on_textBrowser_cursorPositionChanged();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    QFont font;
    QColor color;
};

#endif // MAINWINDOW_H
