#include <QDateTime>
#include <QGraphicsProxyWidget>
#include <QCalendarWidget>
void QGraphicsProxyWidget::setWidget(QWidget*){}
QWidget::QWidget(QWidget *, Qt::WindowFlags){}
void QWidget::setEnabled(bool){} 
QCalendarWidget::QCalendarWidget(QWidget *){}
QCalendarWidget::~QCalendarWidget(){}

QSize QCalendarWidget::sizeHint() const{ return QSize(1,1);}
QSize QCalendarWidget::minimumSizeHint() const{return QSize(1,1);}

QDate QCalendarWidget::selectedDate() const{return QDate::currentDate();}

int QCalendarWidget::yearShown() const{return 1900;}
int QCalendarWidget::monthShown() const{return 1;}

QDate QCalendarWidget::minimumDate() const{return QDate(1970,1,1);}
void QCalendarWidget::setMinimumDate(const QDate&){}

QDate QCalendarWidget::maximumDate() const{return QDate(2040,1,1);}
void QCalendarWidget::setMaximumDate(const QDate&){}

Qt::DayOfWeek QCalendarWidget::firstDayOfWeek() const{return Qt::Monday;}
void QCalendarWidget::setFirstDayOfWeek(Qt::DayOfWeek){}

// QCalendarWidget::### Qt 5: eliminate these two
bool QCalendarWidget::isHeaderVisible() const{return false;}
void QCalendarWidget::setHeaderVisible(bool){} 


bool QCalendarWidget::isGridVisible() const{return false;}
/*
SelectionMode QCalendarWidget::selectionMode() const{return 0;}
void QCalendarWidget::setSelectionMode(SelectionMode ){}

HorizontalHeaderFormat QCalendarWidget::horizontalHeaderFormat() const{return 0;}
void QCalendarWidget::setHorizontalHeaderFormat(HorizontalHeaderFormat)

VerticalHeaderFormat QCalendarWidget::verticalHeaderFormat() const{return 0;}
void QCalendarWidget::setVerticalHeaderFormat(VerticalHeaderFormat){return 0;}

QTextCharFormat QCalendarWidget::headerTextFormat() const{}
void QCalendarWidget::setHeaderTextFormat(const QTextCharFormat &){return 0;}

QTextCharFormat QCalendarWidget::weekdayTextFormat(Qt::DayOfWeek) const{return 0;}
void QCalendarWidget::setWeekdayTextFormat(Qt::DayOfWeek, const QTextCharFormat &){}

QMap<QDate, QCalendarWidget::QTextCharFormat> dateTextFormat() const{}
QTextCharFormat QCalendarWidget::dateTextFormat(const QDate &) const{}
void QCalendarWidget::setDateTextFormat(const QDate &, const QTextCharFormat &){}
*/
bool QCalendarWidget::isDateEditEnabled() const{return false;}
void QCalendarWidget::setDateEditEnabled(bool){}

int QCalendarWidget::dateEditAcceptDelay() const{return 0;}
void QCalendarWidget::setDateEditAcceptDelay(int){}

bool QCalendarWidget::event(QEvent *){return false;}
bool QCalendarWidget::eventFilter(QObject *, QEvent *){return false;}
void QCalendarWidget::mousePressEvent(QMouseEvent *){}
void QCalendarWidget::resizeEvent(QResizeEvent *){}
void QCalendarWidget::keyPressEvent(QKeyEvent * ){}

void QCalendarWidget::paintCell(QPainter *, const QRect &, const QDate &) const{}
void QCalendarWidget::updateCell(const QDate &){}
void QCalendarWidget::updateCells(){}

void QCalendarWidget::setSelectedDate(const QDate &){}
void QCalendarWidget::setDateRange(const QDate &, const QDate &){}
void QCalendarWidget::setCurrentPage(int , int){}
void QCalendarWidget::setGridVisible(bool){}
void QCalendarWidget::setNavigationBarVisible(bool){}
void QCalendarWidget::showNextMonth(){}
void QCalendarWidget::showPreviousMonth(){}
void QCalendarWidget::showNextYear(){}
void QCalendarWidget::showPreviousYear(){}
void QCalendarWidget::showSelectedDate(){}
void QCalendarWidget::showToday(){}
