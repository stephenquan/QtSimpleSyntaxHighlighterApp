#ifndef __SimpleSyntaxHighlighter__
#define __SimpleSyntaxHighlighter__

#include <QObject>
#include <QSyntaxHighlighter>

class SimpleSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    Q_PROPERTY(QVariant textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)

public:
    SimpleSyntaxHighlighter(QObject* parent = nullptr);

signals:
    void textDocumentChanged();

protected:
    QVariant m_TextDocument;

    QVariant textDocument() const { return m_TextDocument; }
    void setTextDocument(const QVariant& textDocument);

    virtual void highlightBlock(const QString &text);

};

#endif
