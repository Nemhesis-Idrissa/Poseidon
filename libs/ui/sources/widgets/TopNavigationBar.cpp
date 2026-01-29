#include <includes/widgets/TopNavigationBar.h>
#include <QStyle>
#include <QResizeEvent>
#include <QIcon>

TopNavBar::TopNavBar(QWidget *parent)
    : QWidget(parent), m_activeNavButton(nullptr)
{
    setupUI();
    initializeOpacityEffects();
}

void TopNavBar::setupUI(){
    setObjectName("TopNavBar");
    setFixedHeight(80);

    //main layout
    QHBoxLayout *topBarLayout = new QHBoxLayout(this);
    topBarLayout -> setContentsMargins(40, 0, 40, 0);
    topBarLayout -> setSpacing(0);

    //Top bar logo section
    QWidget *logoSection = new QWidget();
    QHBoxLayout *logoLayout = new QHBoxLayout(logoSection);
    logoLayout -> setContentsMargins(0, 0, 0, 0);
    logoLayout -> setSpacing(12);

    QLabel *logo = new QLabel();
    QPixmap logoLabel(":/images/aegis.png");

    logo -> setObjectName("Logo");
    logo -> setFixedSize(40, 40);
    logo -> setAlignment(Qt::AlignCenter);
    logo -> setPixmap(logoLabel);
    logo -> setPixmap(logoLabel.scaled(200, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    logoLayout->addWidget(logo);

    topBarLayout -> addWidget(logoSection);
    topBarLayout -> addSpacing(50);


    //Navigation buttons
    m_homeBtn       = createNavButton("Home", 1);
    m_searchBtn     = createNavButton("Search", 2);
    m_analyticsBtn  = createNavButton("Analytics", 3);
    m_datasetsBtn   = createNavButton("Datasets", 4);
    m_reportsBtn    = createNavButton("Reports", 5);
    m_alertsBtn     = createNavButton("Alerts", 6);
    m_dashboardsBtn = createNavButton("Dashboards",7);

    //Adding to layout
    topBarLayout -> addWidget(m_homeBtn);
    topBarLayout -> addWidget(m_searchBtn);
    topBarLayout -> addWidget(m_analyticsBtn);
    topBarLayout -> addWidget(m_datasetsBtn);
    topBarLayout -> addWidget(m_reportsBtn);
    topBarLayout -> addWidget(m_alertsBtn);
    topBarLayout -> addWidget(m_dashboardsBtn);


    // This is for Effects
    m_navButtons.append(m_homeBtn);
    m_navButtons.append(m_searchBtn);
    m_navButtons.append(m_analyticsBtn);
    m_navButtons.append(m_datasetsBtn);
    m_navButtons.append(m_reportsBtn);
    m_navButtons.append(m_alertsBtn);
    m_navButtons.append(m_dashboardsBtn);


    topBarLayout -> addStretch(1);


    //Search bar
    m_searchBar = new QLineEdit();
    m_searchBar -> setObjectName("SearchBar");
    m_searchBar -> setPlaceholderText("Search...");
    m_searchBar -> setMinimumWidth(180);
    m_searchBar -> setMaximumWidth(300);
    m_searchBar -> setFixedHeight(40);
    topBarLayout -> addWidget(m_searchBar, 1);

    topBarLayout -> addSpacing(70);

    //Settings Button
    m_settingsBtn = new QPushButton("Settings");
    m_settingsBtn -> setObjectName("SettingsButton");
    m_settingsBtn -> setFixedHeight(45);
    m_settingsBtn -> setMinimumWidth(180);
    m_settingsBtn -> setCursor(Qt::PointingHandCursor);
    m_settingsBtn -> setFlat(true);
    topBarLayout -> addWidget(m_settingsBtn, 0);
    topBarLayout -> addSpacing(15);

    setActiveButton(1);
}


void TopNavBar::initializeOpacityEffects(){
    QWidget* widgets[] = {
    m_searchBar, m_analyticsBtn, m_datasetsBtn, m_reportsBtn,
    m_alertsBtn, m_dashboardsBtn, m_settingsBtn
    };

    for(QWidget* widget : widgets){
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(widget);
        effect -> setOpacity(1.0);
        widget -> setGraphicsEffect(effect);
        m_effects[widget] = effect;
    }
}



void TopNavBar::smoothSetVisible(QWidget* widget, bool visible) {
    if (!m_effects.contains(widget)) return;

    QGraphicsOpacityEffect* effect = m_effects[widget];

    // Skip if already in correct state
    bool currentlyVisible = widget->isVisible() && effect->opacity() > 0.5;
    if (currentlyVisible == visible) return;

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(150);
    anim->setEasingCurve(QEasingCurve::InOutQuad);

    if (visible) {
        widget->setVisible(true);
        anim->setStartValue(effect->opacity());
        anim->setEndValue(1.0);
    } else {
        anim->setStartValue(effect->opacity());
        anim->setEndValue(0.0);
        connect(anim, &QPropertyAnimation::finished, [widget]() {
            widget->setVisible(false);
        });
    }

    anim->start(QPropertyAnimation::DeleteWhenStopped);
}


void TopNavBar::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    updateResponsiveLayout(event -> size().width());
}

void TopNavBar::updateResponsiveLayout(int width){
    // Hide widgets progressively as screen gets smaller
    m_dashboardsBtn  -> setVisible(width >= 900);
    m_settingsBtn    -> setVisible(width >= 1200);
    m_searchBar      -> setVisible(width >= 1000);
    m_alertsBtn      -> setVisible(width >= 800);
    m_reportsBtn     -> setVisible(width >= 700);
    m_datasetsBtn    -> setVisible(width >= 600);
    m_analyticsBtn   -> setVisible(width >= 500);

    m_homeBtn -> setVisible(true);
}

void TopNavBar::setActiveButton(int pageIndex){
    //Reset previous active button
    if(m_activeNavButton){
        m_activeNavButton -> setObjectName("NavButton");
        m_activeNavButton -> style() -> unpolish(m_activeNavButton);
        m_activeNavButton -> style() -> polish(m_activeNavButton);
    }

    //Find and set new active button
    for(QPushButton *btn : m_navButtons){
        int btnPageIndex = btn ->property("pageIndex").toInt();
        if(btnPageIndex == pageIndex){
            m_activeNavButton = btn;
            btn -> setObjectName("NavButtonActive");
            break;
        }
    }
}

void TopNavBar::setActiveNavButton(QPushButton *btn){
    if(m_activeNavButton){
        m_activeNavButton -> setObjectName("NavButton");
        m_activeNavButton -> style() -> unpolish(m_activeNavButton);
        m_activeNavButton -> style() -> polish(m_activeNavButton);
    }
    m_activeNavButton = btn;
    if(btn){
        btn -> setObjectName("NavButtonActive");
        btn -> style() -> unpolish(btn);
        btn -> style() -> polish(btn);
    }
}


QPushButton *TopNavBar::createNavButton(const QString &text, int pageIndex){
    QPushButton *btn = new QPushButton(text);
    btn -> setObjectName("NavButton");
    btn -> setCursor(Qt::PointingHandCursor);
    btn -> setFixedHeight(80);

    btn -> setProperty("pageIndex", pageIndex);
    connect(btn, &QPushButton::clicked, [this, btn, text, pageIndex](){
        qDebug()<<"Navigation to: "<<text;
        emit navigationRequested(pageIndex);
        setActiveNavButton(btn);
    });

    return btn;
}


QPushButton* TopNavBar::createDropdownButton(const QString &text, const QList<QPair<QString, int>> &items) {
    QPushButton *btn = new QPushButton(text + u8"\u25BC");
    btn->setObjectName("NavButton");
    btn->setCursor(Qt::PointingHandCursor);
    btn->setFixedHeight(80);

    QMenu *menu = new QMenu(btn);
    menu->setObjectName("DropdownMenu");

    for (const auto &item : items) {
        QAction *action = menu->addAction(item.first);
        connect(action, &QAction::triggered, [this, item]() {
            emit navigationRequested(item.second);
            setActiveButton(item.second);
        });
    }

    btn->setMenu(menu);
    return btn;
}
