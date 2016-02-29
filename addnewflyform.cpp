#include "addnewflyform.h"
#include "ui_addnewflyform.h"
#include <QMessageBox>

AddNewFlyForm::AddNewFlyForm(MyGLWidget *parent, int size, int capacity) :
    QMainWindow(parent),
    ui(new Ui::AddNewFlyForm)
{
    ui->setupUi(this);

    ui->sb_col->setMaximum(size);
    ui->sb_row->setMaximum(size);

    ui->sb_flysCount->setMaximum(size*size*capacity);

    widget = parent;


}

AddNewFlyForm::~AddNewFlyForm()
{
    delete ui;
}

void AddNewFlyForm::on_pb_add_clicked()
{
    if (ui->cb_generate->isChecked())
    {
        int flysCount = ui->sb_flysCount->value();
        float minStupid = ui->dsb_minStupidity->value();
        float maxStupid = ui->dsb_maxStupidity->value();

        emit generateRandom(flysCount, minStupid, maxStupid);
    }
    else
    {
        int row = ui->sb_row->value();
        int col = ui->sb_col->value();
        float stupidity = ui->doubleSpinBox->value();

        if (widget->isFullCell(row, col))
        {
            QMessageBox::information(this, "Невозможно добавить новую муху",
                                     "Выбранная клетка заполнена полностью. Выберите другую клетку.",
                                     QMessageBox::Ok);
            return;
        }

        emit newFlyReady(row, col, stupidity);
    }



   // hide();
}

void AddNewFlyForm::on_pb_close_clicked()
{
    hide();
}

void AddNewFlyForm::on_cb_generate_clicked(bool checked)
{
    ui->gb_cell->setEnabled(!checked);
    ui->gb_generate->setEnabled(checked);
}

void AddNewFlyForm::on_dsb_minStupidity_valueChanged(double arg1)
{
    if (arg1>ui->dsb_maxStupidity->value())
        ui->dsb_maxStupidity->setValue(arg1);
}

void AddNewFlyForm::on_dsb_maxStupidity_valueChanged(double arg1)
{
    if (arg1<ui->dsb_minStupidity->value())
        ui->dsb_minStupidity->setValue(arg1);
}
