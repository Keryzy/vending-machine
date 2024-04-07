#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonStatus(int money)
{
    if(money >= 100){
        ui->pbCoffee->setEnabled(true);
    }else{
        ui->pbCoffee->setEnabled(false);
    }

    if(money >= 150){
        ui->pbTea->setEnabled(true);
    }else{
        ui->pbTea->setEnabled(false);
    }

    if(money >= 200){
        ui->pbMilk->setEnabled(true);
    }else{
        ui->pbMilk->setEnabled(false);
    }
}

void Widget::changeMoney(int diff)
{
    if(diff==0){ // Reset button
        money = 0;
        ui->lcdNumber->display(money);
    }else{
        money += diff;
        ui->lcdNumber->display(money);
        buttonStatus(money);
    }
}

void Widget::on_pbCoin10_clicked()
{
    changeMoney(10);
}
void Widget::on_pbCoin50_clicked()
{
    changeMoney(50);
}

void Widget::on_pbCoin100_clicked()
{
    changeMoney(100);
}

void Widget::on_pbCoin500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
}

void Widget::on_reset_clicked()
{
    QMessageBox mb;
    QString result;

    int change[4]={0,};

    if(money >= 500){
        change[0] = money / 500;
        money %= 500;
    }
    if(money >= 100){
        change[1] = money / 100;
        money %= 100;
    }
    if(money >= 50){
        change[2] = money / 50;
        money %= 50;
    }
    if(money >= 10){
        change[3] = money / 10;
        money %= 10;
    }

    for(int i=0;i<4;i++){
        if(change[i]>0){
            if(i==0)
                result += "500\t count : ";
            if(i==1)
                result += "100\t count : ";
            if(i==2)
                result += "50\t count : ";
            if(i==3)
                result += "10\t count : ";

            result += QString::number(change[i]) + "\n";
        }
    }
    if(result == NULL)
        result = "Don't have any change";

    mb.information(this, "Title", result);
    changeMoney(0);
}
