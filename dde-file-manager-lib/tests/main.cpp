#include <gtest/gtest.h>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    qDebug() << "start test cases ..............";
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    qDebug() << "end test cases ..............";
    return ret;
}
