// -*- mode: c++ -*-
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

#ifndef __DATABASE_QUERY_H__
#define __DATABASE_QUERY_H__

/**************************************************************************************************/

/* To Be Implemented
 * - CREATE / ALTER TABLE ...
 * - CREATE INDEX
 * - INSERT INTO table VALUES (...)
 * - CASE
 * - EXCEPT / MINUS
 * - MySQL: ON DUPLICATE KEY UPDATE
 * - EXISTS, ALL, ANY, SOME
 * - INNER JOIN — SELECT * FROM A INNER JOIN B ON A.key = B.key
 * - CROSS JOIN — SELECT * FROM table1 CROSS JOIN table2
 * - LEFT JOIN  — SELECT * FROM A LEFT JOIN B ON A.key = B.key
 *                SELECT * FROM A LEFT JOIN B ON A.key = B.key WHERE B.key IS NULL
 * - RIGHT JOIN — SELECT * FROM A RIGHT JOIN B ON A.key = B.key
 *                SELECT * FROM A RIGHT JOIN B ON A.key = B.key WHERE B.key IS NULL
 * - FULL JOIN —  SELECT * FROM A FULL JOIN B ON A.key = B.key WHERE A.key IS NULL OR B.key IS NULL
 * - SELF JOIN
 * - NATURAL JOIN — SELECT * FROM table1 NATURAL JOIN table2
 *
 * - from_self
 * - session.query(User).get(5)
 * - intersect — SELECT * FROM `table1` INTERSECT SELECT * FROM `table2`
 * - intersect_all
 * - join
 * - one
 * - one_or_none
 * - outerjoin
 * - prefix_with
 * - scalar
 * - select_from
 * - subquery
 * - union
 * - union_all
 */

/**************************************************************************************************/

#include <QBitArray>
#include <QList>
#include <QSharedPointer>
#include <QString>
#include <QVariant>

/**************************************************************************************************/

class QcDatabaseTable;

/**************************************************************************************************/

/* Qt Supported Databases http://doc.qt.io/qt-5/sql-driver.html#supported-databases
 * QDB2	IBM DB2 (version 7.1 and above)
 * QIBASE	Borland InterBase
 * QMYSQL	MySQL
 * QOCI	Oracle Call Interface Driver
 * QODBC	Open Database Connectivity (ODBC) - Microsoft SQL Server and other ODBC-compliant databases
 * QPSQL	PostgreSQL (versions 7.3 and above)
 * QSQLITE2	SQLite version 2
 * QSQLITE    SQLite version 3
 */

enum class SqlFlavour {
  ANSI,
  SQLite,
  MySQL,
  MariaDB,
  PostgreSQL,
  SQL_Server,
  Oracle,
  DB2
};

/**************************************************************************************************/

class QcSqlExpressionTraits;

typedef QSharedPointer<QcSqlExpressionTraits> QcSqlExpressionPtr;
typedef QList<QcSqlExpressionPtr> QcSqlExpressionList;

class QcSqlExpressionTraits
{
public:
  static QString quote_sql_identifier(const QString & name, SqlFlavour flavour);
  static QString to_sql(const QVariant & value);
  static QString comma_join(const QStringList & strings);
  static QString comma_join(const QcSqlExpressionList & expressions, SqlFlavour flavour);

public:
  virtual QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const = 0;
};

/**************************************************************************************************/

class QcSqlField : public QcSqlExpressionTraits
{
public:
  // QcSqlField();
  QcSqlField(const QString & name);
  QcSqlField(const QString & name, const QString & table_name);
  QcSqlField(const QcSqlField & other);
  ~QcSqlField();

  QcSqlField & operator=(const QcSqlField & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QString & table_name() const { return m_table_name; }
  void set_table_name(const QString & table_name) { m_table_name = table_name; }

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
  QString as(const QString & name, SqlFlavour flavour = SqlFlavour::ANSI) const;
  QString as(SqlFlavour flavour = SqlFlavour::ANSI) const; // concat tabl_name

  QcSqlExpressionPtr operator==(const QVariant & value) const;
  QcSqlExpressionPtr operator!=(const QVariant & value) const;

  QcSqlExpressionPtr operator>(const QVariant & value) const;
  QcSqlExpressionPtr operator<(const QVariant & value) const;
  QcSqlExpressionPtr operator>=(const QVariant & value) const;
  QcSqlExpressionPtr operator<=(const QVariant & value) const;

  QcSqlExpressionPtr in(const QVariantList & values) const;
  QcSqlExpressionPtr between(const QVariant & value_min, const QVariant & value_max) const;

  QcSqlExpressionPtr like(const QString & pattern) const;

  QcSqlExpressionPtr is_null() const;
  QcSqlExpressionPtr is_not_null() const;

  QcSqlExpressionPtr asc() const;
  QcSqlExpressionPtr desc() const;

public:
  QString m_name;
  QString m_table_name;
};

typedef QSharedPointer<QcSqlField> QcSqlFieldPtr;
typedef QList<QcSqlField> FieldList;

/**************************************************************************************************/

/* Field Expression
 * e.g. field operator value
 */
template<const char * Symbol>
class QcSqlFieldExpression : public QcSqlExpressionTraits
{
public:
  QcSqlFieldExpression(const QcSqlField & field, const QVariant & value);

  const QcSqlField & field() const { return m_field; }
  const QVariant & value() const { return m_value; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlField m_field; // Ptr ?
  QVariant m_value;
};

/**************************************************************************************************/

class QcSqlFieldExpressionTwoValue : public QcSqlExpressionTraits
{
public:
  QcSqlFieldExpressionTwoValue(const QcSqlField & field, const QVariant & value1, const QVariant & value2);

  const QcSqlField & field() const { return m_field; }
  const QVariant & value1() const { return m_value1; }
  const QVariant & value2() const { return m_value2; }

protected:
  QcSqlField m_field; // Ptr ?
  QVariant m_value1;
  QVariant m_value2;
};

/**************************************************************************************************/

class QcSqlBetweenExpression : public QcSqlFieldExpressionTwoValue
{
  using QcSqlFieldExpressionTwoValue::QcSqlFieldExpressionTwoValue;

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

class QcSqlFieldExpressionValueList : public QcSqlExpressionTraits
{
public:
  QcSqlFieldExpressionValueList(const QcSqlField & field, const QVariantList & values);

  const QcSqlField & field() const { return m_field; }
  const QVariantList & values() const { return m_values; }

  QStringList string_values() const;

protected:
  QcSqlField m_field; // Ptr ?
  QVariantList m_values;
};

/**************************************************************************************************/

class QcSqlInExpression : public QcSqlFieldExpressionValueList
{
  using QcSqlFieldExpressionValueList::QcSqlFieldExpressionValueList;

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

/* Suffix Expression
 * e.g. field IS NULL
 */
template<const char * Suffix>
class QcSqlFieldSuffixExpression : public QcSqlExpressionTraits
{

public:
  QcSqlFieldSuffixExpression(const QcSqlField & field);

  const QcSqlField & field() const { return m_field; }

  QString suffix() const { return Suffix; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlField m_field; // Ptr ?
};

/**************************************************************************************************/

/* Unary Expression
 * operator Expression
 * e.g. NOT field like "%foo%"
 */
template<const char * Symbol>
class QcSqlUnaryExpression : public QcSqlExpressionTraits
{
public:
  QcSqlUnaryExpression(const QcSqlExpressionPtr & expression);

  const QcSqlExpressionPtr & expresion() const { return m_expression; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
};

/**************************************************************************************************/

/* Binary Expression
 *  expression OPERATOR expression
 *  e.g. field1 = 1 AND filed2 = 2
 */
template<const char * Symbol>
class QcSqlBinaryExpression : public QcSqlExpressionTraits
{
public:
  QcSqlBinaryExpression(const QcSqlExpressionPtr & expression1,
                        const QcSqlExpressionPtr & expression2);

  const QcSqlExpressionPtr & expresion1() const { return m_expression1; }
  const QcSqlExpressionPtr & expresion2() const { return m_expression2; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression1;
  QcSqlExpressionPtr m_expression2;
};

/**************************************************************************************************/

// bool T::operator!() const;
// QcSqlExpressionPtr operator!(const QcSqlExpressionPtr & expression);

// not is a keyword
QcSqlExpressionPtr Not(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Count(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Min(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr Max(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Sum(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr Avg(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr operator&&(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2);
QcSqlExpressionPtr operator||(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2);

/**************************************************************************************************/

class QcSqlQuery
{
public:
  typedef QList<QcSqlQuery> QueryList;

private:
  enum class QueryType {
    None,
    Select,
    Insert,
    Update,
    Delete
  };

  enum class Flags {
    SelectDistinct,
    SelectCount,
    SelectExists,
    NumberOfFlags
  };

  enum class SelectType { // Fixme: ???
    None,
    SelectOne,
    // SelectAll,
  };

public:
  QcSqlQuery();
  QcSqlQuery(const QString & table_name);
  // QcSqlQuery(const QcSqlTable & table);
  QcSqlQuery(const QcSqlQuery & other);
  ~QcSqlQuery();

  QcSqlQuery & operator=(const QcSqlQuery & other);

  virtual SqlFlavour sql_flavour() const { return SqlFlavour::ANSI; }

  const QString & table_name() const { return m_table_name; }
  void set_table_name(const QString & table_name) { m_table_name = table_name; }

  QueryType query_type() const { return m_query_type; }
  SelectType select_type() const { return m_select_type; }

  // session.query(func.count(distinct(User.name)))
   QcSqlQuery & distinct();

  QcSqlQuery & count();
  QcSqlQuery & exists();

  QcSqlQuery & add_column(const QcSqlField & field);
  QcSqlQuery & add_column(const QString & name) {
    return add_column(QcSqlField(name));
  }

  QcSqlQuery & filter(const QcSqlExpressionPtr & expression);
  QcSqlQuery & filter_by(const QcSqlField & field, const QVariant & value) {
    return filter(field == value);
  }

  QcSqlQuery & group_by(const QcSqlField & field);
  QcSqlQuery & group_by(const QString & name) {
    return group_by(QcSqlField(name));
  }

  QcSqlQuery & order_by(const QcSqlExpressionPtr & expression);
  QcSqlQuery & order_by(const QcSqlField & field) {
    return order_by(QcSqlExpressionPtr(new QcSqlField(field)));
  }

  QcSqlQuery & having(const QcSqlExpressionPtr & expression);

  int get_limit() const { return m_limit; } // versus limit !
  bool unlimited() const { return m_limit == -1; }

  QcSqlQuery & limit(int value); // not set_limit !
  QcSqlQuery & all() { return limit(-1); }
  QcSqlQuery & first() { return limit(1); }
  QcSqlQuery & offset(int value); // not set_offset !
  QcSqlQuery & slice(int start, int stop);

  QcSqlQuery & one(); // Fixme: ???

  // QcSqlQuery & union_(const QcSqlQuery & query); // union is keyword
  // SELECT * FROM (SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y) UNION SELECT * FROM Z)
  // QcSqlQuery & union_(const QueryList & query);
  // SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y UNION SELECT * FROM Z)
  // QcSqlQuery & union_all(const QcSqlQuery & query); // UNION ALL
  // QcSqlQuery & union_all(const QueryList & query);

  QcSqlQuery & delete_(); // delete is a key word
  // QcSqlQuery & update(const QcSqlField & field, const QVariant & value);

  QString to_sql() const;

private:
  static QString comma_interrogation_list(int count);
  void set_flags(Flags flag, bool value = true) { m_flags.setBit(static_cast<int>(flag), value); }
  bool get_flags(Flags flag) const { return m_flags[static_cast<int>(flag)]; }
  QStringList field_names(const FieldList & fields) const;
  QStringList fields_for_update() const;
  QString table_name_as(const QString & name) const;
  QString quote_sql_identifier(const QString & name) const {
    return QcSqlExpressionTraits::quote_sql_identifier(name, sql_flavour());
  }

  // virtual QString quote_sql_identifier(const QString & name) const;

public:
  QString m_table_name;
  QueryType m_query_type = QueryType::None;
  SelectType m_select_type = SelectType::None;
  QBitArray m_flags;
  FieldList m_fields;
  QcSqlExpressionPtr m_where = nullptr;
  FieldList m_group_by;
  QcSqlExpressionPtr m_having = nullptr;
  QcSqlExpressionList m_order_by;
  int m_limit = -1;
  int m_offset = -1;
};

/**************************************************************************************************/

class QcSqliteQuery : public QcSqlQuery
{
public:
  using QcSqlQuery::QcSqlQuery;

  SqlFlavour sql_flavour() const { return SqlFlavour::SQLite; }
};

/**************************************************************************************************/

class QcMySqlQuery : public QcSqlQuery
{
public:
  using QcSqlQuery::QcSqlQuery;

  SqlFlavour sql_flavour() const { return SqlFlavour::MySQL; }

private:
  // virtual QString quote_sql_identifier(const QString & name) const;
};

/**************************************************************************************************/

class QcSqlServerQuery : public QcSqlQuery
{
public:
  using QcSqlQuery::QcSqlQuery;

  SqlFlavour sql_flavour() const { return SqlFlavour::SQL_Server; }

private:
  // virtual QString quote_sql_identifier(const QString & name) const;
};

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_query.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_QUERY_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
