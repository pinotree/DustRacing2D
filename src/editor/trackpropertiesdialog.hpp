// This file is part of Dust Racing 2D.
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRACKPROPERTIESDIALOG_HPP
#define TRACKPROPERTIESDIALOG_HPP

#include <QDialog>

class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

/*! Dialog to set various track properties:
 *  - Lap count
 *  - Order number
 *  - Is unlocked by default
 *  - Unlocked by which track
 */
class TrackPropertiesDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    TrackPropertiesDialog(
        unsigned int lapCount, unsigned int index, QWidget * parent = nullptr);

    //! Get lap count.
    unsigned int lapCount() const;

    //! Get index.
    unsigned int index() const;

private:

    QGridLayout * m_layout;
    QPushButton * m_okButton;
    QPushButton * m_cancelButton;
    QLineEdit   * m_lapCountEdit;
    QLabel      * m_lapCountLabel;
    QLineEdit   * m_indexEdit;
    QLabel      * m_indexLabel;
};

#endif // TRACKPROPERTIESDIALOG_HPP
