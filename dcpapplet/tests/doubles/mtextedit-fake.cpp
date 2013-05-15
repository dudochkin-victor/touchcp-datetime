#include <mtextedit.h>
MTextEdit::MTextEdit(MTextEditModel::LineMode, const QString &, QGraphicsItem *){}
MTextEdit::MTextEdit(MTextEditModel *, QGraphicsItem *){}
MTextEdit::MTextEdit(MTextEditPrivate *, MTextEditModel *, QGraphicsItem *){}
MTextEdit::~MTextEdit(){}

/*
int MTextEdit::cursorPosition() const;

MTextEditModel::EditMode MTextEdit::mode() const;
MTextEditModel::LineMode MTextEdit::lineMode() const;
M::TextContentType MTextEdit::contentType() const;
QString MTextEdit::text() const;


QTextDocument MTextEdit::*document() const;



QTextCursor MTextEdit::textCursor() const;



void MTextEdit::setTextCursor(const QTextCursor &cursor);

*/    

void MTextEdit::setContentType(M::TextContentType){}
/*
    
    void setTextInteractionFlags(Qt::TextInteractionFlags);

    
    Qt::TextInteractionFlags textInteractionFlags() const;
    void handleMousePress(int cursorPosition, QGraphicsSceneMouseEvent *event, TextFieldLocationType *location);
    void handleMousePress(int cursorPosition, QGraphicsSceneMouseEvent *event);
    void handleMouseRelease(int cursorPosition, QGraphicsSceneMouseEvent *event, TextFieldLocationType *location);
    void handleMouseRelease(int cursorPosition, QGraphicsSceneMouseEvent *event);
    void handleMouseMove(int cursorPosition, QGraphicsSceneMouseEvent *event);
    bool isReadOnly() const;

    

    void setReadOnly(bool);

    

    MTextEditModel::EchoMode echoMode() const;

    

    void setEchoMode(MTextEditModel::EchoMode echoMode);

    

    void deselect();

    

     included in the selection

    void setSelection(int start, int length, bool useBoundaries = false);

    int selectionStart() const;

    QString selectedText() const;

    //! Returns true if some or all of the text has been selected
    bool hasSelectedText() const;

    
    bool isSelectionEnabled() const;

    

    bool isAutoSelectionEnabled() const;

    
    void setAutoSelectionEnabled(bool enable);

    

    void setInputMethodCorrectionEnabled(bool enabled);

    

    bool inputMethodCorrectionEnabled() const;

    

    void setInputMethodPredictionEnabled(bool enabled);

    

    bool inputMethodPredictionEnabled() const;

    

    int maxLength() const;

    

    void setMaxLength(int numChars);

  

    void setInputMethodAutoCapitalizationEnabled(bool enabled);

 

    bool inputMethodAutoCapitalizationEnabled() const;

    

    void setPrompt(const QString &prompt);

    

    QString prompt() const;

    

    void setValidator(const QValidator *validator);

    

    const QValidator *validator() const;

    

    bool hasAcceptableInput() const;

    

    void setCompleter(MCompleter *completer);

    

    MCompleter *completer();

    

     *
    void setAutoSipEnabled(bool enabled);

    //! \sa setAutoSipEnabled
    bool isAutoSipEnabled() const;

    

     *
    void attachToolbar(const QString &name);

    

    void attachToolbar(int id);

    
    QString attachedToolbar() const;

    

    int attachedToolbarId() const;

    

    void detachToolbar();

public Q_SLOTS:
    
*/
 bool MTextEdit::setText(const QString &){return true;}
 bool MTextEdit::insert(const QString &){return true;}
 bool MTextEdit::setCursorPosition(int){return true;}
/*
    

    void selectAll();

    

    void clear();

    
    virtual void copy();

    

    virtual void paste();

    

     *
    virtual void cut();

Q_SIGNALS:
    

    void gainedFocus(Qt::FocusReason);

    

    void lostFocus(Qt::FocusReason);

    

    void textChanged();

    //! \brief This signal is emitted whenever the selection changes
    void selectionChanged();

    //! \brief A signal to be emitted when the cursor position changes
    void cursorPositionChanged();

    //! \brief This signal is emitted when text is selected or de-selected in the text edit.
    // When text is selected this signal will be emitted with yes set to true.
    // If no text has been selected or if the selected text is de-selected this signal is emitted with yes set to false.
    void copyAvailable(bool yes);
    void pasteFailed();
    void returnPressed();

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void inputMethodEvent(QInputMethodEvent *);
    virtual void changeEvent(QEvent *event);
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
*/
