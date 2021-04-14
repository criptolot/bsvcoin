// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BSVCOIN_QT_BSVCOINADDRESSVALIDATOR_H
#define BSVCOIN_QT_BSVCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BsvcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BsvcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Bsvcoin address widget validator, checks for a valid bsvcoin address.
 */
class BsvcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BsvcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // BSVCOIN_QT_BSVCOINADDRESSVALIDATOR_H
