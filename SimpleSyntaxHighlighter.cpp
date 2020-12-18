#include "SimpleSyntaxHighlighter.h"
#include <QQuickTextDocument>
#include <QRegularExpression>
#include <QDebug>

SimpleSyntaxHighlighter::SimpleSyntaxHighlighter(QObject* parent) :
    QSyntaxHighlighter(parent)
{
}

void SimpleSyntaxHighlighter::setTextDocument( const QVariant& textDocument )
{
    if (textDocument == m_TextDocument)
    {
        return;
    }

    m_TextDocument = textDocument;

    QQuickTextDocument* qquickTextDocument = qvariant_cast<QQuickTextDocument*>(textDocument);
    if (qquickTextDocument)
    {
        setDocument(qquickTextDocument->textDocument());
    }
    else
    {
        setDocument(nullptr);
    }

    emit textDocumentChanged();
}

void SimpleSyntaxHighlighter::highlightBlock( const QString &text )
{
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground(Qt::red);

    QRegularExpression startExpression("/\\*");
    QRegularExpression endExpression("\\*/");

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(startExpression);

    while (startIndex >= 0) {
       QRegularExpressionMatch endMatch;
       int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
       int commentLength;
       if (endIndex == -1) {
           setCurrentBlockState(1);
           commentLength = text.length() - startIndex;
       } else {
           commentLength = endIndex - startIndex
                           + endMatch.capturedLength();
       }
       setFormat(startIndex, commentLength, multiLineCommentFormat);
       startIndex = text.indexOf(startExpression,
                                 startIndex + commentLength);
    }

    qDebug() << Q_FUNC_INFO << currentBlockState() << text;
}
