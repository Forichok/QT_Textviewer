#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath("C:\\Users\\Forichok\\Desktop\\");
    dirmodel->setFilter((QDir::NoDotAndDotDot | QDir::AllDirs));
    ui->dirTreeView->setModel(dirmodel);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot|QDir::Files);
    QStringList filters;
    filters << "*.txt";
    filemodel->setNameFilterDisables(true);

    filemodel->setNameFilters(filters);
    filemodel->setRootPath("C:\\Users\\Forichok\\Desktop\\");

    ui->fileListView->setModel(filemodel);

    QFont font1( "Arial" );
    font = font1;
    font.setPointSize( 14 );
    color = QColor::fromRgb(0,0,0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dirTreeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->fileListView->setRootIndex(filemodel->setRootPath(sPath));
}

void MainWindow::on_fileListView_doubleClicked(const QModelIndex &index)
{
      QString sPath = filemodel->fileInfo(index).filePath();

      QFile f1(sPath);

      f1.open(QIODevice::ReadOnly | QIODevice::Text);

      QString s;

      QTextStream textStream(&f1);
      QString codec = ui->codecButtonGroup->checkedButton()->text();
      textStream.setAutoDetectUnicode(false);
      textStream.setCodec(codec.toLocal8Bit().data());

      s = textStream.readAll();
      ui->textBrowser->setAcceptRichText(true);
      ui->textBrowser->setPlainText(s);
}

void MainWindow::on_underlineCheckBox_toggled(bool checked)
{
    auto font = ui->textBrowser->font();
    if(checked){
        font.setUnderline(true);
    }else font.setUnderline(false);

        ui->textBrowser->setCurrentFont(font);
        this->font=font;
}

void MainWindow::on_boldCheckBox_toggled(bool checked)
{
    auto font = ui->textBrowser->font();
    if(checked){
        font.setBold(true);
    }else font.setBold(false);

        ui->textBrowser->setCurrentFont(font);
        this->font=font;
}

void MainWindow::on_italicCheckBox_clicked(bool checked)
{
    auto font = ui->textBrowser->font();
    if(checked){
        font.setItalic(true);
    }else font.setItalic(false);

        ui->textBrowser->setCurrentFont(font);
        this->font=font;
}

void MainWindow::on_strikeoutCheckBox_toggled(bool checked)
{
    auto font = ui->textBrowser->font();
    if(checked){
        font.setStrikeOut(true);
    }else font.setStrikeOut(false);        
        ui->textBrowser->setCurrentFont(font);
        this->font=font;
}


void MainWindow::on_colorComboBox_activated(int index)
{
    switch (index) {
    case 0:
        ui->textBrowser->setTextColor(color = QColor::fromRgb(0,0,0));
        break;
    case 1:
        ui->textBrowser->setTextColor(color = QColor::fromRgb(0,255,0));
        break;
    case 2:
        ui->textBrowser->setTextColor(color = QColor::fromRgb(0,0,255));
        break;
    case 3:
        ui->textBrowser->setTextColor(color = QColor::fromRgb(255,0,0));
        break;
    case 4:
        ui->textBrowser->setTextColor(color = QColor::fromRgb(75,0,130));
        break;
    default:
        break;
    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->textBrowser->setTextColor(QColor::fromRgb(0,0,0));
    auto fontStylesButtons = ui->fontStyleButtonGroup->buttons();
    auto font = ui->textBrowser->font();
        font.setBold(false);
        font.setItalic(false);
        font.setStrikeOut(false);
        font.setUnderline(false);
    foreach(auto fontStyleButton,fontStylesButtons){
        fontStyleButton->setChecked(false);
    }
    ui->colorComboBox->setCurrentIndex(0);
    ui->textBrowser->setText("");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSave_as_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this,tr("Save Text File"), "C://", tr("Text Files (*.txt)"));
    QFile f( filename );
    f.open( QIODevice::WriteOnly );
    auto text = ui->textBrowser->toPlainText();
    f.write(text.toLocal8Bit().data());
    // store data in f
    f.close();
}

void MainWindow::on_textBrowser_cursorPositionChanged()
{
    ui->textBrowser->setTextColor(color);
    ui->textBrowser->setCurrentFont(font);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About","WHO CARES ABOUT ABOUT? \n Forichok");



}
