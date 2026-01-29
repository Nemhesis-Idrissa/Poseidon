#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
#include <QScreen>
#include <QPropertyAnimation>
#include <includes/mainwindow.h>
#include <QIcon>


QString loadStyleSheet(const QString &path){
    QFile file(path);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        return stream.readAll();
    }

    return QString();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString styles;
    styles += loadStyleSheet(":/styles/LoginPageStyle.qss");
    styles += loadStyleSheet(":/styles/TopNavBarStyle.qss");
    qApp->setStyleSheet(styles);

    Q_INIT_RESOURCE(resources);
    QIcon icon;

    QPixmap largePixmap(":/images/aegis.png");
    QPixmap scaledPixmap = largePixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    icon.addPixmap(scaledPixmap);
    app.setWindowIcon(icon);
    QFont font("Segoe UI", 10);
    app.setFont(font);

    QPixmap splashPixmap(":/images/aegis.png");
    QPixmap scaledSplash = splashPixmap.scaledToHeight(600, Qt::SmoothTransformation);
    QSplashScreen *splash= new QSplashScreen(scaledSplash);

    //Central position of the screen
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen ->geometry();

    int centerX = (screenGeometry.width() - splash -> width())/2;
    int centerY =(screenGeometry.height() - splash  -> height())/2;

    //positionner en haut de l'écran (hors vus)
    splash -> move(centerX, -splash->height());
    splash -> show();
    splash -> showMessage("Aegies Loading...", Qt::AlignBottom | Qt::AlignCenter,
                                                Qt::white);

    QPropertyAnimation *slideAnimation = new QPropertyAnimation(splash, "geometry");
    slideAnimation -> setDuration(800);
    slideAnimation -> setStartValue(QRect(centerX, -splash -> height(),
                                        splash -> width(), splash ->height()));

    slideAnimation -> setEndValue(QRect(centerX, centerY, splash->width(), splash->height()));
    slideAnimation -> setEasingCurve(QEasingCurve::OutBounce); //effet rebond
    slideAnimation -> start(QAbstractAnimation::DeleteWhenStopped);



    MainWindow *window = new MainWindow();

    // Après 3 secondes, glisser vers le bas et fermer
    QTimer::singleShot(3000, [splash, centerX, screenGeometry, window](){
        QPropertyAnimation *slideOut = new QPropertyAnimation(splash, "geometry");
        slideOut -> setDuration(500);
        slideOut -> setStartValue(splash -> geometry());
        slideOut -> setEndValue(QRect(centerX, screenGeometry.height(),
                                    splash -> width() , splash -> height()));

        slideOut -> setEasingCurve(QEasingCurve::InBack);
        QObject::connect(slideOut, &QPropertyAnimation::finished, [splash, window](){
            splash -> close();
            splash -> deleteLater();
            window -> show();
        });
        slideOut->start(QAbstractAnimation::DeleteWhenStopped);


    });

    return app.exec();
}
