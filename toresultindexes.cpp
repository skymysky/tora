//***************************************************************************
/*
 * TOra - An Oracle Toolkit for DBA's and developers
 * Copyright (C) 2000-2001,2001 GlobeCom AB
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries. You
 *      are also allowed to link this program with the Qt Non Commercial for
 *      Windows.
 *
 *      Specifically you are not permitted to link this program with the
 *      Qt/UNIX or Qt/Windows products of TrollTech. And you are not
 *      permitted to distribute binaries compiled against these libraries
 *      without written consent from GlobeCom AB. Observe that this does not
 *      disallow linking to the Qt Free Edition.
 *
 * All trademarks belong to their respective owners.
 *
 ****************************************************************************/

#include "toresultindexes.h"
#include "tomain.h"
#include "totool.h"
#include "toconf.h"
#include "tosql.h"
#include "toconnection.h"

bool toResultIndexes::canHandle(toConnection &conn)
{
  return toIsOracle(conn)||conn.provider()=="MySQL";
}

toResultIndexes::toResultIndexes(QWidget *parent,const char *name)
  : toResultView(false,false,parent,name)
{
  setReadAll(true);
  addColumn("Index Name");
  addColumn("Columns");
  addColumn("Type");
  addColumn("Unique");
  setSQLName("toResultIndexes");
}

static toSQL SQLColumns("toResultIndexes:Columns",
			"SELECT Column_Name FROM All_Ind_Columns\n"
			" WHERE Index_Owner = :f1<char[101]> AND Index_Name = :f2<char[101]>\n"
			" ORDER BY Column_Position",
			"List columns an index is built on");

QString toResultIndexes::indexCols(const QString &indOwner,const QString &indName)
{
  toQuery query(connection(),SQLColumns,indOwner,indName);

  QString ret;
  while(!query.eof()) {
    if (!ret.isEmpty())
      ret.append(",");
    ret.append(query.readValue());
  }
  return ret;
}

static toSQL SQLListIndex("toResultIndexes:ListIndex",
			  "SELECT Owner,\n"
			  "       Index_Name,\n"
			  "       Index_Type,\n"
			  "       Uniqueness\n"
			  "  FROM All_Indexes\n"
			  " WHERE Table_Owner = :f1<char[101]>\n"
			  "   AND Table_Name = :f2<char[101]>\n"
			  " ORDER BY Index_Name",
			  "List the indexes available on a table",
			  "8.0");
static toSQL SQLListIndex7("toResultIndexes:ListIndex",
			   "SELECT Owner,\n"
			   "       Index_Name,\n"
			   "       'NORMAL',\n"
			   "       Uniqueness\n"
			   "  FROM All_Indexes\n"
			   " WHERE Table_Owner = :f1<char[101]>\n"
			   "   AND Table_Name = :f2<char[101]>\n"
			   " ORDER BY Index_Name",
			   QString::null,
			   "7.3");

static toSQL SQLListIndexMySQL("toResultIndexes:ListIndex",
			       "SHOW INDEX FROM :tab<noquote>",
			       QString::null,
			       "3.0",
			       "MySQL");

void toResultIndexes::query(const QString &sql,const toQList &param)
{
  if (!handled())
    return;

  enum {
    Oracle,
    MySQL
  } type;

  toConnection &conn=connection();
  if(conn.provider()=="Oracle")
    type=Oracle;
  else if (conn.provider()=="MySQL")
    type=MySQL;
  else
    return;
    
  QString Owner;
  QString TableName;
  toQList::iterator cp=((toQList &)param).begin();
  if (cp!=((toQList &)param).end())
    Owner=*cp;
  cp++;
  if (cp!=((toQList &)param).end())
    TableName=(*cp);

  RowNumber=0;

  clear();

  try {
    toQuery query(connection());
    toQList par;
    if (type==Oracle)
      par.insert(par.end(),Owner);
    par.insert(par.end(),TableName);
    query.execute(SQLListIndex(conn),par);

    QListViewItem *item=NULL;
    while(!query.eof()) {
      if (type==Oracle) {
	item=new QListViewItem(this,item,NULL);

	QString indexOwner(query.readValue());
	QString indexName(query.readValue());
	item->setText(0,indexName);
	item->setText(1,indexCols(indexOwner,indexName));
	item->setText(2,query.readValue());
	item->setText(3,query.readValue());
      } else {
	query.readValue(); // Tablename
	int unique=query.readValue().toInt();
	QString name=query.readValue();
	query.readValue(); // SeqID
	QString col=query.readValue();
	query.readValue();
	query.readValue();
	query.readValue();
	query.readValue();
	query.readValue();
	if (item&&item->text(0)==name)
	  item->setText(1,item->text(1)+","+col);
	else {
	  item=new QListViewItem(this,item,NULL);
	  item->setText(0,name);
	  item->setText(1,col);
	  item->setText(2,(name=="PRIMARY")?"PRIMARY":"INDEX");
	  item->setText(3,unique?"UNIQUE":"NONUNIQUE");
	}
      }
    }
  } TOCATCH
  updateContents();
  return;
}
