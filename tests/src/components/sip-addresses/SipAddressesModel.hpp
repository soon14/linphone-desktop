#ifndef SIP_ADDRESSES_MODEL_H_
#define SIP_ADDRESSES_MODEL_H_

#include <QAbstractListModel>

#include "../contact/ContactModel.hpp"

// =============================================================================

class SipAddressesModel : public QAbstractListModel {
  Q_OBJECT;

public:
  ~SipAddressesModel () = default;

  int rowCount (const QModelIndex &index = QModelIndex()) const override;

  QHash<int, QByteArray> roleNames () const override;
  QVariant data (const QModelIndex &index, int role) const override;

  static void init () {
    if (!m_instance)
      m_instance = new SipAddressesModel();
  }

  static SipAddressesModel *getInstance () {
    return m_instance;
  }

public slots:
  ContactModel *mapSipAddressToContact (const QString &sip_address) const;

private:
  SipAddressesModel (QObject *parent = Q_NULLPTR);

  QHash<QString, QVariantMap> m_sip_addresses;
  QList<const QVariantMap *> m_refs;

  static SipAddressesModel *m_instance;
};

#endif // SIP_ADDRESSES_MODEL_H_
