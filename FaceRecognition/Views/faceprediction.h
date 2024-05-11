#ifndef FACEPREDICTION_H
#define FACEPREDICTION_H

#include <QWidget>

namespace Ui {
class FacePrediction;
}

class FacePrediction : public QWidget
{
    Q_OBJECT

public:
    explicit FacePrediction(QWidget *parent = nullptr);
    ~FacePrediction();

private slots:
    void on_uploadBtn_clicked();

    void on_detectBtn_clicked();

private:
    Ui::FacePrediction *ui;
};

#endif // FACEPREDICTION_H
