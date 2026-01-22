/*
 * BDSup2Sub++ (C) 2012 Adam T.
 * Based on code from BDSup2Sub by Copyright 2009 Volker Oth (0xdeadbeef)
 * and Copyright 2012 Miklos Juhasz (mjuhasz)
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "timeutil.h"

#include <QStringList>
#include <QList>
#include <QRegularExpressionMatch>

TimeUtil::TimeUtil()
{
}

qint64 TimeUtil::timeStrXmlToPTS(QString s, double fps)
{
    QRegularExpressionMatch match = timePattern.match(s);
    if (match.hasMatch())
    {
        qint64 hour = match.captured(1).toInt();
        qint64 min = match.captured(2).toInt();
        qint64 sec = match.captured(3).toInt();
        qint64 frames = match.captured(4).toInt();

        qint64 temp = hour * 60;
        temp += min;
        temp *= 60;
        temp += sec;
        temp *= 1000;
        return (temp +(int)(((frames / fps) * 1000.0) + 0.5)) * 90;
    }
    else
    {
        return -1;
    }
}

qint64 TimeUtil::timeStrToPTS(QString s, bool *ok)
{
    *ok = false;
    bool timestampIsNegative = s[0] == '-';
    QString temp = timestampIsNegative ? s.mid(1) : s;
    QRegularExpressionMatch match = timePattern.match(s);
    if (match.hasMatch())
    {
        qint64 hour = match.captured(1).toInt();
        qint64 min = match.captured(2).toInt();
        qint64 sec = match.captured(3).toInt();
        qint64 ms  = match.captured(4).toInt();

        qint64 temp = hour * 60;
        temp += min;
        temp *= 60;
        temp += sec;
        temp *= 1000;
        *ok = true;
        qint64 ret = (temp + ms) * 90;
        return timestampIsNegative ? -ret : ret;
    }
    else
    {
        return -1;
    }
}

QString TimeUtil::ptsToTimeStrXml(qint64 pts, double fps)
{
    QList<int> time = msToTime((pts + 45) / 90);
    return QString("%1:%2:%3:%4").arg(QString::number(time[0]), 2, QChar('0'))
                                 .arg(QString::number(time[1]), 2, QChar('0'))
                                 .arg(QString::number(time[2]), 2, QChar('0'))
                                 .arg(QString::number((int)(((fps * time[3]) / 1000.0) + 0.5)), 2, QChar('0'));
}

QString TimeUtil::ptsToTimeStr(qint64 pts)
{
    bool ptsIsNegative = pts < 0;
    pts = ptsIsNegative ? -pts : pts;
    QList<int> time = msToTime((pts + 45) / 90);
    return QString("%1%2:%3:%4.%5").arg(ptsIsNegative ? "-" : "")
                                   .arg(QString::number(time[0]), 2, QChar('0'))
                                   .arg(QString::number(time[1]), 2, QChar('0'))
                                   .arg(QString::number(time[2]), 2, QChar('0'))
                                   .arg(QString::number(time[3]), 3, QChar('0'));
}

QString TimeUtil::ptsToTimeStrIdx(qint64 pts)
{
    bool ptsIsNegative = pts < 0;
    pts = ptsIsNegative ? -pts : pts;
    QList<int> time = msToTime((pts + 45) / 90);
    return QString("%1%2:%3:%4:%5").arg(ptsIsNegative ? "-" : "")
                                   .arg(QString::number(time[0]), 2, QChar('0'))
                                   .arg(QString::number(time[1]), 2, QChar('0'))
                                   .arg(QString::number(time[2]), 2, QChar('0'))
                                   .arg(QString::number(time[3]), 3, QChar('0'));
}

QList<int> TimeUtil::msToTime(qint64 ms)
{
    QList<int> time(4);
    // time[0] = hours
    time.replace(0, (int)(ms / (60 * 60 * 1000)));
    ms -= (time[0] * 60 * 60 * 1000);
    // time[1] = minutes
    time.replace(1, (int)(ms / (60 * 1000)));
    ms -= (time[1] * 60 * 1000);
    // time[2] = seconds
    time.replace(2, (int)(ms / 1000));
    ms -= (time[2] * 1000);
    time.replace(3, (int)ms);
    return time;
}
