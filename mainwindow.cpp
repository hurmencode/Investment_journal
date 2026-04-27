#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupModel();

    connect(ui->addButton, &QPushButton::clicked,
            this, &MainWindow::addInvestment);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    model = new QSqlTableModel(this);
    model->setTable("investments");
    model->select();

    model->setHeaderData(1, Qt::Horizontal, "Asset");
    model->setHeaderData(2, Qt::Horizontal, "Amount");
    model->setHeaderData(3, Qt::Horizontal, "Price");
    model->setHeaderData(4, Qt::Horizontal, "Date");

    ui->tableView->setModel(model);
}

void MainWindow::addInvestment()
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO investments (asset, amount, price, date) "
        "VALUES (?, ?, ?, ?)"
        );

    query.addBindValue(ui->assetInput->text());
    query.addBindValue(ui->amountInput->value());
    query.addBindValue(ui->priceInput->value());
    query.addBindValue(ui->dateInput->date().toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Insert error:" << query.lastError().text();
    }

    model->select(); // обновить таблицу
}
