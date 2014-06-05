/****************************************************************************
**
** Copyright (C) 2014 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV application.
**
** GNU General Public License Usage
** 
** This file may be used under the terms of the GNU General Public License 
** version 3.0 as published by the Free Software Foundation and appearing 
** in the file LICENSE.GPL included in the packaging of this file.  Please 
** review the following information to ensure the GNU General Public License 
** version 3.0 requirements will be met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "QMatSource.hpp"
#include "QMatState.hpp"
#include "QMatNode.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <QSGSimpleMaterial>

QMatSource::QMatSource(QQuickItem *parent) :
    QMatDisplay(parent)
{
}

QMatSource::~QMatSource(){
}

void QMatSource::setFile(const QString &file){
    if ( file != m_file ){
        m_file = file;
        emit fileChanged();
        cv::Mat temp = cv::imread(file.toStdString());

        if ( !temp.empty() ){
            temp.copyTo(*output()->data());
            setImplicitWidth(output()->data()->size().width);
            setImplicitHeight(output()->data()->size().height);
            emit outChanged();
            update();
        }
    }
}