/****************************************************************************
**
** Copyright (C) 2014-2017 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#ifndef QMATVIEW_H
#define QMATVIEW_H

#include "qmatdisplay.h"

class QMatView : public QQuickItem{

    Q_OBJECT
    Q_PROPERTY(QMat* mat         READ mat          WRITE setMat          NOTIFY matChanged)
    Q_PROPERTY(bool linearFilter READ linearFilter WRITE setLinearFilter NOTIFY linearFilterChanged)

public:
    explicit QMatView(QQuickItem* parent = 0);
    ~QMatView();

    QMat* mat();
    void setMat(QMat* mat);

    bool linearFilter() const;
    void setLinearFilter(bool filter);

signals:
    void matChanged(QMat* arg);
    void linearFilterChanged();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData);

private:
    QMat* m_mat;
    bool  m_linearFilter;
};

inline QMat *QMatView::mat(){
    return m_mat;
}

inline void QMatView::setMat(QMat *arg){
    if ( arg == 0 )
        return;

    cv::Mat* matData = arg->cvMat();
    if ( implicitWidth() != matData->cols || implicitHeight() != matData->rows ){
        setImplicitWidth(matData->cols);
        setImplicitHeight(matData->rows);
    }
    m_mat = arg;

    emit matChanged(arg);
    update();
}

inline bool QMatView::linearFilter() const{
    return m_linearFilter;
}

inline void QMatView::setLinearFilter(bool filter){
    if ( filter != m_linearFilter ){
        m_linearFilter = filter;
        emit linearFilterChanged();
        update();
    }
}

#endif // QMATVIEW_H
