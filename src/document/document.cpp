// This file was automatically generated by SqlOrm
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "document.h"

#include "database/json_helper.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

DocumentSchema::DocumentSchema()
: QcSchema(QLatin1String("Document"), QLatin1String("document"))
{
  add_field(QcSchemaField(QLatin1String("id"),
                          QLatin1String("int"),
                          QLatin1String("integer"),
                          QLatin1String(""),
                          QLatin1String("id"),
                          QLatin1String("id"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("name"),
                          QLatin1String("QString"),
                          QLatin1String("text"),
                          QLatin1String(""),
                          QLatin1String("name"),
                          QLatin1String("name"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("author"),
                          QLatin1String("QString"),
                          QLatin1String("text"),
                          QLatin1String(""),
                          QLatin1String("author"),
                          QLatin1String("author"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("version"),
                          QLatin1String("int"),
                          QLatin1String("integer"),
                          QLatin1String(""),
                          QLatin1String("version"),
                          QLatin1String("version"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("date"),
                          QLatin1String("QDateTime"),
                          QLatin1String("integer"),
                          QLatin1String(""),
                          QLatin1String("date"),
                          QLatin1String("date"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("description"),
                          QLatin1String("QString"),
                          QLatin1String("text"),
                          QLatin1String(""),
                          QLatin1String("description"),
                          QLatin1String("description"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("url"),
                          QLatin1String("QUrl"),
                          QLatin1String("text"),
                          QLatin1String(""),
                          QLatin1String("url"),
                          QLatin1String("url"),
                          QLatin1String(""),
                          QLatin1String("")));
  add_field(QcSchemaField(QLatin1String("size"),
                          QLatin1String("int"),
                          QLatin1String("integer"),
                          QLatin1String(""),
                          QLatin1String("size"),
                          QLatin1String("size"),
                          QLatin1String(""),
                          QLatin1String("")));
}

DocumentSchema::~DocumentSchema()
{}

/**************************************************************************************************/

Document::Document()
  : m_bits(8),
    m_id(),
    m_name(),
    m_author(),
    m_version(),
    m_date(),
    m_description(),
    m_url(),
    m_size()
{}

Document::Document(const Document & other)
  : m_bits(other.m_bits),
    m_id(other.m_id),
    m_name(other.m_name),
    m_author(other.m_author),
    m_version(other.m_version),
    m_date(other.m_date),
    m_description(other.m_description),
    m_url(other.m_url),
    m_size(other.m_size)
{}

Document::Document(const QJsonObject & json_object)
 : Document()
{
  m_id = json_object[QLatin1String("id")].toInt();
  m_name = json_object[QLatin1String("name")].toString();
  m_author = json_object[QLatin1String("author")].toString();
  m_version = json_object[QLatin1String("version")].toInt();
  m_date = json_helper::load_datetime(json_object[QLatin1String("date")]);
  m_description = json_object[QLatin1String("description")].toString();
  m_url = json_object[QLatin1String("url")].toString();
  m_size = json_object[QLatin1String("size")].toInt();
}

Document::Document(const QVariantHash & variant_hash)
 : Document()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
  m_name = variant_hash[QLatin1String("name")].toString();
  m_author = variant_hash[QLatin1String("author")].toString();
  m_version = variant_hash[QLatin1String("version")].toInt();
  m_date = variant_hash[QLatin1String("date")].toDateTime();
  m_description = variant_hash[QLatin1String("description")].toString();
  m_url = variant_hash[QLatin1String("url")].toUrl();
  m_size = variant_hash[QLatin1String("size")].toInt();
}

Document::Document(const QVariantList & variants)
 : Document()
{
  m_id = variants[0].toInt();
  m_name = variants[1].toString();
  m_author = variants[2].toString();
  m_version = variants[3].toInt();
  m_date = variants[4].toDateTime();
  m_description = variants[5].toString();
  m_url = variants[6].toUrl();
  m_size = variants[7].toInt();
}

Document::Document(const QSqlRecord & record)
 : Document()
{
  m_id = record.value(0).toInt();
  m_name = record.value(1).toString();
  m_author = record.value(2).toString();
  m_version = record.value(3).toInt();
  m_date = json_helper::load_sql_datetime_as_epoch(record.value(4));
  m_description = record.value(5).toString();
  m_url = record.value(6).toUrl();
  m_size = record.value(7).toInt();
}

Document::Document(const QSqlQuery & query)
 : Document()
{
  m_id = query.value(0).toInt();
  m_name = query.value(1).toString();
  m_author = query.value(2).toString();
  m_version = query.value(3).toInt();
  m_date = json_helper::load_sql_datetime_as_epoch(query.value(4));
  m_description = query.value(5).toString();
  m_url = query.value(6).toUrl();
  m_size = query.value(7).toInt();
}

Document::~Document()
{}

Document &
Document::operator=(const Document & other)
{
  if (this != &other) {
    m_bits = other.m_bits;
    m_id = other.m_id;
    m_name = other.m_name;
    m_author = other.m_author;
    m_version = other.m_version;
    m_date = other.m_date;
    m_description = other.m_description;
    m_url = other.m_url;
    m_size = other.m_size;
  }

  return *this;
}
bool
Document::operator==(const Document & other)
{
  if (m_id != other.m_id)
    return false;
  if (m_name != other.m_name)
    return false;
  if (m_author != other.m_author)
    return false;
  if (m_version != other.m_version)
    return false;
  if (m_date != other.m_date)
    return false;
  if (m_description != other.m_description)
    return false;
  if (m_url != other.m_url)
    return false;
  if (m_size != other.m_size)
    return false;

  return true;
}

void
Document::set_id(int value)
{
  if (m_id != value) {
    m_id = value;
    m_bits.setBit(DocumentSchema::Fields::ID);
    emit idChanged();
  }
}

void
Document::set_name(const QString & value)
{
  if (m_name != value) {
    m_name = value;
    m_bits.setBit(DocumentSchema::Fields::NAME);
    emit nameChanged();
  }
}

void
Document::set_author(const QString & value)
{
  if (m_author != value) {
    m_author = value;
    m_bits.setBit(DocumentSchema::Fields::AUTHOR);
    emit authorChanged();
  }
}

void
Document::set_version(int value)
{
  if (m_version != value) {
    m_version = value;
    m_bits.setBit(DocumentSchema::Fields::VERSION);
    emit versionChanged();
  }
}

void
Document::set_date(const QDateTime & value)
{
  if (m_date != value) {
    m_date = value;
    m_bits.setBit(DocumentSchema::Fields::DATE);
    emit dateChanged();
  }
}

void
Document::set_description(const QString & value)
{
  if (m_description != value) {
    m_description = value;
    m_bits.setBit(DocumentSchema::Fields::DESCRIPTION);
    emit descriptionChanged();
  }
}

void
Document::set_url(const QUrl & value)
{
  if (m_url != value) {
    m_url = value;
    m_bits.setBit(DocumentSchema::Fields::URL);
    emit urlChanged();
  }
}

void
Document::set_size(int value)
{
  if (m_size != value) {
    m_size = value;
    m_bits.setBit(DocumentSchema::Fields::SIZE);
    emit sizeChanged();
  }
}

QJsonObject
Document::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
    if (is_id_modified())
      json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    if (is_name_modified())
      json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    if (is_author_modified())
      json_object.insert(QLatin1String("author"), QJsonValue(m_author));
    if (is_version_modified())
      json_object.insert(QLatin1String("version"), QJsonValue(m_version));
    if (is_date_modified())
      json_object.insert(QLatin1String("date"), json_helper::dump_datetime(m_date));
    if (is_description_modified())
      json_object.insert(QLatin1String("description"), QJsonValue(m_description));
    if (is_url_modified())
      json_object.insert(QLatin1String("url"), json_helper::dump_url(m_url));
    if (is_size_modified())
      json_object.insert(QLatin1String("size"), QJsonValue(m_size));
  } else {
    json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    json_object.insert(QLatin1String("author"), QJsonValue(m_author));
    json_object.insert(QLatin1String("version"), QJsonValue(m_version));
    json_object.insert(QLatin1String("date"), json_helper::dump_datetime(m_date));
    json_object.insert(QLatin1String("description"), QJsonValue(m_description));
    json_object.insert(QLatin1String("url"), json_helper::dump_url(m_url));
    json_object.insert(QLatin1String("size"), QJsonValue(m_size));
  }

  return json_object;
}


QVariantHash
Document::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_author_modified())
      variant_hash[QLatin1String("author")] = m_author;
    if (is_version_modified())
      variant_hash[QLatin1String("version")] = m_version;
    if (is_date_modified())
      variant_hash[QLatin1String("date")] = m_date;
    if (is_description_modified())
      variant_hash[QLatin1String("description")] = m_description;
    if (is_url_modified())
      variant_hash[QLatin1String("url")] = m_url;
    if (is_size_modified())
      variant_hash[QLatin1String("size")] = m_size;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("author")] = m_author;
    variant_hash[QLatin1String("version")] = m_version;
    variant_hash[QLatin1String("date")] = m_date;
    variant_hash[QLatin1String("description")] = m_description;
    variant_hash[QLatin1String("url")] = m_url;
    variant_hash[QLatin1String("size")] = m_size;
  }

  return variant_hash;
}

QVariantList
Document::to_variant_list() const
{
  QVariantList variants;
  variants << m_id;
  variants << m_name;
  variants << m_author;
  variants << m_version;
  variants << m_date;
  variants << m_description;
  variants << m_url;
  variants << m_size;

  return variants;
}

QVariantHash
Document::to_variant_hash_sql(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_author_modified())
      variant_hash[QLatin1String("author")] = m_author;
    if (is_version_modified())
      variant_hash[QLatin1String("version")] = m_version;
    if (is_date_modified())
      variant_hash[QLatin1String("date")] = json_helper::dump_sql_datetime_as_epoch(m_date);
    if (is_description_modified())
      variant_hash[QLatin1String("description")] = m_description;
    if (is_url_modified())
      variant_hash[QLatin1String("url")] = m_url;
    if (is_size_modified())
      variant_hash[QLatin1String("size")] = m_size;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("author")] = m_author;
    variant_hash[QLatin1String("version")] = m_version;
    variant_hash[QLatin1String("date")] = json_helper::dump_sql_datetime_as_epoch(m_date);
    variant_hash[QLatin1String("description")] = m_description;
    variant_hash[QLatin1String("url")] = m_url;
    variant_hash[QLatin1String("size")] = m_size;
  }

  return variant_hash;
}

QVariantList
Document::to_variant_list_sql() const
{
  QVariantList variants;
  variants << m_id;
  variants << m_name;
  variants << m_author;
  variants << m_version;
  variants << json_helper::dump_sql_datetime_as_epoch(m_date);
  variants << m_description;
  variants << m_url;
  variants << m_size;

  return variants;
}



QVariant
Document::field(int position) const
{
  switch(position) {
   case DocumentSchema::Fields::ID:
     return m_id;
   case DocumentSchema::Fields::NAME:
     return m_name;
   case DocumentSchema::Fields::AUTHOR:
     return m_author;
   case DocumentSchema::Fields::VERSION:
     return m_version;
   case DocumentSchema::Fields::DATE:
     return m_date;
   case DocumentSchema::Fields::DESCRIPTION:
     return m_description;
   case DocumentSchema::Fields::URL:
     return m_url;
   case DocumentSchema::Fields::SIZE:
     return m_size;
   default:
     return QVariant(); // error
  }
}

void
Document::set_field(int position, const QVariant & value)
{
  switch(position) {
   case DocumentSchema::Fields::ID: {
     m_id = value.toInt();
     break;
   }
   case DocumentSchema::Fields::NAME: {
     m_name = value.toString();
     break;
   }
   case DocumentSchema::Fields::AUTHOR: {
     m_author = value.toString();
     break;
   }
   case DocumentSchema::Fields::VERSION: {
     m_version = value.toInt();
     break;
   }
   case DocumentSchema::Fields::DATE: {
     m_date = value.toDateTime();
     break;
   }
   case DocumentSchema::Fields::DESCRIPTION: {
     m_description = value.toString();
     break;
   }
   case DocumentSchema::Fields::URL: {
     m_url = value.toUrl();
     break;
   }
   case DocumentSchema::Fields::SIZE: {
     m_size = value.toInt();
     break;
   }
  }
}

QDataStream &
operator<<(QDataStream & out, const Document & obj)
{
  out << obj.id();
  out << obj.name();
  out << obj.author();
  out << obj.version();
  out << obj.date();
  out << obj.description();
  out << obj.url();
  out << obj.size();

  return out;
}

QDataStream &
operator>>(QDataStream & in, Document & obj)
{
  QDateTime _QDateTime;
  QString _QString;
  QUrl _QUrl;
  int _int;

  in >> _int;
  obj.set_id(_int);
  in >> _QString;
  obj.set_name(_QString);
  in >> _QString;
  obj.set_author(_QString);
  in >> _int;
  obj.set_version(_int);
  in >> _QDateTime;
  obj.set_date(_QDateTime);
  in >> _QString;
  obj.set_description(_QString);
  in >> _QUrl;
  obj.set_url(_QUrl);
  in >> _int;
  obj.set_size(_int);

  return in;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const Document & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QLatin1Literal("Document(");
  debug << obj.id();
  debug << QLatin1Literal(", ");
  debug << obj.name();
  debug << QLatin1Literal(", ");
  debug << obj.author();
  debug << QLatin1Literal(", ");
  debug << obj.version();
  debug << QLatin1Literal(", ");
  debug << obj.date();
  debug << QLatin1Literal(", ");
  debug << obj.description();
  debug << QLatin1Literal(", ");
  debug << obj.url();
  debug << QLatin1Literal(", ");
  debug << obj.size();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/


DocumentDatabaseSchema::DocumentDatabaseSchema(QcDatabase & database)
  : QcDatabaseSchema(database),
    m_document(nullptr)
{
  m_document = &register_table(DocumentSchema::instance());
}

DocumentDatabaseSchema::~DocumentDatabaseSchema()
{}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/